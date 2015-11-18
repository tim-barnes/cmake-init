
# 
# Configuration for all sub-projects
# 

# Generate version-header
configure_file(template-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/template-version.h)

# Include files from the binary directory (e.g., auto-generated headers)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)


# 
# Sub-projects
# 

# Libraries
set(IDE_FOLDER "")
add_subdirectory(fiblib)

# Applications
set(IDE_FOLDER "Applications")
add_subdirectory(fibcmd)

# Tests
set(IDE_FOLDER "Tests")
add_subdirectory(tests)


# 
# Deployment
# 

# We do NOT want to deploy this header (at least not for binary packages)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/template/template-version.h DESTINATION ${INSTALL_INCLUDE}/template)
