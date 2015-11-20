
# 
# Configuration for all sub-projects
# 

# Generate version-header
configure_file(template-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/template-version.h)



# Determine runtime directory
set(RUNTIME_DIR "${PROJECT_SOURCE_DIR}")
if(OPTION_PORTABLE_INSTALL)
    set(RUNTIME_DIR_INSTALL "")
else()
    set(RUNTIME_DIR_INSTALL "${CMAKE_INSTALL_PREFIX}/${INSTALL_DATA}")
endif()

message("RUNTIME_DIR         = ${RUNTIME_DIR}")
message("RUNTIME_DIR_INSTALL = ${RUNTIME_DIR_INSTALL}")

set(TEMPLATE_META_SOURCE         "${CMAKE_CURRENT_BINARY_DIR}/template-meta.cpp")
set(TEMPLATE_META_SOURCE_INSTALL "${CMAKE_CURRENT_BINARY_DIR}/template-meta-install.cpp")

set(VAR_RUNTIME_DIR "${RUNTIME_DIR}")
configure_file(template-meta.cpp.in ${TEMPLATE_META_SOURCE})
set(VAR_RUNTIME_DIR "${RUNTIME_DIR_INSTALL}")
configure_file(template-meta.cpp.in ${TEMPLATE_META_SOURCE_INSTALL})
set(VAR_RUNTIME_DIR "")


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
