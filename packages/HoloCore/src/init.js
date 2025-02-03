const { spawn } = require("node:child_process");
const fs = require("fs");
const path = require("node:path");
const { holoBinaryPath } = require("../variable");

const execute_command = (command, args) => {
    return new Promise((resolve, reject) => {
        const configure = spawn(command, args, {
            cwd: path.join(__dirname, ".."),
        });

        configure.on("close", (code) => {
            if (code === 0) resolve();
            else reject();
        });
    });
};

const init = async () => {
    const filePath = path.join(path.join(__dirname, ".."), holoBinaryPath);
    const exists = fs.existsSync(filePath);

    if (!exists) {
        await execute_command("node-gyp", ["configure"]);
        await execute_command("node-gyp", ["build"]);
    }
};

module.exports = init;
