INCLUDE_DIRECTORIES(${ANN_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${NGL_INCLUDE_DIR})
add_executable(
	getNeighborGraph
	getNeighborGraph.cpp
)
target_link_libraries(getNeighborGraph ${ANN_LIBRARY})

INSTALL(TARGETS getNeighborGraph
        ARCHIVE DESTINATION ${DEST}/lib
        LIBRARY DESTINATION ${DEST}/include
        RUNTIME DESTINATION ${DEST}/bin
)

FIND_PATH( QHULL_PATH qdelaunay
           PATHS "qhull" "../qhull" "../qhull/build" "../qhull/bin" "/usr/bin")

IF (QHULL_PATH)
  SET(QHULL_FOUND TRUE)
  MESSAGE(STATUS "Found qdelaunay at : ${QHULL_PATH}")
ELSE()
        MESSAGE(STATUS "Did not find QHULL")
ENDIF(QHULL_PATH)


if(QHULL_FOUND)
	INCLUDE_DIRECTORIES(${NGL_INCLUDE_DIR})
	add_definitions(-DQDELAUNAY_PATH=\"${QHULL_PATH}\")

	add_executable(
		getDelaunay
		getDelaunay.cpp
	)
	target_link_libraries(getDelaunay)
	INSTALL(TARGETS getDelaunay
        	ARCHIVE DESTINATION ${DEST}/lib
        	LIBRARY DESTINATION ${DEST}/include
        	RUNTIME DESTINATION ${DEST}/bin
	)
endif()


