# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.6.0)
project("CEnginePlayGround")
SET (CMAKE_CXX_STANDARD 11)
add_definitions(-std=c++17)
set(WINSAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CENGINE_SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../cell)
set(ST3D_DEPDIR ${WINSAMPLE_DIR}/../deps/)
set(CMATHI_DIR ${WINSAMPLE_DIR}/../math/)
set(CUTILITY_DIR ${WINSAMPLE_DIR}/../utility/)

if(MSVC)
     # Disable annoying MSVC warnings (all targets)
  add_definitions(/D "_CRT_SECURE_NO_WARNINGS")

  # Parallel build on MSVC (all targets)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

  if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")

    # Disable Eigen vectorization for Windows 32 bit builds (issues with unaligned access segfaults)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DNANOGUI_EIGEN_DONT_ALIGN")
  endif()
endif()

add_library( libassimp STATIC IMPORTED )
add_library( libz STATIC IMPORTED)
add_library(libglfw3 STATIC IMPORTED)
set_target_properties( libassimp  PROPERTIES IMPORTED_LOCATION  ${ST3D_DEPDIR}/assimp/lib/windows-x86/assimp-vc141-mt.lib )
set_target_properties( libz  PROPERTIES IMPORTED_LOCATION  ${ST3D_DEPDIR}/assimp/lib/windows-x86/zlibstatic.lib )
set_target_properties( libglfw3  PROPERTIES IMPORTED_LOCATION  ${ST3D_DEPDIR}/GLFW/libs/glfw3.lib )

include(${WINSAMPLE_DIR}/../CMakelists.txt)

target_link_libraries(cengine libz libassimp libglfw3)


add_library(app STATIC
			${WINSAMPLE_DIR}/scenes/pbr_test.cpp
			${WINSAMPLE_DIR}/scenes/pbr_test.h
			#${WINSAMPLE_DIR}/scenes/base_sample.hpp
			#${WINSAMPLE_DIR}/scenes/base_sample.cpp
)
target_link_libraries(app cengine)

add_executable(rendering_sample
            ${WINSAMPLE_DIR}/samples/rendering_sample.cpp
)
target_link_libraries(rendering_sample app)


add_executable(animation_sample
            ${WINSAMPLE_DIR}/samples/animation_sample.cpp
)
target_link_libraries(animation_sample app)
add_executable(frameGraph_sample
            ${WINSAMPLE_DIR}/samples/frameGraph_sample.cpp
)
target_link_libraries(frameGraph_sample app)





