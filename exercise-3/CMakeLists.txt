cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(exercise VERSION 1.0)

# ######################################################
# Read and load all sub directory
set ( subDirectory
)
foreach (directory ${subDirectory})
   add_subdirectory (${directory})
endforeach ()
# ######################################################

# ######################################################
# Create a new executable
add_executable(exercise03.exe main.cxx)
target_link_libraries(exercise03.exe PUBLIC dearimgui glfw GLU GL)
set_target_properties(exercise03.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exe/) 
