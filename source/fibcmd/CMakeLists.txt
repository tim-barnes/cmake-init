
# 
# Find external dependencies
# 

# e.g., find_package(THIRDPARTY REQUIRED)


# 
# Declare target
# 

set(target fibcmd)
message(STATUS "App ${target}")


# 
# Includes
# 

# External includes
include_directories(
    # e.g., ${TRDP_INCLUDE_DIR}
)

# Includes of this project
include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/fiblib/include
)


# 
# Libraries
# 

set(libs
    # e.g., ${TRDP_LIBRARIES}
    fiblib
)


# 
# Compiler definitions
# 

# Library import/export
if (OPTION_BUILD_STATIC)
    add_definitions("-D${META_PROJECT_NAME_UPPER}_STATIC")
endif()


# 
# Sources
# 

set(sources
    main.cpp
)


# 
# Build
# 

add_executable(${target} ${sources})

target_link_libraries(${target} ${libs})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

set_target_properties(${target}
    PROPERTIES
    INSTALL_VERSION              FALSE
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")


# 
# Deployment
# 

install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
#   LIBRARY DESTINATION ${INSTALL_SHARED}
#   ARCHIVE DESTINATION ${INSTALL_LIB}
)
