#pragma once

#ifdef CORRANALYSIS_SHARED
  #ifdef CORRANALYSIS_EXPORTS
    #define CORR_API extern "C" __declspec(dllexport)
  #else
    #define CORR_API extern "C" __declspec(dllimport)
  #endif
#else
  #ifdef __cplusplus
    #define CORR_API extern "C"
  #else
    #define CORR_API
  #endif
#endif

// Обчислює вибіркову коваріацію двох масивів x та y довжини n (повертає NAN при помилці)
CORR_API double covariance(const double* x, const double* y, int n);

// Обчислює лінійний коефіцієнт кореляції Пірсона в межах [-1; 1] (NAN при нульовій дисперсії або помилці)
CORR_API double pearson(const double* x, const double* y, int n);

// Обчислює ранговий коефіцієнт кореляції Спірмена в межах [-1; 1]
CORR_API double spearman(const double* x, const double* y, int n);

// Обчислює симетричну матрицю кореляцій Пірсона розміром vars x vars.
// data — масив довжини vars * n (по рядках: кожен рядок — окрема змінна довжини n).
// outMatrix — попередньо виділений буфер розміром vars * vars.
// Повертає 0 при успіху, -1 при помилці параметрів.
CORR_API int correlationMatrix(const double* data, int vars, int n, double* outMatrix);
