cmake_minimum_required(VERSION 3.23)
project(AED_Schedule)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(AED_Schedule
        src/Block.cpp
        src/Block.h
        src/Class.cpp
        src/Class.h
        src/Helpy.cpp
        src/Helpy.h
        src/main.cpp
        src/Request.cpp
        src/Request.h
        src/Schedule.cpp
        src/Schedule.h
        src/Student.cpp
        src/Student.h
        src/UC.cpp
        src/UC.h)
