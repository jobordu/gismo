 ### CMakeLists.txt ---
## 
## Author: Angelos Mantzaflaris 
## Copyright (C) 2012 - RICAM-Linz.
######################################################################

## #################################################################
## Collect Headers
## #################################################################

set(${PROJECT_NAME}_externals "${CMAKE_CURRENT_SOURCE_DIR}"
    CACHE INTERNAL "Externals directory")

add_subdirectory(zlib)

if(GISMO_BUILD_CPPLOT)
#add_subdirectory(boost)
add_subdirectory(cpplot)
endif(GISMO_BUILD_CPPLOT)

#add_subdirectory(Eigen)
#add_subdirectory(rapidxml)


#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
