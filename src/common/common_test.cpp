#include "common/common_test.h"

int sum(const std::vector<int>& nums) {
    int sum = 0;
    for(auto & num : nums) {
        sum += num;
    }
    return sum;
}