#include "hungarian.hpp"
#include <limits>
#include <queue>

namespace assign {

std::pair<std::vector<int>, long long>
hungarian_min_sum(const std::vector<std::vector<long long>>& C_in) {
    const int n = (int)C_in.size();
    std::vector<std::vector<long long>> C = C_in;

    // Row reduction
    for (int i = 0; i < n; ++i) {
        long long mn = C[i][0];
        for (int j = 1; j < n; ++j) if (C[i][j] < mn) mn = C[i][j];
        for (int j = 0; j < n; ++j) C[i][j] -= mn;
    }

    // Column reduction
    for (int j = 0; j < n; ++j) {
        long long mn = C[0][j];
        for (int i = 1; i < n; ++i) if (C[i][j] < mn) mn = C[i][j];
        for (int i = 0; i < n; ++i) C[i][j] -= mn;
    }

    auto build_zero_graph = [&](std::vector<std::vector<int>>& adj){
        adj.assign(n, {});
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (C[i][j] == 0) adj[i].push_back(j);
    };

    auto dfs = [&](auto&& self, int u,
                   const std::vector<std::vector<int>>& adj,
                   std::vector<int>& matchC,
                   std::vector<char>& used) -> bool {
        for (int v : adj[u]) if (!used[v]) {
            used[v] = 1;
            if (matchC[v] == -1 || self(self, matchC[v], adj, matchC, used)) {
                matchC[v] = u;
                return true;
            }
        }
        return false;
    };

    std::vector<std::vector<int>> adj;
    std::vector<int> matchC(n, -1);      // col -> row
    std::vector<int> matchR(n, -1);      // row -> col (result)

    while (true) {
        build_zero_graph(adj);
        std::fill(matchC.begin(), matchC.end(), -1);

        int msize = 0;
        for (int i = 0; i < n; ++i) {
            std::vector<char> used(n, 0);
            if (dfs(dfs, i, adj, matchC, used)) ++msize;
        }
        if (msize == n) {
            for (int j = 0; j < n; ++j) if (matchC[j] != -1) matchR[ matchC[j] ] = j;
            long long cost = 0;
            for (int i = 0; i < n; ++i) cost += C_in[i][ matchR[i] ];
            return {matchR, cost};
        }

        // Minimum vertex(zero) cover
        std::vector<char> visRow(n, 0), visCol(n, 0);
        std::queue<int> q;
        std::vector<int> matchRow(n, -1);
        for (int j = 0; j < n; ++j) if (matchC[j] != -1) matchRow[ matchC[j] ] = j;
        for (int i = 0; i < n; ++i) if (matchRow[i] == -1) { visRow[i] = 1; q.push(i); }

        while (!q.empty()) {
            int r = q.front(); q.pop();
            for (int c : adj[r]) {
                if (!visCol[c]) {
                    visCol[c] = 1;
                    if (matchC[c] != -1 && !visRow[ matchC[c] ]) {
                        visRow[ matchC[c] ] = 1;
                        q.push(matchC[c]);
                    }
                }
            }
        }

        long long delta = std::numeric_limits<long long>::max();
        for (int i = 0; i < n; ++i) if (visRow[i])
            for (int j = 0; j < n; ++j) if (!visCol[j] && C[i][j] < delta)
                delta = C[i][j];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (visRow[i] && !visCol[j]) C[i][j] -= delta;          // uncovered
                else if (!visRow[i] && visCol[j]) C[i][j] += delta;     // crossed line
            }
    }
}

}
