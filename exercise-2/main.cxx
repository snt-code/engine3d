#include "../libdearimgui/dearimgui/imgui.h"
#include "../libdearimgui/dearimgui/ImBackend/imgui_impl_glfw.h"
#include "../libdearimgui/dearimgui/ImBackend/imgui_impl_opengl3.h"
#include <stdio.h>

#include "../libdearimgui/dearimgui/glad/glad.h" /// Always load before GLFW
#include <GLFW/glfw3.h>                          /// Will drag system OpenGL headers
#include <GL/glu.h>

#include <iostream>


#include "shader.h"

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
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());





    ///
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return 0;
};

// #################################################################################

// Main code
int main(int, char**)
{
    /// Initialize configuration
    configData configData;
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";


    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /// Create window
    configData.glfwWindow = glfwCreateWindow(1280, 720, "sntengine3D", nullptr, nullptr);
    if(configData.glfwWindow == nullptr)
    {
        glfwTerminate();
        return -1;    
    }
    /// Setup glfw context
    glfwMakeContextCurrent(configData.glfwWindow);
    glfwSwapInterval(1); // Enable vsync

    /// Initialize GLAD
    if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }


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


    /// OpenGL initialization context
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fragmentShaderSource ="#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    Shader shader;
    shader.load(vertexShaderSource,fragmentShaderSource);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

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

        // draw our first triangle
        // glUseProgram(shaderProgram);
        shader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

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
