#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

#include "Buffer.h"

namespace ChatApp
{
    class StreamWriter
    {
    public:
        virtual ~StreamWriter() = default;

        virtual bool IsStreamGood() const = 0;
        virtual uint64_t GetStreamPosition() = 0;
        virtual void SetStreamPosition(uint64_t position) = 0;
        virtual bool WriteData(const char *data, size_t size) = 0;

        operator bool() const { return IsStreamGood(); }

        void WriteBuffer(Buffer buffer, bool writeSize = true);
        void WriteZero(uint64_t size);
        void WriteString(const std::string &string);
        void WriteString(std::string_view string);

        template <typename T>
        void WriteRaw(const T &type)
        {
            WriteData((char *)&type, sizeof(T));
        }

        template <typename T>
        void WriteObjec(const T &obj)
        {
            T::Serialize(this, obj);
        }

        template <typename Key, typename Value>
        void WriteMap(const std::map<Key, Value> &map, bool writeSize = true)
        {
            if (writeSize)
            {
                WriteRaw<uint32_t>((uint32_t)map.size());
            }
            for (const auto &[key, value] : map)
            {
                if constexpr (std::is_trivial<Key>())
                {
                    WriteRaw<Key>(key);
                }
                else
                {
                    WriteObjec<Key>(key);
                }

                if constexpr (std::is_trivial<Value>())
                {
                    WriteRaw<Value>(value);
                }
                else
                {
                    WriteObjec<Value>(value);
                }
            }
        }

        template <typename Key, typename Value>
        void WriteMap(const std::unordered_map<Key, Value> &map, bool writeSize = true)
        {
            if (writeSize)
            {
                WriteRaw<uint32_t>((uint32_t)map.size());
            }
            for (const auto &[key, value] : map)
            {
                if constexpr (std::is_trivial<Key>())
                {
                    WriteRaw<Key>(key);
                }
                else
                {
                    WriteObjec<Key>(key);
                }

                if constexpr (std::is_trivial<Value>())
                {
                    WriteRaw<Value>(value);
                }
                else
                {
                    WriteObjec<Value>(value);
                }
            }
        }

        template <typename T>
        void WriteArray(const std::vector<T> &array, bool writeSize = true)
        {
            if (writeSize)
            {
                WriteRaw<uint32_t>((uint32_t)array.size());
            }
            for (const auto &elemet : array)
            {
                if constexpr (std::is_trivial<T>())
                {
                    WriteRaw<T>(elemet);
                }
                else
                {
                    WriteObjec<T>(elemet);
                }
            }
        }

        void WriteArray(const std::vector<std::string> &array, bool writeSize)
        {
            if (writeSize)
            {
                WriteRaw<uint32_t>((uint32_t)array.size());
            }
            for (const auto &elemet : array)
            {
                WriteString(elemet);
            }
        }
    };
}