# written by Ryan Puhalovich (rpuhalovich, 1064808)

cmake_minimum_required(VERSION 3.17.1)
project(LearningCMake CXX)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

set(EXTERN_DIR ${CMAKE_SOURCE_DIR}/extern)

# --- src ---
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE src ${SRC_DIR}/*.cpp ${SRC_DIR}/*.hpp ${SRC_DIR}/*.h ${SRC_DIR}/*.shader)

# --- glad ---
add_library(glad "${EXTERN_DIR}/glad/src/glad.c")
set(inc ${inc} ${EXTERN_DIR}/glad/include)
set(lib ${lib} glad)

# --- glfw ---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/glfw)

set(lib ${lib} glfw)

# --- exe ---
add_executable(${PROJECT_NAME} ${src})
include_directories(${PROJECT_NAME} ${inc})

if(MSVC)
  target_link_libraries(${PROJECT_NAME} ${lib} opengl32) # how do I make tabs 4 spaces?!
endif()

if(APPLE)
  target_link_libraries(${PROJECT_NAME} ${lib} "-framework OpenGL")
endif()

source_group(TREE ${SRC_DIR} FILES ${src})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(
  glad
  glfw
  uninstall
  PROPERTIES FOLDER "Libraries")
