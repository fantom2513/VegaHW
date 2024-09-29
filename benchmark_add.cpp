//
// Created by fanto on 29.09.2024.
//
#include <benchmark/benchmark.h>
#include "my_add.hpp"

// Бенчмарк для функции my_add
static void BM_my_add(benchmark::State& state) {
    for (auto _ : state) {
        my_add(10, 20); // Пример вызова функции для бенчмарка
    }
}
BENCHMARK(BM_my_add);

BENCHMARK_MAIN();