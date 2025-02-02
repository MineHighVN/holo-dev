const fs = require("fs");
const path = require("path");

const folders = [
    "cpp/src",
    "cpp/src/HPC",
    "cpp/src/utils",
    "cpp/src/Window",
    "cpp/src/HoloEngine",
    "cpp/src/exports",
    "cpp/dependencies/include/imgui",
];

function getCppFiles() {
    const cppFiles = [];
    folders.forEach((folder) => {
        const fullPath = path.resolve(__dirname, folder);
        if (fs.existsSync(fullPath)) {
            const files = fs
                .readdirSync(fullPath)
                .filter((file) => file.endsWith(".cpp"))
                .map((file) => path.join(folder, file).replace(/\\/g, "/"));
            cppFiles.push(...files);
        }
    });
    return cppFiles;
}

const cppFiles = getCppFiles();
cppFiles.forEach((file) => console.log(file));
