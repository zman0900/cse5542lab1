cmake_minimum_required (VERSION 2.6)
project (cse5542lab1)
add_executable (lab1 lab1.cpp GlGlut.cpp)
target_link_libraries (lab1 glut GL)
