const Node = require("../Node/Node");

class DivElement extends Node {
    constructor(attr) {
        super("div", attr);
    }
}

module.exports = DivElement;
