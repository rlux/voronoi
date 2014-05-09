
######
# This is the find-script for your project/library used by CMake if this project/libary is to be
# included in another project/library.
######
#
# VORONOI_DIR
# VORONOI_FOUND
# VORONOI_LIBRARIES
# VORONOI_INCLUDES

# VORONOI_LIBRARY
# VORONOI_RELEASE
# VORONOI_DEBUG
# VORONOI_INCLUDE_DIR




# Definition of function "find" with two mandatory arguments, "LIB_NAME" and "HEADER".
function (find LIB_NAME HEADER)

    set(HINT_PATHS ${ARGN})

    if (${LIB_NAME} STREQUAL "voronoi")
        set(LIB_NAME_UPPER VORONOI)
        set(LIBNAME voronoi)
    else()
        string(TOUPPER VORONOI_${LIB_NAME} LIB_NAME_UPPER)
        set(LIBNAME ${LIB_NAME})
    endif()

    find_path(
	${LIB_NAME_UPPER}_INCLUDE_DIR
	${HEADER}
        ${ENV_VORONOI_DIR}/include
        ${ENV_VORONOI_DIR}/source/${LIB_NAME}/include
        ${VORONOI_DIR}/include
        ${VORONOI_DIR}/source/${LIB_NAME}/include
        ${ENV_PROGRAMFILES}/voronoi/include
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where ${HEADER} resides"
    )


    find_library(
	${LIB_NAME_UPPER}_LIBRARY_RELEASE
        NAMES ${LIBNAME}
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} library"
    )
    find_library(
	${LIB_NAME_UPPER}_LIBRARY_DEBUG
        NAMES ${LIBNAME}d
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} debug library"
    )
    

    if(${LIB_NAME_UPPER}_LIBRARY_RELEASE AND ${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY "optimized" ${${LIB_NAME_UPPER}_LIBRARY_RELEASE} "debug" ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    elseif(${LIB_NAME_UPPER}_LIBRARY_RELEASE)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_RELEASE})
    elseif(${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    endif()


    set(VORONOI_INCLUDES  ${VORONOI_INCLUDES}  ${${LIB_NAME_UPPER}_INCLUDE_DIR} PARENT_SCOPE)
    set(VORONOI_LIBRARIES ${VORONOI_LIBRARIES} ${${LIB_NAME_UPPER}_LIBRARY} PARENT_SCOPE)

    # DEBUG MESSAGES
#    message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")
#    message("${LIB_NAME_UPPER}_LIBRARY_RELEASE = ${${LIB_NAME_UPPER}_LIBRARY_RELEASE}")
#    message("${LIB_NAME_UPPER}_LIBRARY_DEBUG   = ${${LIB_NAME_UPPER}_LIBRARY_DEBUG}")
#    message("${LIB_NAME_UPPER}_LIBRARY         = ${${LIB_NAME_UPPER}_LIBRARY}")

endfunction(find)








# load standard CMake arguments (c.f. http://stackoverflow.com/questions/7005782/cmake-include-findpackagehandlestandardargs-cmake)
include(FindPackageHandleStandardArgs)

if(CMAKE_CURRENT_LIST_FILE)
    get_filename_component(VORONOI_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif()

file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" ENV_PROGRAMFILES)
file(TO_CMAKE_PATH "$ENV{VORONOI_DIR}" ENV_VORONOI_DIR)

set(LIB_PATHS   
    ${VORONOI_DIR}/build
    ${VORONOI_DIR}/build/Release
    ${VORONOI_DIR}/build/Debug
    ${VORONOI_DIR}/build-release
    ${VORONOI_DIR}/build-debug
    ${VORONOI_DIR}/lib
    ${ENV_VORONOI_DIR}/lib
    ${ENV_PROGRAMFILES}/voronoi/lib
    /usr/lib
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    /usr/lib64
    /usr/local/lib64
    /sw/lib64
    /opt/local/lib64
)


# Find libraries
find(fiblib fiblib/fiblib_api.h ${LIB_PATHS})


# DEBUG
#message("VORONOI_INCLUDES  = ${VORONOI_INCLUDES}")
#message("VORONOI_LIBRARIES = ${VORONOI_LIBRARIES}")

find_package_handle_standard_args(VORONOI DEFAULT_MSG VORONOI_LIBRARIES VORONOI_INCLUDES)
mark_as_advanced(VORONOI_FOUND)
