const { init, holo } = require("@holo/core");

const startEntry = async (func) => {
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
    func();
};

module.exports = startEntry;
