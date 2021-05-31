# ---- Name of example target ----

set(EXAMPLE ${TARGET_LIB}_example)


# ---- Source files of example ----

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++")

# ---- Define example target ----

add_executable(${EXAMPLE} ${SOURCES})

target_include_directories(${EXAMPLE}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${EXAMPLE} PRIVATE ${TARGET_LIB})

set_target_properties(${EXAMPLE} PROPERTIES CXX_STANDARD 17)
