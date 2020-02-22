cmake_minimum_required(VERSION 3.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CURSES_NEED_NCURSES True)

file(GLOB SYSTEM_SOURCES system/*.cpp)
add_library(system STATIC ${SYSTEM_SOURCES})
# target_compile_features(system PRIVATE cxx_constexpr)

project(tnl2000 VERSION 0.1.0)
add_executable(tnl2000 main.cpp)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(tnl2000 system)
target_compile_features(tnl2000 PRIVATE cxx_constexpr)
target_link_libraries(tnl2000 Threads::Threads)
target_link_libraries(tnl2000 ${CURSES_LIBRARIES})