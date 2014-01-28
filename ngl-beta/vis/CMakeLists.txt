INCLUDE_DIRECTORIES(${ANN_INCLUDE_DIR})
if(CAIRO_FOUND)
	INCLUDE_DIRECTORIES(${CAIRO_INCLUDE_DIR})
	INCLUDE_DIRECTORIES(${NGL_INCLUDE_DIR})

	add_executable(
		drawEmptyRegion
		drawEmptyRegion.cpp
	)
	target_link_libraries(drawEmptyRegion ${CAIRO_LIBRARIES} ${ANN_LIBRARY})
	INSTALL(TARGETS drawEmptyRegion
        	ARCHIVE DESTINATION ${DEST}/lib
        	LIBRARY DESTINATION ${DEST}/include
        	RUNTIME DESTINATION ${DEST}/bin
	)
endif()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 
	# Mac OS X specific code
	SET(OperatingSystem "Mac OS X")
	add_definitions(-DMAC_OSX)
	MESSAGE(STATUS "Compiling for Mac OS X")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

INCLUDE_DIRECTORIES(${NGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})
add_executable(
	interactiveGraph
	interactiveGraph.cpp
)
target_link_libraries(interactiveGraph ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${ANN_LIBRARY})

INSTALL(TARGETS interactiveGraph
        ARCHIVE DESTINATION ${DEST}/lib
        LIBRARY DESTINATION ${DEST}/include
        RUNTIME DESTINATION ${DEST}/bin
)


