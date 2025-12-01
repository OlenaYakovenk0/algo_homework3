#include "hungarian.hpp"
#include <vector>
#include <limits>
#include <cassert>

namespace assign {

std::pair<std::vector<int>, long long>
hungarian_min_sum(const std::vector<std::vector<long long>>& C_in) {
    const int n = (int)C_in.size();
    assert(n > 0);
    for (auto &row : C_in) assert((int)row.size() == n);

    const long long INF = std::numeric_limits<long long>::max()/4;

    // Перейдемо на 1-based індексацію (класична форма алгоритму)
    std::vector<std::vector<long long>> a(n+1, std::vector<long long>(n+1));
    for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) a[i][j] = C_in[i-1][j-1];

    std::vector<long long> u(n+1,0), v(n+1,0);
    std::vector<int> p(n+1,0), way(n+1,0);

    for (int i=1; i<=n; ++i) {
        p[0] = i;
        std::vector<long long> minv(n+1, INF);
        std::vector<char> used(n+1, false);
        int j0 = 0;

        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long long delta = INF;
            for (int j=1; j<=n; ++j) if (!used[j]) {
                long long cur = a[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                if (minv[j] < delta) { delta = minv[j]; j1 = j; }
            }
            for (int j=0; j<=n; ++j) {
                if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                else          { minv[j] -= delta; }
            }
            j0 = j1;
        } while (p[j0] != 0);

        // Відновлення змін ланцюжком
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    std::vector<int> match(n, -1);
    for (int j=1; j<=n; ++j) if (p[j]) match[p[j]-1] = j-1;

    long long cost = 0;
    for (int i=0;i<n;++i) cost += C_in[i][ match[i] ];
    return {match, cost};
}

} // namespace assign
