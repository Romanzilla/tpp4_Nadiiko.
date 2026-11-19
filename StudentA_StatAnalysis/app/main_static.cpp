#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include "StatAnalysis.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== [Етап 1] Перевірка СТАТИЧНОЇ бібліотеки StatAnalysis (Варіант 7 - Студент А) ===\n\n";

    double sample[] = { 12.5, 18.0, 14.2, 22.8, 19.5, 15.0, 25.4, 16.6 };
    int n = sizeof(sample) / sizeof(sample[0]);

    std::cout << "Вибірка (n = " << n << "): ";
    for (int i = 0; i < n; ++i) std::cout << sample[i] << (i + 1 < n ? ", " : "\n");

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Середнє арифметичне (mean):      " << mean(sample, n) << "\n";
    std::cout << "Вибіркова дисперсія (variance):  " << variance(sample, n, 1) << "\n";
    std::cout << "Стандартне відхилення (stdDev):  " << stdDev(sample, n, 1) << "\n";
    std::cout << "Медіана (median):                " << median(sample, n) << "\n";

    double q1 = 0.0, q2 = 0.0, q3 = 0.0;
    if (quartiles(sample, n, &q1, &q2, &q3) == 0) {
        std::cout << "Квартилі (Q1, Q2, Q3):           " << q1 << " | " << q2 << " | " << q3 << "\n";
    }

    std::cout << "\n[Перевірка граничних випадків (Edge Cases)]:\n";
    std::cout << "1) nullptr масив -> mean = " << mean(nullptr, 5) << " (очікується nan)\n";
    std::cout << "2) n = 1 для вибіркової дисперсії -> variance = " << variance(sample, 1, 1) << " (очікується nan)\n";
    std::cout << "3) nullptr для вихідних квартилів -> код повернення = " << quartiles(sample, n, nullptr, &q2, &q3) << " (очікується -1)\n";

    return 0;
}
