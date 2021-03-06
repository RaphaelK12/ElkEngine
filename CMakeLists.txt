# Some functions require a certain version of cmake (for example file GLOB )
cmake_minimum_required(VERSION 3.1)

# Create the project
set(PROJECT_NAME ELK)
set(CMAKE_MACOSX_RPATH 1)
project(${PROJECT_NAME})

# Add the external module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/Modules)

# Find external packages
find_package(OPENGL REQUIRED)
find_package(GLEW 	REQUIRED)
find_package(GLM 	  REQUIRED)
if(APPLE)
  find_library(OPENGL_FRAMEWORK OpenGL)
  find_library(COCOA_FRAMEWORK Cocoa)
endif(APPLE)

# Add include directories
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

# Our own include directory
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE PATH "${PROJECT_NAME} include directories")
include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-g")

# Creating our own ELK library
file(GLOB ${PROJECT_NAME}_SOURCES
  ${PROJECT_SOURCE_DIR}/src/core/*.cpp
  ${PROJECT_SOURCE_DIR}/src/object_extensions/*.cpp)
file(GLOB ${PROJECT_NAME}_HEADERS
  ${PROJECT_SOURCE_DIR}/include/elk/core/*.h
  ${PROJECT_SOURCE_DIR}/include/elk/object_extensions/*.h)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
set(${PROJECT_NAME}_LIBRARIES ${PROJECT_NAME} CACHE FILEPATH "${PROJECT_NAME} libraries")

# Link other libraries
target_link_libraries(
	${PROJECT_NAME}
	${OPENGL_LIBRARIES}
	${OPENGL_glu_LIBRARY}
	${GLEW_LIBRARIES})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-std=c++14")

target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_DIR="${PROJECT_SOURCE_DIR}")

# Compile options
option(${PROJECT_NAME}_BUILD_EXAMPLES "Build all examples." OFF)
option(${PROJECT_NAME}_USE_GLFW "Use GLFW." OFF)
option(${PROJECT_NAME}_USE_ASSIMP "Use Assimp." OFF)
option(${PROJECT_NAME}_USE_DEVIL "Use DevIL." OFF)
option(${PROJECT_NAME}_USE_FREEIMAGE "Use Freeimage." OFF)

######################
# External Libraries #
######################
if (${PROJECT_NAME}_USE_GLFW)
  find_package(GLFW3 REQUIRED)
  include_directories(${GLFW_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
  target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include/elk/window/application_window_glfw.h
    ${PROJECT_SOURCE_DIR}/src/window/application_window_glfw.cpp)
    #target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_USE_GLFW = "1")
endif()

if (${PROJECT_NAME}_USE_ASSIMP)
  find_package(ASSIMP REQUIRED)
  include_directories(${ASSIMP_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})
  target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include/elk/asset_loading/asset_loading_assimp.h
    ${PROJECT_SOURCE_DIR}/src/asset_loading/asset_loading_assimp.cpp)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_USE_ASSIMP)
endif()

if (${PROJECT_NAME}_USE_DEVIL)
  find_package(DEVIL REQUIRED)
  include_directories(${IL_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${IL_LIBRARIES})
  target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include/elk/texture_loading/texture_loading_devil.h
    ${PROJECT_SOURCE_DIR}/src/texture_loading/texture_loading_devil.cpp)
endif()

if (${PROJECT_NAME}_USE_FREEIMAGE)
  find_package(FREEIMAGE REQUIRED)
  include_directories(${FREEIMAGE_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${FREEIMAGE_LIBRARIES})
  target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include/elk/texture_loading/texture_loading_freeimage.h
    ${PROJECT_SOURCE_DIR}/src/texture_loading/texture_loading_freeimage.cpp)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_USE_FREEIMAGE)
endif()

############
# Examples #
############
if (${PROJECT_NAME}_BUILD_EXAMPLES)
  if (${PROJECT_NAME}_USE_GLFW)
    file(GLOB EXAMPLE1_SOURCE ${PROJECT_SOURCE_DIR}/examples/glfw_example.cpp)
    add_executable(glfw_example ${EXAMPLE1_SOURCE})
    target_link_libraries(
      glfw_example
      ${PROJECT_NAME}
    )
    set_target_properties(glfw_example PROPERTIES COMPILE_FLAGS "-std=c++14")
  else()
    message(WARNING "Unable to build GLFW example, enable ${PROJECT_NAME}_USE_GLFW!")
  endif()
endif()