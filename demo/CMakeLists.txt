cmake_minimum_required(VERSION 2.6)

project(demo)

set(target demo)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

include_directories("../include")

set(sources
	main.cpp
	
	mainwindow.cpp
)

QT4_WRAP_CPP(moc_sources
	mainwindow.h
)

add_executable(${target} ${sources} ${moc_sources})

target_link_libraries(${target} voronoi ${QT_LIBRARIES})
