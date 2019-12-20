cmake_minimum_required(VERSION 3.12)
project(FilterDataById)
include(GNUInstallDirs)
set(APP_NAME filter)

add_executable(${APP_NAME} main.cpp )
set_target_properties(${APP_NAME} PROPERTIES CXX_STANDARD 17)

