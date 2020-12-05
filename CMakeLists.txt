cmake_minimum_required(VERSION 3.7)
project(benchmarks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -march=native")

find_program(FAUST_PROGRAM "faust")

find_package(PkgConfig REQUIRED)
pkg_check_modules(Benchmark "benchmark" REQUIRED IMPORTED_TARGET)

add_custom_command(
  OUTPUT "${CMAKE_SOURCE_DIR}/sources/resonator.cpp"
  COMMAND "${FAUST_PROGRAM}" -cn Resonator -os -o "${CMAKE_SOURCE_DIR}/sources/resonator.cpp" -a "${CMAKE_SOURCE_DIR}/sources/resonator.cxx" "${CMAKE_SOURCE_DIR}/sources/resonator.dsp"
  DEPENDS "${CMAKE_SOURCE_DIR}/sources/resonator.dsp" "${CMAKE_SOURCE_DIR}/sources/resonator.cxx")

add_executable(strings_benchmark
  sources/resonator.cpp)
target_link_libraries(strings_benchmark
  PRIVATE PkgConfig::Benchmark)
