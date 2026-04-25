cmake_minimum_required(VERSION 3.10)
project(platformer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glad)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PRIVATE src/
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE glfw
	PRIVATE glad
)

target_compile_definitions(${PROJECT_NAME} 
	PRIVATE $<$<CONFIG:Debug>:_DEBUG>
)