#pragma once

#ifdef STATANALYSIS_SHARED
  #ifdef STATANALYSIS_EXPORTS
    #define STAT_API extern "C" __declspec(dllexport)
  #else
    #define STAT_API extern "C" __declspec(dllimport)
  #endif
#else
  #ifdef __cplusplus
    #define STAT_API extern "C"
  #else
    #define STAT_API
  #endif
#endif

// Обчислює середнє арифметичне вибірки (повертає NAN при некоректних даних)
STAT_API double mean(const double* data, int n);

// Обчислює дисперсію вибірки (isSample != 0 -> ділення на n-1; isSample == 0 -> ділення на n)
STAT_API double variance(const double* data, int n, int isSample);

// Обчислює стандартне відхилення (корінь з дисперсії)
STAT_API double stdDev(const double* data, int n, int isSample);

// Обчислює медіану вибірки (не змінює вхідний масив)
STAT_API double median(const double* data, int n);

// Обчислює перший (Q1), другий (Q2/медіана) та третій (Q3) квартилі.
// Повертає 0 при успіху, -1 при помилці вхідних параметрів.
STAT_API int quartiles(const double* data, int n, double* q1, double* q2, double* q3);
