#include "hungarian.hpp"
#include <cassert>
#include <vector>
using namespace std;

int main(){
    {
        vector<vector<long long>> C = {
            {4,1,3},
            {2,0,5},
            {3,2,2}
        };
        auto [p, cost] = assign::hungarian_min_sum(C);
        assert((int)p.size()==3);
        assert(cost==5);
    }
    {
        vector<vector<long long>> C = {
            {9,2,7,8},
            {6,4,3,7},
            {5,8,1,8},
            {7,6,9,4}
        };
        auto [p, cost] = assign::hungarian_min_sum(C);
        assert(cost==13);
    }
    return 0;
}
