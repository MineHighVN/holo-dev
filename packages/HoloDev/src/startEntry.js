const { init, holo } = require("@holo/core");
const createElement = require("./createElement");
const HPC = require("./HPC");

const startEntry = async (func) => {
    global.document = {};

    try {
        await init();
        HPC.init();
        console.log("Initialization completed.");
        // holo.hpc.registerHPC((event, data) => {
        //     console.log("OK >> ", event, data);

        //     if (event === "window_action") {
        //         if (data === "close") {
        //             process.exit(0);
        //         }
        //     }
        // });
        HPC.addEventCallback((event, data) => {
            if (event === "window_action") {
                if (data === "close") {
                    process.exit(0);
                }
            }
        });
    } catch (err) {
        process.exit(1);
    }

    holo.window.init();

    const body = createElement("body");
    document.body = body;
    document.body.appendChildren(func());
};

module.exports = startEntry;
