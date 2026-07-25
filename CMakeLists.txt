cmake_minimum_required(VERSION 3.15)

project(Raytracing)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_library(glad
    external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)
include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

FetchContent_MakeAvailable(glm)

include_directories(include)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.hpp" "src/*.h" "include/*.h" "include/*.hpp")

add_executable(Raytracing ${SOURCES} ${HEADERS})

target_link_libraries(Raytracing
    PRIVATE
        glfw
        glad
        glm
)

if(MSVC)
    target_compile_options(Raytracing PRIVATE /W4)
else()
    target_compile_options(Raytracing PRIVATE -Wall -Wextra)
endif()