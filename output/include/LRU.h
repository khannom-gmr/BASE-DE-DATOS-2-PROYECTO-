#pragma once
#include "replacer.h"
#include <list>
#include <vector>

namespace DB
{
    class LRU : public Replacer
    {
    private:
        bool IsInReplacer(int frame_id);    
        std::list<int> w_list{};
        std::vector<std::list<int>::iterator> page_iters;

    public:
        // numero paginas para el LRU
        explicit LRU(size_t num_pages);
        ~LRU();
        bool Victim(int *frame_id) override;
        void Pin(int frame_id) override;
        void Unpin(int frame_id) override;
        size_t Size() override;
    };

    LRU::LRU(size_t num_pages) : page_iters{num_pages} {}

    LRU::~LRU() = default;

    // Metodo de eliminacion del objeto al que se accedio menos recientemente (back)
    bool LRU::Victim(int *frame_id)
    {
        // si w_list esta vacia devuelve falso
        if (w_list.empty())
        {
            *frame_id = -1;
            return false;
        }
        
        *frame_id = w_list.back();
        w_list.pop_back();
        page_iters[*frame_id] = std::list<int>::iterator{};
        return true;
    }

    void LRU::Pin(int frame_id)
    {
        // Si no esta en el replacer termina
        // Si esta procede a eliminarlo de w_list
        if (!IsInReplacer(frame_id))
            return;
        w_list.erase(page_iters[frame_id]);
        page_iters[frame_id] = std::list<int>::iterator{};
    }

    void LRU::Unpin(int frame_id)
    {
        // Si ya esta en el replacer termina
        // Si no procede a agregarlo al frente de w_list
        if (IsInReplacer(frame_id))
            return;
        w_list.push_front(frame_id);
        page_iters[frame_id] = w_list.begin();
    }

    //Retrona la cantidad de frames en el replacer
    size_t LRU::Size()
    {
        return w_list.size();
    }

    // Verifica el estado de un frame en el replacer
    bool LRU::IsInReplacer(int frame_id)
    {
        return page_iters[frame_id] != std::list<int>::iterator{};
    }
}