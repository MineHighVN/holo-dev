const init = require("./src/init");
const { holoBinaryPath } = require("./variable");

/**
 * @typedef {Object} holo
 *
 * @property {Object} window - All method about window
 * @property {(title: string) => void} window.setTitle - Set title for window
 * @property {() => void} window.init - Init everything about window
 *
 * @property {Object} hpc - All method about HPC
 * @property {(a: string, b: any) => void} hpc.registerHPC - Register HPC for handle event
 *
 * @property {Object} document - Control everything on view - C++
 * @property {(NodeID: number, children: (string | number)) => void} document.setChildren - set children for a node
 * @property {(NodeID: number, children: (string | number)) => void} document.appendChildren - append a node child to another node
 * @property {(nodeName: string) => number} document.createNode - Create new node
 *
 */

/** @type {holo} */
const holo = require(holoBinaryPath);

module.exports = { init, holo };
