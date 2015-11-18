
# 
# Test setup
# 

# DISABLE CMP0037: Target names should not be reserved and should match a validity pattern
# 
# This policy was introduced in 3.0.0 and does not allow targets named "test" or "help" ...
# Since we do not rely on cmake testing we stick to the old policy for now.
if(POLICY CMP0037)
    cmake_policy(SET CMP0037 OLD)
endif()

# Function: Build test and add command to execute it via target 'test'
function(add_test_without_ctest target)
    add_subdirectory(${target})
    add_dependencies(test ${target})
    add_custom_command(TARGET test POST_BUILD 
        COMMAND $<TARGET_FILE:${target}> --gtest_output=xml:gtests.xml)
endfunction()

# Design decision: tests are enabled by default. If the required components are not found,
# tests are disabled and a warning is printed, but configuration is still valid.

# Skip tests if disabled
if(NOT OPTION_BUILD_TESTS)
    return()
endif()

# Find necessary packages
find_package(GMOCK)
find_package(GTEST)

# Disable tests if gmock or gtest have not been found
if(NOT GMOCK_FOUND OR NOT GTEST_FOUND)
    message("Tests skipped: gmock and/or gtest not found")
    return()
endif()

# Include gmock and gtest
include_directories(
    ${GMOCK_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIR}
)

# Target 'test'
add_custom_target(test)
set_target_properties(test PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)


# 
# Tests
# 

add_test_without_ctest(fiblib-test)
