# - Try to find ANN
# Once done this will define
#  
#  ANN_FOUND        - system has ANN
#  ANN_INCLUDE_DIR  - the ANN include directory
#  ANN_LIBRARY      - Link these to use ANN
#   

IF (ANN_INCLUDE_DIRS)
  # Already in cache, be silent
  SET(ANN_FIND_QUIETLY TRUE)
ENDIF (ANN_INCLUDE_DIRS)

FIND_PATH( ANN_INCLUDE_DIR ANN/ANN.h
           PATHS "ann_1.1.2/include" "/usr/include" "../ann_1.1.2/include" "C:/libs/ANN/include")

if( WIN32 )

 message(status "ANN library finder not tested for windows yet!")
 
 FIND_LIBRARY( ANN_LIBRARY
               NAMES ann.lib
               PATHS "C:/libs/ANN/lib")
               
 # Store the library dir. May be used for linking to dll!
 GET_FILENAME_COMPONENT( ANN_LIBRARY_DIR ${ANN_LIBRARY} PATH )
 
else (WIN32)

FIND_LIBRARY( ANN_LIBRARY
               NAMES ann ANN
               PATHS /lib /usr/lib /usr/lib64 /usr/local/lib ann_1.1.2/lib ../ann_1.1.2/lib)

endif( WIN32)


IF (ANN_INCLUDE_DIR AND ANN_LIBRARY)
  SET(ANN_FOUND TRUE)
ELSE (ANN_INCLUDE_DIR AND ANN_LIBRARY)
  SET( ANN_FOUND FALSE )
ENDIF (ANN_INCLUDE_DIR AND ANN_LIBRARY)
