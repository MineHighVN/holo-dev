const Node = require("../Node/Node");

class TextElement extends Node {
    constructor(tagName, attr) {
        super(tagName, attr);
    }
}

module.exports = TextElement;
