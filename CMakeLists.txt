cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(exercise VERSION 1.0)

# ######################################################
# Read and load all sub directory
set ( subDirectory
     libdearimgui
     #libmodule
)
foreach (directory ${subDirectory})
   add_subdirectory (${directory})
endforeach ()
# ######################################################

# ######################################################
# Create a new executable
add_executable(test.exe main.cxx imgui_impl_glfw.h imgui_impl_glfw.cpp imgui_impl_opengl3.h imgui_impl_opengl3.cpp imgui_impl_opengl3_loader.h)
target_link_libraries(test.exe PUBLIC dearimgui GL glfw GLU)
set_target_properties(test.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) 
