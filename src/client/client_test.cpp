#include "common/common_test.h"
#include "common/log.h"

int main() {
    ChatApp::Log::Init();
    std::vector<int> datas = {1, 2, 3, 4};
    int ret = sum(datas);
    std::cout << "client: " << ret << "\n";
    CA_TRACE_TAG("client", "client trace info {}", ret);
    CA_INFO_TAG("client", "client info info {}", ret);
    CA_WARN_TAG("client", "client warn info {}", ret);
    CA_ERROR_TAG("client", "client error info {}", ret);
    ChatApp::Log::Shutdown();
    return 0;
}