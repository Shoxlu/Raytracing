cmake_minimum_required(VERSION 3.15)

project(GeneticSimulation CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/SDL)

include_directories(include)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.hpp" "src/*.h" "include/*.h" "include/*.hpp")


if(WIN32)
    add_executable(GeneticSimulation ${SOURCES} ${HEADERS})
else()
    add_executable(GeneticSimulation ${SOURCES} ${HEADERS})
endif()

target_link_libraries(GeneticSimulation PRIVATE SDL3::SDL3)

if(MSVC)
    target_compile_options(GeneticSimulation PRIVATE /W4)
else()
    target_compile_options(GeneticSimulation PRIVATE -Wall -Wextra)
endif()