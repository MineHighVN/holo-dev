const { holo } = require("@holo/core");

let callback = [];
let initialization = false;

class HPC {
    static addEventCallback(cb) {
        if (typeof cb === "function") callback.push(cb);
        else throw Error("first argument must be a function");
    }

    static removeAllEventCallback() {
        callback = [];
    }

    static init() {
        if (!initialization) {
            initialization = true;

            holo.hpc.registerHPC((event, data) => {
                for (let i = 0; i < callback.length; i++) {
                    const func = callback[i];
                    func(event, data);
                }
            });
        }
    }
}

module.exports = HPC;
