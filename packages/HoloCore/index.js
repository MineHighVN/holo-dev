const init = require("./src/init");

/**
 * @typedef {Object} holo
 *
 * @property {Object} window - All method about window
 * @property {(title: string) => void} window.setTitle - Set title for window
 * @property {() => void} window.init - Init everything about window
 *
 * @property {Object} hpc - All method about HPC
 * @property {(a: string, b: any) => void} hpc.registerHPC - Register HPC for handle event
 * @property {(nodeName: string) => number} holo.createNode - Create new node
 *
 * @property {Object} document - Control everything on view - C++
 * @property {(NodeID: number, children: (string | number)) => void} document.setChildren - set children for a node
 * @property {(NodeID: number, children: (string | number)) => void} document.appendChildren - append a node child to another node
 *
 */

/** @type {holo} */
const holo = require("./build/Release/holo_core.node");

module.exports = { init, holo };
