# CMakeList.txt : CMake project for lamina, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project ("lamina" LANGUAGES CXX)

# Add source to this project's executable.

add_subdirectory("lamina_source")
add_subdirectory("tests")



# TODO: Add tests and install targets if needed.
