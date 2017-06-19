project(displayImage)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

ADD_SUBDIRECTORY(opencv.cmake) 
SET_TARGET_PROPERTIES(displayImage PROPERTIES RUNTIME_OUTPUT_DIRECTORY> "${PROJECT_SOURCE_DIR}/lib") 
add_executable(${PROJECT_NAME} ${SRC_LIST})