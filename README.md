Voronoi++
=======

Voronoi++ is a C++ library to calculate voronoi diagrams for a given set of points.

Content
------------

 * [Requirements](#requirements)
 * [Building](#building)
 * [License](#license)

Requirements
---------------------

 * [gcc 4.7](http://gcc.gnu.org/)
 * [CMake 2.8.12](http://www.cmake.org/)
 * [Qt5](http://qt-project.org/) (for example)
 
Building
------------------------------------------

	> mkdir build && cd build
	> cmake ..
	> make

If you also want to compile the demo program, replace the second command with the following:

	> cmake .. -DBUILD_WITH_EXAMPLE=true
    
License
-----------

Voronoi++ is licensed under the LPGL-3.
