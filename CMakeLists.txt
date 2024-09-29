cmake_minimum_required(VERSION 3.14)
project(sample_cpp_project)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Основной исполняемый файл
add_executable(main main.cpp src/my_add.cpp)

# Подключение Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests test_add.cpp src/my_add.cpp)
target_link_libraries(tests gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)

# Подключение Google Benchmark
FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.6.1
)
FetchContent_MakeAvailable(googlebenchmark)

# Создание бенчмарка
add_executable(benchmark_add benchmark_add.cpp src/my_add.cpp)
target_link_libraries(benchmark_add benchmark::benchmark)

# Подключение Doxygen для генерации документации
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Проверяем, что конфигурационный файл существует
    if(EXISTS ${DOXYGEN_IN})
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        add_custom_target(doc ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
    else()
        message(WARNING "Doxyfile not found. Documentation will not be generated.")
    endif()
endif()
