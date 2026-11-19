#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include "CorrAnalysis.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== [Етап 3.1] НЕЯВНЕ зв'язування (Implicit Linking) CorrAnalysis.dll ===\n";
    std::cout << "Виконавець: Студент А (Надійко Роман) | Бібліотека партнера: CorrAnalysis\n\n";

    double hours[]  = { 1.0, 2.0, 3.5, 4.0, 5.5, 7.0, 8.0 };
    double scores[] = { 52.0, 58.0, 67.0, 71.0, 82.0, 91.0, 96.0 };
    int n = 7;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Коваріація (covariance):       " << covariance(hours, scores, n) << "\n";
    std::cout << "Кореляція Пірсона (pearson):   " << pearson(hours, scores, n) << "\n";
    std::cout << "Кореляція Спірмена (spearman): " << spearman(hours, scores, n) << "\n";

    double dataset[3 * 5] = {
        1.0, 2.0, 3.0, 4.0, 5.0,
        2.1, 3.9, 6.2, 8.1, 9.8,
        9.0, 7.2, 5.1, 3.0, 1.2
    };
    double corrMat[9]{};
    int status = correlationMatrix(dataset, 3, 5, corrMat);
    std::cout << "\nСтатус correlationMatrix: " << status << "\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << std::setw(9) << corrMat[i * 3 + j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n--- Тестування граничних випадків (Edge Cases) контракту партнера ---\n";
    double constArr[] = { 5.0, 5.0, 5.0, 5.0 };
    double normArr[]  = { 1.0, 2.0, 3.0, 4.0 };
    std::cout << "1) Передача nullptr: pearson(nullptr, y, 4) = " << pearson(nullptr, normArr, 4) << "\n";
    std::cout << "2) Розмір масиву n = 1 (< 2): covariance(x, y, 1) = " << covariance(normArr, normArr, 1) << "\n";
    std::cout << "3) Нульова дисперсія (константний ряд): pearson(const, norm, 4) = " << pearson(constArr, normArr, 4) << "\n";
    std::cout << "4) Некоректний буфер матриці (nullptr): code = " << correlationMatrix(dataset, 3, 5, nullptr) << "\n";

    return 0;
}
