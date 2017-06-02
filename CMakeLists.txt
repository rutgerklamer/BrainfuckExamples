cmake_minimum_required(VERSION 2.6)
project(PlAINCMAKETEST)

set(CMAKE_CXX_FLAG "-g -Wall")

set(SOURCES
	main.cpp
	)

add_executable(brainfuck ${SOURCES})
