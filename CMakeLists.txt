cmake_minimum_required(VERSION 2.6)

project(voronoi)

option(BUILD_WITH_DEMO "Compile Voronoi++ with a demo using Qt" OFF)
option(BUILD_SHARED "Compile as shared library" ON)

set(target voronoi)

include_directories("include")

set(api_include
        include/geometry/Point.h
        include/geometry/Vector.h
        include/geometry/Line.h
        include/geometry/Circle.h
        include/geometry/Rectangle.h
        include/geometry/Parabola.h
        include/geometry/ConvexPolygon.h
        include/geometry/real.h

        include/VoronoiCell.h
        include/VoronoiDiagram.h
        include/VoronoiEdge.h
        include/VoronoiSite.h
        include/voronoi.h
        include/voronoi_api.h

        include/fortune/Arc.h
        include/fortune/BeachLine.h
        include/fortune/Event.h
        include/fortune/Fortune.h
)

set(sources
	src/geometry/Point.cpp
	src/geometry/Vector.cpp
	src/geometry/Line.cpp
	src/geometry/Circle.cpp
	src/geometry/Rectangle.cpp
	src/geometry/Parabola.cpp
	src/geometry/ConvexPolygon.cpp
	
	src/VoronoiCell.cpp
	src/VoronoiDiagram.cpp
	src/VoronoiEdge.cpp
	src/VoronoiSite.cpp
	
	src/fortune/Arc.cpp
	src/fortune/BeachLine.cpp
	src/fortune/Event.cpp
	src/fortune/Fortune.cpp
)

if (BUILD_SHARED)
    add_definitions(-DVORONOI_STATIC)
    add_library(${target} SHARED ${sources} ${api_include})
else(BUILD_SHARED)
    add_definitions(-DVORONOI_EXPORTS)
    add_library(${target} STATIC ${sources} ${api_include})
endif(BUILD_SHARED)

if (BUILD_WITH_DEMO)
	add_subdirectory("demo")
endif (BUILD_WITH_DEMO)
