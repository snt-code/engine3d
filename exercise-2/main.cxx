#include "../libdearimgui/dearimgui/imgui.h"
#include "../libdearimgui/dearimgui/ImBackend/imgui_impl_glfw.h"
#include "../libdearimgui/dearimgui/ImBackend/imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <GL/glu.h>

#include <iostream>


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// #################################################################################

// Cube vertices
float cubeVertices[] = {
    // Positions        
    -0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f,  0.5f, 
     0.5f, -0.5f,  0.5f, 
     0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f,  0.5f  
};

unsigned int cubeIndices[] = {
    // Back face
    0, 1, 2,
    2, 3, 0,
    // Front face
    4, 5, 6,
    6, 7, 4,
    // Left face
    4, 0, 3,
    3, 7, 4,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Bottom face
    4, 5, 1,
    1, 0, 4,
    // Top face
    3, 2, 6,
    6, 7, 3
};

void drawCube(float angle)
{
    glPushMatrix();
    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 36; ++i)
    {
        int idx = cubeIndices[i];
        glVertex3f(cubeVertices[3 * idx], cubeVertices[3 * idx + 1], cubeVertices[3 * idx + 2]);
    }
    glEnd();

    glPopMatrix();

}

// #################################################################################

struct configData
{
    /// GLFW
    GLFWwindow* glfwWindow;

    /// 

    ///
    ImVec4 mainv_clearColor  = ImVec4(0.483f, 0.483f, 0.483f, 1.00f);
    ///
    bool flag_demo_window    = true;
    bool flag_window_1       = false;

    ///
    float demo_cube_angle    = 0.0f;

};

// #################################################################################

int contextImGui(configData& configData)
{
    // Demo Window
    // if (configData.flag_demo_window)
    //     ImGui::ShowDemoWindow(&configData.flag_demo_window);

    // // 3. Show another simple window.
    // if (configData.flag_window_1)
    // {
    //     ImGui::Begin("Another Window", &configData.flag_window_1);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    //     ImGui::Text("Hello from another window!");
    //     if (ImGui::Button("Close Me"))
    //         configData.flag_window_1= false;
    //     ImGui::End();
    // }

    return 0;
}

// #################################################################################

int contextRendering(configData& configData)
{
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(configData.glfwWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(configData.mainv_clearColor.x * configData.mainv_clearColor.w, configData.mainv_clearColor.y * configData.mainv_clearColor.w, configData.mainv_clearColor.z * configData.mainv_clearColor.w, configData.mainv_clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());




    // Draw cube
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)display_w / (float)display_h, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);

    configData.demo_cube_angle += 0.5f;
    drawCube(configData.demo_cube_angle);





    ///
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return 0;
};

// #################################################################################

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    /// Initialize configuration
    configData configData;
    configData.glfwWindow = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);

    // Create window with graphics context
    if (configData.glfwWindow  == nullptr)
        return 1;
    glfwMakeContextCurrent(configData.glfwWindow);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(configData.glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glEnable(GL_DEPTH_TEST);
    // Main loop
    while (!glfwWindowShouldClose(configData.glfwWindow))
    {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /// running imgui context
        contextImGui(configData);

        /// main viewport rendering
        contextRendering(configData);

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(configData.glfwWindow);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(configData.glfwWindow);
    glfwTerminate();

    return 0;
}
