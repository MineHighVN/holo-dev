{
    "targets": [
        {
            "target_name": "holo_core",
            "sources": [
                "<!@(node generate_sources.js)",
            ],
            "include_dirs": [
                "<(module_root_dir)/cpp/dependencies/include"
            ],
            "cflags": [
                "-std=c++11",
            ],
            "cflags_cc": [
                "-fexceptions",
            ],
            "conditions": [
                ['OS=="linux"', {
                    "defines": [
                        "LINUX",
                    ],
                    "cflags": [
                        "-fPIC",
                    ],
                    "libraries": [
                        "-lglfw",
                        "-lrt",
                        "-lm",
                        "-ldl",
                        "-lGL",
                    ],
                }
                ],
                ['OS=="mac"', {
                    "defines": [
                        "MAC",
                    ],
                }],
                ['OS=="win"', {
                    "defines": [
                        "WIN",
                    ],
                    "library_dirs": [
                        "<(module_root_dir)/cpp/dependencies/lib/windows"
                    ],
                    "libraries": [
                        "-lglfw3_mt",
                        "-lopengl32",
                        "-lgdi32",
                    ],
                }],
            ],
        }
    ]
}