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
   implot_demo.cpp
   implot_internal.h
   implot_items.cpp
   implot.cpp
   implot.h
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