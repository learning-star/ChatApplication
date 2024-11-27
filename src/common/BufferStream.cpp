#include "common/BufferStream.h"

namespace ChatApp {
    BufferStreamReader::BufferStreamReader(Buffer targetBuffer, uint64_t position)
        : m_TargetBuffer(targetBuffer), m_BufferPosition(position) {}

    bool BufferStreamReader::ReadData(char *destination, size_t size) {
        bool valid = m_BufferPosition + size <= m_TargetBuffer.Size;
        if(!valid) {
            return false;
        }
        // 两次memcpy，不需要。
        // memcpy(destination, m_TargetBuffer.ReadBytes(size, m_BufferPosition), size);
        memcpy(destination, m_TargetBuffer.As<uint8_t>() + m_BufferPosition, size);
        m_BufferPosition += size;
        return true;
    }

    BufferStreamWriter::BufferStreamWriter(Buffer targetBuffer, uint64_t position)
        : m_TargetBuffer(targetBuffer), m_BufferPosition(position)
    {
    }

    bool BufferStreamWriter::WriteData(const char *data, size_t size) {
        bool valid = m_BufferPosition + size <= m_TargetBuffer.Size;
		if (!valid)
			return false;
            
        // m_TargetBuffer.Write(data, size, m_BufferPosition);
        // 保持一致
		memcpy(m_TargetBuffer.As<uint8_t>() + m_BufferPosition, data, size);
		m_BufferPosition += size;
		return true;
    }
}

