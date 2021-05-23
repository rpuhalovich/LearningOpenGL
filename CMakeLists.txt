# written by Ryan Puhalovich - github.com/rpuhalovich

cmake_minimum_required(VERSION 3.17.1)
project(LearningOpenGL CXX)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER Predefined)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEB")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DREL")

# --- src ------------------------------------------
set(SHADER_DIR "${CMAKE_SOURCE_DIR}/src/shader/")
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE src 
  ${SRC_DIR}/*.cpp
  ${SRC_DIR}/*.hpp
  ${SRC_DIR}/*.h
  ${SRC_DIR}/*.shader
  ${SRC_DIR}/*.vert
  ${SRC_DIR}/*.frag
)

set(tgt_inc
  ${SRC_DIR}/gfx
  ${SRC_DIR}/shader
)

# --- lib ------------------------------------------
set(EXTERN_DIR ${CMAKE_SOURCE_DIR}/extern)

# glad
add_library(glad "${EXTERN_DIR}/glad/src/glad.c")
set(inc ${inc} ${EXTERN_DIR}/glad/include)
set(lib ${lib} glad)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/glfw)
set(lib ${lib} glfw)

include_directories(${inc})

# --- exe ------------------------------------------
add_executable(${PROJECT_NAME} ${src})
target_compile_definitions(${PROJECT_NAME} PUBLIC SHADER_DIR="${SHADER_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC ${tgt_inc})

if(MSVC)
  target_link_libraries(${PROJECT_NAME} ${lib} opengl32)
elseif(APPLE)
  add_compile_definitions(GL_SILENCE_DEPRECATION)
  target_link_libraries(${PROJECT_NAME} ${lib} "-framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa")
endif()

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(
  glad
  glfw
  uninstall
  PROPERTIES FOLDER "Libraries")
