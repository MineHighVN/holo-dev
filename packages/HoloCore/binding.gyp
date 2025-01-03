{
    "targets": [
        {
            "target_name": "holo_core",
            "sources": [
                "<!@(ls -1 cpp/src/*.cpp)",
                "<!@(ls -1 cpp/src/HPC/*.cpp)",
                "<!@(ls -1 cpp/src/utils/*.cpp)",
                "<!@(ls -1 cpp/src/Window/*.cpp)",
                "<!@(ls -1 cpp/src/HoloEngine/*.cpp)",
                "<!@(ls -1 cpp/dependencies/include/imgui/*.cpp)",
            ],
            "include_dirs": [
                "<(module_root_dir)/cpp/dependencies/include"
            ],
            "library_dirs": [
                "<(module_root_dir)/cpp/dependencies/lib"
            ],
            "cflags": [
                "-std=c++11",
            ],
            "cflags_cc": [
                "-fexceptions",
            ],
            "libraries": [
                "-lglfw",
                "-lrt",
                "-lm",
                "-ldl",
                "-lGL",
            ],
        }
    ]
}