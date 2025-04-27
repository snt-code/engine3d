# ######################################################
# Read and load all sub directory
set ( subDirectory
   ImNodeFlow/
   ImPlot/
)
foreach (directory ${subDirectory})
   add_subdirectory (${directory})
endforeach ()
# ######################################################

# ######################################################
# Reset the file scope
set( localFile
    imconfig.h
    imgui.h
    imgui_internal.h
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
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