set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++"
)

if (SHARED)
    set(LIB_TYPE SHARED)
    set(CMAKE_C_VISIBILITY_PRESET hidden)
else()
    set(LIB_TYPE STATIC)
endif()

add_library(${TARGET_LIB} ${LIB_TYPE} ${SOURCES})

target_include_directories(${TARGET_LIB}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
