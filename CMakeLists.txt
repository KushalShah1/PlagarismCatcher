cmake_minimum_required(VERSION 3.14)
project(Plagarism_Catcher)

set(CMAKE_CXX_STANDARD 14)

add_executable(Plagarism_Catcher main.cpp sm_doc_set HashTable.cpp HashTable.h)