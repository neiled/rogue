# Install script for directory: /Users/cdcorrea/Research/ngl/qhull

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/Users/cdcorrea/Research/ngl/qhull/build/libqhullcpp.a")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libqhullcpp.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libqhullcpp.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}/usr/local/lib/libqhullcpp.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/Users/cdcorrea/Research/ngl/qhull/build/libqhullstatic.a")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libqhullstatic.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libqhullstatic.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}/usr/local/lib/libqhullstatic.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE STATIC_LIBRARY FILES "/Users/cdcorrea/Research/ngl/qhull/build/libqhullstatic_p.a")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libqhullstatic_p.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libqhullstatic_p.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}/usr/local/lib/libqhullstatic_p.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES
    "/Users/cdcorrea/Research/ngl/qhull/build/libqhull.6.dylib"
    "/Users/cdcorrea/Research/ngl/qhull/build/libqhull.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}/usr/local/lib/libqhull.6.dylib"
      "$ENV{DESTDIR}/usr/local/lib/libqhull.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/libqhull.6.dylib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES
    "/Users/cdcorrea/Research/ngl/qhull/build/libqhull_p.6.dylib"
    "/Users/cdcorrea/Research/ngl/qhull/build/libqhull_p.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}/usr/local/lib/libqhull_p.6.dylib"
      "$ENV{DESTDIR}/usr/local/lib/libqhull_p.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "/usr/local/lib/libqhull_p.6.dylib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/cdcorrea/Research/ngl/qhull/build/qhull")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/qhull" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/qhull")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/qhull")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/cdcorrea/Research/ngl/qhull/build/rbox")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/rbox" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/rbox")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/rbox")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/cdcorrea/Research/ngl/qhull/build/qconvex")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/qconvex" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/qconvex")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/qconvex")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/cdcorrea/Research/ngl/qhull/build/qdelaunay")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/qdelaunay" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/qdelaunay")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/qdelaunay")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/cdcorrea/Research/ngl/qhull/build/qvoronoi")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/qvoronoi" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/qvoronoi")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/qvoronoi")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/Users/cdcorrea/Research/ngl/qhull/build/qhalf")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/qhalf" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/qhalf")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/qhalf")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/include/libqhull" TYPE FILE FILES
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/libqhull.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/geom.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/io.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/mem.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/merge.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/poly.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qhull_a.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qset.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/random.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/stat.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/user.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/include/libqhull" TYPE FILE FILES
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/index.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-geom.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-globa.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-io.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-mem.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-merge.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-poly.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-qhull.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-set.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-stat.htm"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhull/qh-user.htm"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/include/libqhullcpp" TYPE FILE FILES
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/Coordinates.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/functionObjects.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/PointCoordinates.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/Qhull.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullError.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullFacet.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullFacetList.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullFacetSet.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullHyperplane.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullIterator.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullLinkedList.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullPoint.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullPoints.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullPointSet.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullQh.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullRidge.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullSet.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullSets.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullStat.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullVertex.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/QhullVertexSet.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/RboxPoints.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/RoadError.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/RoadLogEvent.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/libqhullcpp/UsingLibQhull.h"
    "/Users/cdcorrea/Research/ngl/qhull/src/qhulltest/RoadTest.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/share/man/man1" TYPE FILE RENAME "qhull.1" FILES "/Users/cdcorrea/Research/ngl/qhull/html/qhull.man")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/share/man/man1" TYPE FILE RENAME "rbox.1" FILES "/Users/cdcorrea/Research/ngl/qhull/html/rbox.man")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/share/doc/qhull" TYPE FILE FILES
    "/Users/cdcorrea/Research/ngl/qhull/README.txt"
    "/Users/cdcorrea/Research/ngl/qhull/REGISTER.txt"
    "/Users/cdcorrea/Research/ngl/qhull/Announce.txt"
    "/Users/cdcorrea/Research/ngl/qhull/COPYING.txt"
    "/Users/cdcorrea/Research/ngl/qhull/index.htm"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/usr/local/share/doc/qhull" TYPE DIRECTORY FILES "/Users/cdcorrea/Research/ngl/qhull/html/")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/cdcorrea/Research/ngl/qhull/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/cdcorrea/Research/ngl/qhull/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
