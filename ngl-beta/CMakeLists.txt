PROJECT(EmptyRegionGraphs)

cmake_minimum_required(VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-stdlib=libstdc++")

#SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
SET (DEST ${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_MODULE_PATH "../config")
IF ( CMAKE_BUILD_TYPE STREQUAL "")
  SET(CMAKE_BUILD_TYPE "Release")
ENDIF (CMAKE_BUILD_TYPE STREQUAL "")

FIND_PATH( NGL_INCLUDE_DIR ngl.h
           PATHS "include" "../include")


INCLUDE(./config/FindANN.cmake)
#FIND_PACKAGE(ANN REQUIRED)
if(ANN_FOUND)
        MESSAGE(STATUS "Using ANN : ${ANN_INCLUDE_DIR}")
        MESSAGE(STATUS "  Library : ${ANN_LIBRARY}")
else()
        MESSAGE(FATAL_ERROR "Did not find ANN")
endif()

FIND_PACKAGE(OpenGL)
FIND_PACKAGE(GLUT)

INCLUDE(./config/FindCairo.cmake)
#FIND_PACKAGE(Cairo REQUIRED)

if(CAIRO_FOUND)
        MESSAGE(STATUS "Using Cairo ${CAIRO_VERSION}. Include : ${CAIRO_INCLUDE_DIR}")
        MESSAGE(STATUS "Library: ${CAIRO_LIBRARIES}")
endif()

add_subdirectory(binsrc)
add_subdirectory(vis)


