cmd_Release/holo_core.node := ln -f "Release/obj.target/holo_core.node" "Release/holo_core.node" 2>/dev/null || (rm -rf "Release/holo_core.node" && cp -af "Release/obj.target/holo_core.node" "Release/holo_core.node")
