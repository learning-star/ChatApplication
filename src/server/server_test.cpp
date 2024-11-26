#include "common/common_test.h"
#include "common/log.h"

int main() {
    ChatApp::Log::Init();
    std::vector<int> datas = {1, 2, 3, 4};
    int ret = sum(datas);
    std::cout << "server: " << ret << "\n";
    CA_COMMON_TRACE("server info {0}.", ret);
    CA_COMMON_INFO("server info {0}.", ret);
    CA_COMMON_WARN("server info {0}.", ret);
    CA_COMMON_ERROR("server info {0}.", ret);
    CA_COMMON_TRACE_TAG("logging", "server info {0}.", ret);
    CA_COMMON_TRACE_TAG("logging", "server info {0}.", ret);
    CA_COMMON_TRACE_TAG("logging", "server info {0}.", ret);
    CA_COMMON_TRACE_TAG("logging", "server info {0}.", ret);
    ChatApp::Log::Shutdown();
    return 0;
}