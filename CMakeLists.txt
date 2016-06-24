
cmake_minimum_required(VERSION 3.2)

add_executable(zeropimpl
	main.cpp
	lib.cpp
)

target_compile_options(zeropimpl PRIVATE -std=c++11)
