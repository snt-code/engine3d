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
     dearimgui/
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
add_library (dearimgui ${globalFile})
target_include_directories(dearimgui PUBLIC ${CMAKE_SOURCE_DIR}/libdearimgui)
# Set output directory
set_target_properties(dearimgui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libdearimgui)
set_target_properties(dearimgui PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libdearimgui)
# ######################################################

