cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(CMoss VERSION 0.0.1 LANGUAGES C)

set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

include(src/Moss.cmake)
