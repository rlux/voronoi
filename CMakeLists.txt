cmake_minimum_required(VERSION 2.6)

project(voronoi)

option(BUILD_WITH_DEMO "Compile Voronoi++ with a demo using Qt" OFF)

set(target voronoi)

include_directories("include")

set(sources
	src/geometry/Point.cpp
	src/geometry/Line.cpp
	src/geometry/Circle.cpp
	src/geometry/Triangle.cpp
	src/geometry/Rectangle.cpp
	src/geometry/Polygon.cpp
	
	src/VoronoiCell.cpp
	src/VoronoiDiagram.cpp
	src/VoronoiEdge.cpp
	src/VoronoiSite.cpp
	
	src/fortune/Arc.cpp
	src/fortune/BeachLine.cpp
	src/fortune/Event.cpp
	src/fortune/Fortune.cpp
)

add_library(${target} SHARED ${sources})

if (BUILD_WITH_DEMO)
	add_subdirectory("demo")
endif (BUILD_WITH_DEMO)