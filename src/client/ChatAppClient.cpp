#include "common/BufferStream.h"
#include "common/Log.h"

int main(int argc, char* argv[]) {
    ChatApp::ScopeForLog logManager;
    ChatApp::Buffer buf;
    buf.Allocate(2048);
    ChatApp::BufferStreamWriter bufWrite(buf);

    CA_INFO_TAG("BufferStreamWriter", "CurBufPosistion: {0}", bufWrite.GetStreamPosition());
    bufWrite.WriteRaw<int>(123);
    CA_INFO_TAG("BufferStreamWriter", "CurBufPosistion: {0}", bufWrite.GetStreamPosition());
    std::string test_str = "这是测试数据";
    bufWrite.WriteString(test_str);
    CA_INFO_TAG("BufferStreamWriter", "CurBufPosistion: {0}", bufWrite.GetStreamPosition());

    ChatApp::BufferStreamReader bufReader(buf);

    CA_INFO_TAG("BufferStreamReader", "CurBufPosistion: {0}", bufReader.GetStreamPosition());
    int data;
    std::string data_str;
    bufReader.ReadRaw<int>(data);
    CA_INFO_TAG("BufferStreamReader", "CurBufPosistion: {0}", bufReader.GetStreamPosition());
    bufReader.ReadString(data_str);
    CA_INFO_TAG("BufferStreamReader", "CurBufPosistion: {0}", bufReader.GetStreamPosition());

    return 0;
}