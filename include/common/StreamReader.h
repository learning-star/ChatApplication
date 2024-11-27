#pragma once

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

#include "Buffer.h"

namespace ChatApp {
    class StreamReader {
    public:
        virtual ~StreamReader() = default;

        virtual bool IsStreamGood() const = 0;
        virtual uint64_t GetStreamPosition() = 0;
        virtual void SetStreamPosition(uint64_t position) = 0;
        virtual bool ReadData(char* destination, size_t size) = 0;

        operator bool() const { return IsStreamGood(); }

        bool ReadBuffer(Buffer& buffer, uint32_t size = 0);
        bool ReadString(std::string& string);

        template<typename T>
        bool ReadRaw(T& type) {
            bool ret = ReadData((char*)&type, sizeof(T));
            return ret;
        }

        template<typename T>
        void ReadObject(T& obj) {
            T::Deserialize(this, obj);
        }

        template<typename Key, typename Value>
        void ReadMap(std::map<Key, Value>& map, uint32_t size) {
            if(size == 0) {
                ReadRaw<uint32_t>(size);
            }
            for(uint32_t i=0; i<size;++i) {
                Key key;
                /// C++17 静态条件语句，条件需在编译期间确定。如果条件为true，保留分支，否则忽略分支（不会编译）
                /// std::is_trivial 模板：判断是否为平凡类型（trivial）
                /// 默认构造函数、拷贝构造函数、移动构造函数、拷贝赋值运算符、移动赋值运算符和析构函数全都是编译器默认生成的。
                /// 类型没有虚函数或虚基类。
                /// 该类型的内存布局是可以直接拷贝的（通过 memcpy 或类似方法复制数据是安全的）
                if constexpr (std::is_trivial<Key>()) { 
                    ReadRaw<Key>(key);
                } else {
                    ReadObject<Key>(key);
                }

                if constexpr (std::is_trivial<Value>()) {
                    ReadRaw<Value>(map[key]);
                } else {
                    ReadObject<Value>(map[key]);
                }
            }
        }

        template<typename Key, typename Value>
        void ReadMap(std::unordered_map<Key, Value>& map, uint32_t size) {
            if(size == 0) {
                ReadRaw<uint32_t>(size);
            }
            for(uint32_t i=0; i<size;++i) {
                Key key;
                if constexpr (std::is_trivial<Key>()) {
                    ReadRaw<Key>(key);
                } else {
                    ReadObject<Key>(key);
                }

                if constexpr (std::is_trivial<Value>()) {
                    ReadRaw<Value>(map[key]);
                } else {
                    ReadObject<Value>(map[key]);
                }
            }
        }

        template<typename Value>
        void ReadMap(std::unordered_map<std::string, Value>& map, uint32_t size) {
            if(size == 0) {
                ReadRaw<uint32_t>(size);
            }
            for(uint32_t i=0; i<size;++i) {
                std::string key;
                ReadString(key);
                
                if constexpr (std::is_trivial<Value>()) {
                    ReadRaw<Value>(map[key]);
                } else {
                    ReadObject<Value>(map[key]);
                }
            }

        }

        template<typename T>
		void ReadArray(std::vector<T>& array, uint32_t size = 0)
		{
			if (size == 0)
				ReadRaw<uint32_t>(size);

			array.resize(size);

			for (uint32_t i = 0; i < size; ++i)
			{
				if constexpr (std::is_trivial<T>())
					ReadRaw<T>(array[i]);
				else
					ReadObject<T>(array[i]);
			}
		}

		void ReadArray(std::vector<std::string>& array, uint32_t size)
		{
			if (size == 0)
				ReadRaw<uint32_t>(size);

			array.resize(size);

			for (uint32_t i = 0; i < size; ++i)
				ReadString(array[i]);
		}
    };
}