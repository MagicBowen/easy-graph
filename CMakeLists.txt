cmake_minimum_required(VERSION 3.14)

# ---- Project ----

project(easy_graph VERSION 1.0.0)

set(TARGET_LIB ${PROJECT_NAME})

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Options for project ----

option(SHARED      "Generate shared library otherwise static" OFF)
option(EXAMPLE     "Generate examples of target" ON)
option(ENABLE_TEST "Build tests" OFF)
option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)

# ---- Using CPM to add dependencies for project ----

include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)
CPMUsePackageLock(package-lock.cmake)

# ---- Add source folder for project ----

add_subdirectory("src")

# ---- Add example for project ----

if(EXAMPLE)
    add_subdirectory(example)
endif()

# ---- Add test for project ----

if(ENABLE_TEST)
    add_subdirectory(test)
endif()
