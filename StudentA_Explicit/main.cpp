#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

// Оголошення типів покажчиків на функції згідно з Контрактом (без #include "CorrAnalysis.h")
typedef double (*CovarianceFunc)(const double*, const double*, int);
typedef double (*PearsonFunc)(const double*, const double*, int);
typedef double (*SpearmanFunc)(const double*, const double*, int);
typedef int    (*CorrMatrixFunc)(const double*, int, int, double*);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "=== [Етап 3.2] ЯВНЕ зв'язування (Explicit Linking) CorrAnalysis.dll ===\n";
    std::cout << "Виконавець: Студент А (Надійко Роман) | Завантаження через LoadLibrary/GetProcAddress\n\n";

    HMODULE hDll = LoadLibraryA("CorrAnalysis.dll");
    if (!hDll) {
        std::cerr << "[ПОМИЛКА] Не вдалося завантажити CorrAnalysis.dll! Код WinAPI: " << GetLastError() << "\n";
        return 1;
    }
    std::cout << "[OK] Бібліотеку CorrAnalysis.dll успішно завантажено в адресний простір процесу.\n";

    auto fnCov  = reinterpret_cast<CovarianceFunc>(GetProcAddress(hDll, "covariance"));
    auto fnPear = reinterpret_cast<PearsonFunc>(GetProcAddress(hDll, "pearson"));
    auto fnSpea = reinterpret_cast<SpearmanFunc>(GetProcAddress(hDll, "spearman"));
    auto fnMat  = reinterpret_cast<CorrMatrixFunc>(GetProcAddress(hDll, "correlationMatrix"));

    if (!fnCov || !fnPear || !fnSpea || !fnMat) {
        std::cerr << "[ПОМИЛКА] Не знайдено одну або декілька експортованих функцій у DLL!\n";
        FreeLibrary(hDll);
        return 1;
    }
    std::cout << "[OK] Усі 4 адреси функцій успішно отримано через GetProcAddress().\n\n";

    double x[] = { 2.0, 4.0, 6.0, 8.0, 10.0 };
    double y[] = { 3.0, 7.0, 10.0, 15.0, 21.0 };
    int n = 5;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Виклик fnCov(x, y, 5)  = " << fnCov(x, y, n) << "\n";
    std::cout << "Виклик fnPear(x, y, 5) = " << fnPear(x, y, n) << "\n";
    std::cout << "Виклик fnSpea(x, y, 5) = " << fnSpea(x, y, n) << "\n";

    // Перевірка граничного випадку при явному виклику
    double nanCheck = fnPear(nullptr, y, n);
    std::cout << "\nПеревірка Edge Case (nullptr): fnPear(nullptr, y, 5) = " << nanCheck << "\n";

    FreeLibrary(hDll);
    std::cout << "\n[OK] Бібліотеку CorrAnalysis.dll коректно вивантажено через FreeLibrary().\n";
    return 0;
}
