# Install script for directory: /Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/build/CGL/src/libCGL.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CGL" TYPE FILE FILES
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/CGL.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/vector2D.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/vector3D.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/vector4D.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/matrix3x3.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/matrix4x4.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/quaternion.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/complex.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/color.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/osdtext.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/viewer.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/base64.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/tinyxml2.h"
    "/Users/BryceSchmidtchen/Google Drive/CS184/Final_Project/facemesh/mesh_edit/CGL/src/renderer.h"
    )
endif()

