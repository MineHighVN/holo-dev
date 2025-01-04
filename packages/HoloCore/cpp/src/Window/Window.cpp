#include "Window.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../HoloEngine/Body.h"

#include "../HoloEngine/Node.h"

#include "../HPC/HPC.h"

#ifdef _WIN32
const std::string OS_NAME = "Windows";
#elif __linux__
const std::string OS_NAME = "Linux";
#else
const std::string OS_NAME = "Unknown";
#endif

std::unique_ptr<Window> window;

bool Window::Init() {
    std::cout <<  "Detect OS  >>> " << OS_NAME << "\n";

    if (!glfwInit()) {
        std::cerr << "failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    this->window = glfwCreateWindow(1280, 720, "HoloJS - New Project", NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    io.Fonts->Clear();

    ImFontConfig config;
    config.SizePixels = 16.0f;
    io.Fonts->AddFontDefault(&config);

    ImGui_ImplOpenGL3_CreateFontsTexture();

    return true;
}

void Window::Render() {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        this->draw_list = ImGui::GetForegroundDrawList();

        if (body != nullptr) {
            body->render();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(this->window);
    }
}

void Window::Quit() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->window);
    glfwTerminate();

    HPC::Emit("window_action", "close");
}

void Window::setTitle(const char* title) {
    glfwSetWindowTitle(this->window, title);
}

GLFWwindow* Window::getGLFWWindow() {
    return this->getGLFWWindow();
}
