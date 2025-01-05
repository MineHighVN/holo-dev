const path = require("path");
const fs = require("fs");

const calculateSpecificity = (selector) => {
    const idCount = (selector.match(/#/g) || []).length;
    const classCount = (selector.match(/\./g) || []).length;
    const elementCount = (selector.match(/[a-zA-Z0-9-]+/g) || []).length;

    return {
        id: idCount,
        class: classCount,
        element: elementCount,
        total: idCount * 100 + classCount * 10 + elementCount,
    };
};

const parse = (css) => {
    const result = {};
    const rules = css.split("}");

    const toCamelCase = (str) =>
        str.replace(/-([a-z])/g, (_, char) => char.toUpperCase());

    rules.forEach((rule) => {
        const [selector, styles] = rule.split("{");
        if (selector && styles) {
            const cleanSelector = selector.trim();
            const styleObject = styles.split(";").reduce((acc, style) => {
                const [key, value] = style.split(":");
                if (key && value) {
                    acc[toCamelCase(key.trim())] = value.trim();
                }
                return acc;
            }, {});
            result[cleanSelector] = styleObject;
        }
    });

    return result;
};

const loadAndParse = (filePath) => {
    const css = fs.readFileSync(filePath, { encoding: "utf8" });

    return parse(css);
};

module.exports = { parse, loadAndParse };
