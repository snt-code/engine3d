# ######################################################
# Read and load all sub directory
set ( subDirectory
)
foreach (directory ${subDirectory})
   add_subdirectory (${directory})
endforeach ()
# ######################################################

# ######################################################
# Reset the file scope
set( localFile
   imgui_impl_glfw.h
   imgui_impl_glfw.cpp
   imgui_impl_opengl2.h
   imgui_impl_opengl2.cpp   
   imgui_impl_opengl3.h
   imgui_impl_opengl3.cpp
   imgui_impl_opengl3_loader.h
)
foreach( file ${localFile} )
   set(tmpFile "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
   list( APPEND globalFile ${tmpFile})
endforeach( file ${subFile} )
# ######################################################

# ######################################################
# propagate upwards
set(globalFile "${globalFile}" PARENT_SCOPE)
# ######################################################