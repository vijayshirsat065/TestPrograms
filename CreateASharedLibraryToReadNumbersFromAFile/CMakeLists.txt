cmake_minimum_required(VERSION 3.13)

file(GLOB sources *.h *.c *.cxx *.cpp *.hxx)
add_executable(CreateASharedLibraryToReadNumbersFromAFile ${sources})