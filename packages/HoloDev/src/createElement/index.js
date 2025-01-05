const TextElement = require("../element/Text");
const DivElement = require("../element/Div");
const BodyElement = require("../element/Body");
const NodeAttribute = require("../element/Node");

const elementMap = {
    /**
     *
     * @param {NodeAttribute} attr
     * @returns {DivElement}
     */
    div: (attr) => new DivElement(attr),
    p: (attr) => new TextElement("p", attr),
    /**
     *
     * @param {NodeAttribute} attr
     * @returns {BodyElement}
     */
    body: (attr) => new BodyElement(attr),
    fragment: (attr) => {
        return attr.children || [];
    },
};

/**
 *
 * @param {"div" | "p" | "body"} name
 * @param {NodeAttribute} attributes
 */
const createElement = (name, attributes) => {
    if (typeof name === "function") {
        const func = name;

        return func(attributes || {});
    } else {
        const func = elementMap[name];

        if (func) return func(attributes);
        else {
            throw Error(`tag not exists`);
        }
    }
};

module.exports = createElement;
