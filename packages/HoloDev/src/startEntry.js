const { init, holo } = require("@holo/core");
const createElement = require("./createElement");

const startEntry = async (func) => {
    global.document = {};

    const body = createElement("body");

    document.body = body;

    try {
        await init();
        console.log("Initialization completed.");
        holo.hpc.registerHPC((event, data) => {
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
    document.body.appendNode(func());
};

module.exports = startEntry;
