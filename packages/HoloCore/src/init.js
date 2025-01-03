const { spawn } = require("node:child_process");
const fs = require("fs");
const path = require("node:path");

const LD_LIBRARY_PATH = process.env.LD_LIBRARY_PATH;

const execute_command = (command, args) => {
    return new Promise((resolve, reject) => {
        const configure = spawn(command, args, {
            stdio: "inherit",
            env: { ...process.env, FORCE_COLOR: "1" },
            cwd: path.join(__dirname, ".."),
        });

        configure.on("close", (code) => {
            if (code === 0) resolve();
            else reject();
        });
    });
};

const init = async () => {
    const filePath = path.join(__dirname, "../build/Release/holo_core.node");
    const exists = fs.existsSync(filePath);

    if (!exists) {
        await execute_command("node-gyp", ["configure"]);
        await execute_command("node-gyp", ["build"]);
    }
};

module.exports = init;
