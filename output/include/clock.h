#pragma once
#include "replacer.h"
#include <list>
#include <vector>

namespace DB
{
    class Clock : public Replacer
    {
    private:
        size_t clock_hand;          // Indice que recorre los frames del algoritmo
        size_t buffer_size;         // Tamanio que se usa en el buffer
        std::vector<bool> ref_;     // Ref_bit 
        std::vector<bool> in_;      //  Presente en el clock ?
    
    public:
        explicit Clock(size_t num_pages);
        ~Clock() override;
        bool Victim(int *frame_id) override;    // encuentra el indice del frame disponible
        void Pin(int frame_id) override;
        void Unpin(int frame_id) override;
        // Retorna el numero de frames que estan presentes en el algoritmo
        size_t Size() override;         
    
    };

    Clock::Clock(size_t num_pages)
    {
        clock_hand = 0;
        buffer_size = num_pages;
        in_ = std::vector<bool>(num_pages, 0);
        ref_ = std::vector<bool>(num_pages, 0);
    }

    Clock::~Clock() = default;

    bool Clock::Victim(int *frame_id)
    {
        while(Size() > 0)
        {
            clock_hand = clock_hand % buffer_size;
            if(in_[clock_hand] && !ref_[clock_hand])    // si esta y no esta en uso
            {
                //in_[clock_hand] = false;
                *frame_id = clock_hand;     // devuelve indice
                clock_hand++;               // avanza indice
                return true;
            }
            else if(ref_[clock_hand])       // si esta ocupado
            {
                ref_[clock_hand] = false;   //  cambia a 0
                clock_hand++;               // avanza indice
            }
            else
                clock_hand++;
        }
        return false;
    }

    void Clock::Pin(int frame_id) 
    {
        in_[frame_id] = false;
    }

    void Clock::Unpin(int frame_id) 
    {
        ref_[frame_id] = true;
        in_[frame_id] = true;
    }

    size_t Clock::Size()
    { 
        size_t counter = 0;
        for(size_t i = 0; i < buffer_size; ++i)
            if(in_[i])
                counter++;
        return counter;
    }
}