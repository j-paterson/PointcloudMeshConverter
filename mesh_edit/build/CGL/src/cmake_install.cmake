# Install script for directory: /Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/build/CGL/src/libCGL.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CGL" TYPE FILE FILES
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/CGL.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/vector2D.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/vector3D.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/vector4D.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/matrix3x3.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/matrix4x4.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/quaternion.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/complex.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/color.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/osdtext.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/viewer.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/base64.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/tinyxml2.h"
    "/Users/jpat/Documents/School/Junior2/CS184/final_proj/mesh_edit/CGL/src/renderer.h"
    )
endif()

