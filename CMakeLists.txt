cmake_minimum_required(VERSION 3.27.0)
project(QR-Code-Generator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(QR-Code-Generator main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
