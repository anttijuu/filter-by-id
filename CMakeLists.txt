cmake_minimum_required(VERSION 3.12)
project(FilterStudentsById)
include(GNUInstallDirs)
set(APP_NAME filterstudents)

add_executable(${APP_NAME} main.cpp )
set_target_properties(${APP_NAME} PROPERTIES CXX_STANDARD 14)

