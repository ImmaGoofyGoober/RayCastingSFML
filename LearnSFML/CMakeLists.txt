cmake_minimum_required(VERSION 3.20)
project("RayCastingSFML" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/sfml/sfml
	GIT_TAG master
)

FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} 
	"src/main.cpp"
	"src/raycaster.cpp"
	"src/renderer.cpp"
	"src/scene.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)