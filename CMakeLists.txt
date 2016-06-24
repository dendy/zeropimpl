
cmake_minimum_required(VERSION 3.2)

add_executable(zeropimpl
	abc.cpp
	main.cpp
	lib.cpp
	test_pimpl.cpp
	test_zeropimpl.cpp
)

target_compile_options(zeropimpl PRIVATE -std=c++11)
