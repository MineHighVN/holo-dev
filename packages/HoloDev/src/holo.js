const createElement = require("./createElement");

/**
 *
 * @param {string} tagName
 * @param {import("./element/Node").NodeAttribute} attributes
 * @returns
 */
const _holo = (tagName, attributes) => {
    return createElement(tagName, attributes);
};

module.exports = _holo;
