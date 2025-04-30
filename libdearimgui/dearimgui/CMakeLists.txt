# ######################################################
# Read and load all sub directory
set ( subDirectory
   ImBackend/
   ImNodeFlow/
   ImPlot/
   glad/
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
   imgui.cpp
   imgui_internal.h
   imgui_draw.cpp
   imgui_tables.cpp
   imgui_widgets.cpp
   imstb_rectpack.h
   imstb_textedit.h
   imstb_truetype.h
   imgui_demo.cpp
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