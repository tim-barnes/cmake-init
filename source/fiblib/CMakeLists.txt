
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

set(target_objects "${target}-objects")
set(target_install "${target}-install")
set(target_local   "${target}-local")

# Build the main part of the library as a cmake object library (no actual output)
add_library(${target_objects} OBJECT ${api_includes} ${sources})
target_compile_options(${target_objects} PRIVATE ${DEFAULT_COMPILE_FLAGS})
set_target_properties(${target_objects}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH	             ${include_path})

# Build local version of the library
add_library(${target_local} ${TEMPLATE_META_SOURCE} $<TARGET_OBJECTS:${target_objects}>)
set_target_properties("${target_local}"
    PROPERTIES
    OUTPUT_NAME              "${target}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    INSTALL_VERSION          FALSE
)
target_link_libraries(${target_local} ${libs})

# Build install-version of the library
add_library(${target_install} ${TEMPLATE_META_SOURCE_INSTALL} $<TARGET_OBJECTS:${target_objects}>)
set_target_properties(${target_install}
    PROPERTIES
    OUTPUT_NAME              "${target}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp"
    INSTALL_VERSION          TRUE
)
target_link_libraries(${target_install} ${libs})

# Create library target
add_library(${target} INTERFACE)
target_link_libraries(${target} INTERFACE
#   $<$<BOOL:$<TARGET_PROPERTY:INSTALL_VERSION>>:${target_install}>
#   $<$<NOT:$<BOOL:$<TARGET_PROPERTY:INSTALL_VERSION>>>:${target_local}>
    $<$<BOOL:$<TARGET_PROPERTY:INSTALL_VERSION>>:bla>
    $<$<NOT:$<BOOL:$<TARGET_PROPERTY:INSTALL_VERSION>>>:blub>
)



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
