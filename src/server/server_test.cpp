#include "common/common_test.h"

int main() {
    std::vector<int> datas = {1, 2, 3, 4};
    int ret = sum(datas);
    std::cout << "server: " << ret << "\n";
    return 0;
}