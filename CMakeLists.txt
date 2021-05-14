# written by Ryan Puhalovich (rpuhalovich, 1064808)

cmake_minimum_required(VERSION 3.17.1)
project(LearningCMake CXX)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

# --- glfw ---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/glfw)

set(libs glfw)

# --- src ---
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE src ${SRC_DIR}/*.cpp ${SRC_DIR}/*.h)

# --- exe ---
add_executable(${PROJECT_NAME} ${src})
source_group(TREE ${SRC_DIR} FILES ${src})

if(MSVC)
  target_link_libraries(${PROJECT_NAME} ${libs} opengl)
endif()

if (APPLE)
  target_link_libraries(${PROJECT_NAME} ${libs} "-framework OpenGL")
endif()
