cmd_Release/obj.target/holo_core.node := g++ -o Release/obj.target/holo_core.node -shared -pthread -rdynamic -m64 -L/home/minehighvn/Documents/Workspace/Holo/packages/HoloCore/cpp/dependencies/lib  -Wl,-soname=holo_core.node -Wl,--start-group Release/obj.target/holo_core/cpp/src/main.o Release/obj.target/holo_core/cpp/src/HPC/HPC.o Release/obj.target/holo_core/cpp/src/utils/getNode.o Release/obj.target/holo_core/cpp/src/utils/getParameters.o Release/obj.target/holo_core/cpp/src/Window/Window.o Release/obj.target/holo_core/cpp/src/HoloEngine/Body.o Release/obj.target/holo_core/cpp/src/HoloEngine/Div.o Release/obj.target/holo_core/cpp/src/HoloEngine/Node.o Release/obj.target/holo_core/cpp/src/HoloEngine/NodeManager.o Release/obj.target/holo_core/cpp/src/HoloEngine/Text.o Release/obj.target/holo_core/cpp/dependencies/include/imgui/imgui.o Release/obj.target/holo_core/cpp/dependencies/include/imgui/imgui_demo.o Release/obj.target/holo_core/cpp/dependencies/include/imgui/imgui_draw.o Release/obj.target/holo_core/cpp/dependencies/include/imgui/imgui_impl_glfw.o Release/obj.target/holo_core/cpp/dependencies/include/imgui/imgui_impl_opengl3.o Release/obj.target/holo_core/cpp/dependencies/include/imgui/imgui_tables.o Release/obj.target/holo_core/cpp/dependencies/include/imgui/imgui_widgets.o -Wl,--end-group -lglfw -lrt -lm -ldl -lGL
