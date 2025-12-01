#include "hungarian.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    // Формат: n, далі n рядків по n цілих
    int n; if(!(cin >> n)) return 1;
    vector<vector<long long>> C(n, vector<long long>(n));
    for (int i=0;i<n;++i) for (int j=0;j<n;++j) cin >> C[i][j];

    auto [p, cost] = assign::hungarian_min_sum(C);
    cout << "cost " << cost << "\n";
    for (int i=0;i<n;++i) cout << i << " -> " << p[i] << "\n";
    return 0;
}
