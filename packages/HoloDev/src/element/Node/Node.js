const { holo } = require("@holo/core");

/**
 * @typedef {Object} NodeAttribute
 * @property {string} tagName
 * @property {(Array<Node|string> | Node | string | undefined)} children
 * @property {Array} styles
 * @property {{current: any}} ref
 * @property {string} key
 */

class Node {
    NodeID = -1;

    /**
     *
     * @param {string} tagName
     * @param {NodeAttribute} [attr={}]
     */
    constructor(tagName, attr = {}) {
        this.tagName = tagName;

        /**
         * @type {Array<Node>|string}
         */
        this._children = [];

        /**
         * @type {Node | null}
         */
        this.parent = null;

        this.NodeID = holo.document.createNode(this.tagName);

        this.styles = [];

        this.key = attr.key || "";

        if (attr.children) {
            this.setChildren(attr.children);
        }
    }

    /**
     * Getter for children
     */
    get children() {
        return this._children;
    }

    /**
     * Setter for children
     */
    set children(newChildren) {
        this._children = newChildren;
    }

    /**
     * flattens nested arrays to single-level array
     * @param {Array} array
     * @returns {Array}
     */
    flatten(array) {
        return Array.isArray(array)
            ? array.reduce((acc, item) => acc.concat(this.flatten(item)), [])
            : [array];
    }

    /**
     * @param {Array<Node|string> | Node|string} children
     */
    appendChildren(children) {
        const flatChildren = this.flatten(children);
        for (let i = 0; i < flatChildren.length; i++) {
            if (flatChildren[i] instanceof Node) flatChildren[i].parent = this;
        }
        this._children.push(...flatChildren);

        holo.document.appendChildren(this.NodeID, flatChildren);
    }

    /**
     * @param {Array<Node|string> | Node|string} children
     */
    setChildren(children) {
        const flatChildren = this.flatten(children);
        for (let i = 0; i < flatChildren.length; i++) {
            if (flatChildren[i] instanceof Node) flatChildren[i].parent = this;
        }
        this._children = flatChildren;

        holo.document.setChildren(this.NodeID, flatChildren);
    }
}

module.exports = Node;
