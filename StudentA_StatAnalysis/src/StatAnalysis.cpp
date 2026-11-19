#include "StatAnalysis.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

static bool isValidInput(const double* data, int n) {
    if (data == nullptr || n <= 0) return false;
    for (int i = 0; i < n; ++i) {
        if (std::isnan(data[i]) || std::isinf(data[i])) return false;
    }
    return true;
}

static double percentileSorted(const std::vector<double>& sorted, double p) {
    int n = static_cast<int>(sorted.size());
    if (n == 1) return sorted[0];
    double pos = p * (n - 1);
    int idx = static_cast<int>(std::floor(pos));
    double frac = pos - idx;
    if (idx + 1 < n) {
        return sorted[idx] + frac * (sorted[idx + 1] - sorted[idx]);
    }
    return sorted[n - 1];
}

extern "C" {

double mean(const double* data, int n) {
    if (!isValidInput(data, n)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += data[i];
    }
    return sum / static_cast<double>(n);
}

double variance(const double* data, int n, int isSample) {
    int minReq = (isSample != 0) ? 2 : 1;
    if (n < minReq || !isValidInput(data, n)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double m = mean(data, n);
    double sqSum = 0.0;
    for (int i = 0; i < n; ++i) {
        double diff = data[i] - m;
        sqSum += diff * diff;
    }
    double denom = (isSample != 0) ? static_cast<double>(n - 1) : static_cast<double>(n);
    return sqSum / denom;
}

double stdDev(const double* data, int n, int isSample) {
    double var = variance(data, n, isSample);
    if (std::isnan(var)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return std::sqrt(var);
}

double median(const double* data, int n) {
    if (!isValidInput(data, n)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    std::vector<double> sorted(data, data + n);
    std::sort(sorted.begin(), sorted.end());
    return percentileSorted(sorted, 0.50);
}

int quartiles(const double* data, int n, double* q1, double* q2, double* q3) {
    if (!isValidInput(data, n) || q1 == nullptr || q2 == nullptr || q3 == nullptr) {
        return -1;
    }
    std::vector<double> sorted(data, data + n);
    std::sort(sorted.begin(), sorted.end());
    *q1 = percentileSorted(sorted, 0.25);
    *q2 = percentileSorted(sorted, 0.50);
    *q3 = percentileSorted(sorted, 0.75);
    return 0;
}

} // extern "C"
