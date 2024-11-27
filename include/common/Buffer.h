#pragma once

#include <memory>
#include <string.h>

namespace ChatApp {

    struct Buffer {
        void* Data;
        uint64_t Size;
        Buffer() : Data(nullptr), Size(0){}
        Buffer(const void* data, uint64_t size) 
            : Data((void*)(data)), Size(size) {}
        // shallow copy. 
        // 浅拷贝。
        Buffer(const Buffer& other) = default;
        Buffer(const Buffer& other, uint64_t size)
            : Data(other.Data), Size(size) {
        }
        void Allocate(uint64_t size) {
            delete[] (uint8_t*)Data;
            Data = nullptr;
            if(size == 0) {
                return;
            }
            Data = new uint8_t[size];
            Size = size;
        }

        void BeZero() {
            if(Data) {
                memset(Data, 0, Size);
            }
        }
        // deep copy
        // 深拷贝
        static Buffer Copy(const Buffer& other) {
            Buffer buffer;
            buffer.Allocate(other.Size);
            memcpy(buffer.Data, other.Data, other.Size);
            return buffer;
        }

        static Buffer Copy(const void* data, uint64_t size) {
            Buffer buffer;
            buffer.Allocate(size);
            memcpy(buffer.Data, data, size);
            return buffer;
        }

        inline uint64_t GetSize() const {return Size;}

        void Release() {
            delete[] (uint8_t*)Data;
            Data = nullptr;
            Size = 0;
        }

        ///////////////////////////////////////////////////////////////////
        // template define
        template<typename T>
        T& Read(uint64_t offset = 0) const {
            // 4 byte align, maybe exsit some problems
            return *(T*)((uint32_t*)Data + offset);
            // return *(T*)((uint8_t*)Data + offset * sizeof(T));
        }

        // 将内存类型转换为类型T
        template<typename T>
        T* As() const
        {
            return (T*)Data;
        }
        /////////////////////////////////////////////////////////////////

        uint8_t* ReadBytes(uint64_t size, uint64_t offset) const {
            uint8_t* buffer = new uint8_t[size];
            memcpy(buffer, (uint8_t*)Data + offset, size);
            return buffer;
        }

        void Write(const void* data, uint64_t size, uint64_t offset = 0) {
            memcpy((uint8_t*)Data+offset, data, size);
        }

        operator bool() const {
            return Data;
        }

        uint8_t& operator [](int index) {
            return ((uint8_t*)Data)[index];
        }

        uint8_t operator [](int index) const {
            return ((uint8_t*)Data)[index];
        }
    };
}