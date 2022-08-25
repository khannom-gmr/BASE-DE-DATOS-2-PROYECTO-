#pragma  once
#include <cstdint>
#include <cstddef>
#include <iostream>

namespace DB
{
    class Replacer
    {
    public:
        // Define los metodos virtuales
        Replacer() = default;
        virtual ~Replacer() = default;
        virtual bool Victim(int32_t *frame_id) = 0;     // Polimorfismo
        virtual void Pin(int32_t frame_id) = 0;         // Pin frame 
        virtual void Unpin(int32_t frame_id) = 0;       // Unpin frame
        virtual size_t Size() = 0;                      // tamanio de buffer
    };
}