# ######################################################
# Read and load all sub directory
set ( subDirectory
    glad/
    glm/
    imgui/
    shader/
)
foreach (directory ${subDirectory})
   add_subdirectory (${directory})
endforeach ()
# ######################################################

# ######################################################
# Reset the file scope
set( localFile
    object.h
    object.cxx
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