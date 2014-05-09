
set(target voronoi)
message(STATUS "Lib ${target}")

#
# External libraries
#

# e.g., find_package(THIRDPARTY REQUIRED)

#
# Includes
#

include_directories(
    # e.g., ${TRDP_INCLUDE_DIR}
)

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Libraries
#

set(libs
    # e.g., ${THIRDPARTY_LIBRARY}
)

#
# Compiler definitions
#

if (OPTION_BUILD_STATIC)
    add_definitions("-DVORONOI_STATIC")
else()
    add_definitions("-DVORONOI_EXPORTS")
endif()

#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(sources
	${source_path}/fortune/Event.cpp
	${source_path}/fortune/BeachLine.cpp
	${source_path}/fortune/Arc.cpp
	${source_path}/fortune/Fortune.cpp
	${source_path}/geometry/Circle.cpp
	${source_path}/geometry/Parabola.cpp
	${source_path}/geometry/ConvexPolygon.cpp
	${source_path}/geometry/Vector.cpp
	${source_path}/geometry/Point.cpp
	${source_path}/geometry/Line.cpp
	${source_path}/geometry/Rectangle.cpp
	${source_path}/VoronoiCell.cpp
	${source_path}/VoronoiDiagram.cpp
	${source_path}/VoronoiEdge.cpp
	${source_path}/VoronoiSite.cpp
)

set(api_includes
	${include_path}/fortune/Arc.h
	${include_path}/fortune/Fortune.h
	${include_path}/fortune/BeachLine.h
	${include_path}/fortune/Event.h
	${include_path}/geometry/Vector.h
	${include_path}/geometry/Parabola.h
	${include_path}/geometry/Point.h
	${include_path}/geometry/ConvexPolygon.h
	${include_path}/geometry/Circle.h
	${include_path}/geometry/Line.h
	${include_path}/geometry/real.h
	${include_path}/geometry/Rectangle.h
	${include_path}/voronoi_api.h
	${include_path}/VoronoiCell.h
	${include_path}/VoronoiDiagram.h
	${include_path}/VoronoiEdge.h
	${include_path}/voronoi.h
	${include_path}/VoronoiSite.h
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${api_includes})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})

#
# Build library
#

if(OPTION_BUILD_STATIC)
    add_library(${target} ${api_includes} ${sources})
else()
    add_library(${target} SHARED ${api_includes} ${sources})
endif()

target_link_libraries(${target} ${libs})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH	            ${include_path})

#
# Deployment
#

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
