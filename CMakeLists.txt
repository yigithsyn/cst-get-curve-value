cmake_minimum_required(VERSION 2.8.9)


project (cstff)

#Bring the headers, such as Student.h into the project
include_directories(disphelper_081/source)

file(GLOB SOURCES "disphelper_081/source/*.c")
# compile
add_executable(cstff main.cpp ${SOURCES})