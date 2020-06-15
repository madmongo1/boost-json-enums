cmake_minimum_required(VERSION 3.15)

include(cmake/HunterGate.cmake)

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.257.tar.gz"
        SHA1 "52203b35dfc2f975f4c22fc89f055476726e4288"
        LOCAL
)

project(BestSoftphoneProblem)

hunter_add_package(Boost COMPONENTS system)
find_package(Boost CONFIG COMPONENTS system)

add_subdirectory(subs/json)

find_package(Threads)

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(check ${src_files})
target_include_directories(check PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(check PRIVATE Boost::system Threads::Threads boost_json)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(check PRIVATE -Werror -Wall -Wextra -pedantic)
endif()