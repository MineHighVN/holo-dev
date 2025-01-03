const { holo } = require("@holo/core");

/**
 * @typedef {Object} NodeAttribute
 * @property {string} tagName
 * @property {(Array<Node|string> | Node | string)} children
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
        this._children = attr.children || [];

        this.NodeID = holo.createNode(this.tagName);

        this.styles = [];

        this.key = attr.key || "";

        if (Array.isArray(this._children))
            for (let i = 0; i < attr.children.length; i++) {
                const node = attr.children[i];
                this.appendNode(node);
            }
        else {
            this._children = attr.children;

            if (typeof attr.children === "string") {
                holo.document.setChildren(this.NodeID, attr.children);
            }
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
     * Function will call when children change
     * @param {Array<Node>|string} newChildren
     */

    appendNode(node) {
        this._children.push(node);
    }
}

module.exports = Node;
