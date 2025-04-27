# ######################################################
# CMake Library Template
# ######################################################
# Brief:
# The librairie structure is build as following:
#   libname/
#   | - CMakeLists.txt
#   | - name/
#     | - CMakeLists.txt
#     | - Code.cxx
# ######################################################

# ######################################################
# Read and load all sub directory
set ( subDirectory
     module
)
foreach (directory ${subDirectory})
   add_subdirectory (${directory})
endforeach ()
# ######################################################

# ######################################################
# Reset the file scope
set (localFile)
# Load file from subdirectory
foreach( file ${localFile} )
   set(tmpFile "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
   list( APPEND globalFile ${tmpFile})
endforeach( file ${subFile} )
# ######################################################

# ######################################################
# Initialize library
add_library (module ${globalFile})
target_include_directories(module PUBLIC ${CMAKE_SOURCE_DIR}/libmodule)
# Link the libraries
target_link_libraries(module PUBLIC dearimgui)
# Set output directory
set_target_properties(module PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libmodule)
set_target_properties(module PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libmodule)
# ######################################################

