#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "hungarian.hpp"

int main() {
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 1;

    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> C[i][j];

    auto t0 = chrono::steady_clock::now();
    auto res = assign::hungarian_min_sum(C);
    auto t1 = chrono::steady_clock::now();
    (void)res;

    double secs = chrono::duration<double>(t1 - t0).count();
    cout.setf(std::ios::fixed);
    cout << std::setprecision(6) << secs << "\n";
    return 0;
}
