cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(mox.node)

#
# -- Check Input variables
#
if(OCC_ROOT-NOTFOUND)
  message(SEND_ERROR "OCC_ROOT is not defined")
endif()

set(OCC_INC_DIR "${OCC_ROOT}/include/opencascade")
set(OCC_LIB_DIR "${OCC_ROOT}/lib")

#
# -- Check dependencies
#
find_path(NODE_INC_DIR node_buffer.h HINTS /usr/local/include/node)

if(NODE_INC_DIR-NOTFOUND)
  message(SEND_ERROR "Node.js header files not found")                                                                          
endif()  

#
# -- Flags
#
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support")
endif()

add_definitions(-Wall -fPIC)

#
# -- Define directories and file variable
#

INCLUDE_DIRECTORIES(
  ${OCC_INC_DIR}
  ${NODE_INC_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

LINK_DIRECTORIES(
  ${OCC_LIB_DIR}
)

file(GLOB_RECURSE SRC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB_RECURSE MARKDOWN_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/*.md)

set(OCC_LIBS
  FWOSPlugin
  TKBO
  TKBRep
  TKBin
  TKBinL
  TKBinTObj
  TKBinXCAF
  TKBool
  TKCAF
  TKCDF
  TKDCAF
  TKDraw
  TKFeat
  TKFillet
  TKG2d
  TKG3d
  TKGeomAlgo
  TKGeomBase
  TKHLR
  TKIGES
  TKLCAF
  TKMath
  TKMesh
  TKMeshVS
  TKOffset
  TKOpenGl
  TKPrim
  TKQADraw
  TKSTEP
  TKSTEP209
  TKSTEPAttr
  TKSTEPBase
  TKSTL
  TKService
  TKShHealing
  TKStd
  TKStdL
  TKTObj
  TKTObjDRAW
  TKTopAlgo
  TKTopTest
  TKV3d
  TKVCAF
  TKVRML
  TKViewerTest
  TKXCAF
  TKXDEDRAW
  TKXDEIGES
  TKXDESTEP
  TKXMesh
  TKXSBase
  TKXSDRAW
  TKXml
  TKXmlL
  TKXmlTObj
  TKXmlXCAF
  TKernel
)

#
# -- Target
#

add_library(${PROJECT_NAME}
  ${SRC_LIST} ${INC_LIST} ${MARKDOWN_LIST})

target_link_libraries(${PROJECT_NAME}
  ${OCC_LIBS})

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  PREFIX ""
  SUFFIX ""
  OUTPUT_NAME ${PROJECT_NAME}
)
