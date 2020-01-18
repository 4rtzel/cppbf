cmake_minimum_required(VERSION 3.0)
project(cppbf VERSION 1.0 LANGUAGES CXX)

add_library(
    ${PROJECT_NAME}
    INTERFACE
)

target_compile_features(
    ${PROJECT_NAME}
    INTERFACE
        cxx_std_17
)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(
        ${PROJECT_NAME}
        INTERFACE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
