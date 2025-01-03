const TextElement = require("../element/TextElement");
const DivElement = require("../element/DivElement");

const elementMap = {
    div: (attr) => new DivElement(attr),
    p: (attr) => new TextElement("p", attr),
};

/**
 *
 * @param {string} name
 * @param {*} attributes
 */
const createElement = (name, attributes) => {
    const func = elementMap[name];

    if (func) return func(attributes);
    else {
        throw Error(`tag not exists`);
    }
};

module.exports = createElement;
