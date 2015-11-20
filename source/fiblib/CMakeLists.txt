
# 
# Find external dependencies
# 

# e.g., find_package(THIRDPARTY REQUIRED)


# 
# Declare target
# 

set(target fiblib)
message(STATUS "Lib ${target}")


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
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# 
# Libraries
# 

set(libs
    # e.g., ${THIRDPARTY_LIBRARY}
)


# 
# Compiler definitions
# 

# Library import/export
if (OPTION_BUILD_STATIC)
    add_definitions("-D${META_PROJECT_NAME_UPPER}_STATIC")
else()
    add_definitions("-DFIBLIB_EXPORTS")
endif()


# 
# Sources
# 

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(api_includes
    ${include_path}/fiblib_api.h
    ${include_path}/Fibonacci.h
    ${include_path}/fiblib_meta.h
)

set(sources
    ${source_path}/Fibonacci.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${api_includes})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# 
# Build
# 

add_library("${target}-temp" OBJECT ${api_includes} ${sources})

target_compile_options("${target}-temp" PRIVATE ${DEFAULT_COMPILE_FLAGS})

set_target_properties("${target}-temp"
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH	            ${include_path})

add_library(${target} ${TEMPLATE_META_SOURCE} $<TARGET_OBJECTS:fiblib-temp>)
set_target_properties("${target}"
    PROPERTIES
    OUTPUT_NAME "${target}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${target} ${libs})

add_library("${target}-install" ${TEMPLATE_META_SOURCE_INSTALL} $<TARGET_OBJECTS:fiblib-temp>)
set_target_properties("${target}-install"
    PROPERTIES
    OUTPUT_NAME "${target}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp"
)

target_link_libraries("${target}-install" ${libs})


# 
# Deployment
# 

# Library
install(TARGETS "${target}-install"
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
