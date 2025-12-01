#pragma once
#include <vector>
#include <utility>

namespace assign {

std::pair<std::vector<int>, long long>
hungarian_min_sum(const std::vector<std::vector<long long>>& C);
}
