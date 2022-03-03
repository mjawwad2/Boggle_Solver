cmake_minimum_required(VERSION 3.17)
project(Boggle)

set(CMAKE_CXX_STANDARD 14)

# link with lld if available for speed
option(ENABLE_LLD "LLD" ON)
if (ENABLE_LLD)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=lld -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LLD_VERSION)
    if(LLD_VERSION MATCHES "LLD")
        SET(LLD_AVAILABLE ON)
        MESSAGE(STATUS "lld linker available")
    endif()
endif()

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Basic_Boggle_Solver Basic_Boggle_Solver.cpp Boggle.cpp Dictionary.cpp)
add_executable(Basic_Dictionary Basic_Dictionary.cpp Dictionary.cpp)
add_executable(Dictionary_Tests unit_tests/Dictionary_tests.cpp Dictionary.cpp)
add_executable(Boggle_Tests unit_tests/Boggle_tests.cpp Boggle.cpp Dictionary.cpp)

if (APPLE)
    set_property(TARGET Basic_Boggle_Solver PROPERTY CXX_STANDARD 11)
    set_property(TARGET Basic_Dictionary PROPERTY CXX_STANDARD 11)
    set_property(TARGET Dictionary_Tests PROPERTY CXX_STANDARD 11)
    set_property(TARGET Boggle_Tests PROPERTY CXX_STANDARD 11)
endif()