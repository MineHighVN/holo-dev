const Node = require("../Node");

class BodyElement extends Node {
    constructor(attr) {
        super("body", attr);
        document.body = this;
    }
}

module.exports = BodyElement;
