#YU Univercity 210214XX Child Kim
#2016년 1학기 SCSC 알고리즘 레포트

cmake_minimum_required(VERSION 3.5)
project(SCSC161)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        unittest.cpp
        binadd.c binadd.h bintree.c bintree.h binstar.c binstar.h binoper.c binoper.h topsort.c topsort.h graphoper.c graphoper.h allcost.c allcost.h)
add_executable(SCSC161 ${SOURCE_FILES})
target_link_libraries(SCSC161 /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)