#pragma once
#include "replacer.h"
#include <list>
#include <vector>

namespace DB
{
    // algoritmo MRU
    class MRU : public Replacer
    {
    private:
        bool IsInReplacer(int frame_id);
        std::list<int> w_list{};
        std::vector<std::list<int>::iterator> page_iters;

    public:
        // numero paginas para el LRU
        explicit MRU(size_t num_pages);
        ~MRU();
        bool Victim(int *frame_id) override;    // encuentra el indice del frame disponible
        void Pin(int frame_id) override;
        void Unpin(int frame_id) override;
        size_t Size() override;
    };

    MRU::MRU(size_t num_pages) : page_iters{num_pages} {}

    MRU::~MRU() = default;

    // Metodo de eliminacion del objeto al que se accedio menos recientemente (front)
    bool MRU::Victim(int *frame_id)
    {
        //Si w_list esta vacia retorna false
        if (w_list.empty())
        {
            *frame_id = -1;
            return false;
        }
        // Guarda el puntero al frame del frente
        // Elimina el puntero de las paginas
        *frame_id = w_list.front();
        w_list.pop_front();
        page_iters[*frame_id] = std::list<int>::iterator{};
        return true;
    }

    // Este metodo debe llamarse despues de que una pagina se fije a un frame en Buffer.
    // Deberia eliminar el frame que contiene la pagina anclada del replacer
    void MRU::Pin(int frame_id)
    {
        // Si no esta en el replacer termina
        // Si esta procede a eliminarlo de w_list
        if (!IsInReplacer(frame_id))
            return;
        w_list.erase(page_iters[frame_id]);
        page_iters[frame_id] = std::list<int>::iterator{};
    }

    // Llamar a este método cuando el sea necesario retirar al frame del Buffer. 
    // Este metodo debe agregar el frame que contiene la pagina no fijada al replacer
    void MRU::Unpin(int frame_id)
    {
        // Si ya esta en el replacer termina
        // Si no procede a agregarlo al frente de w_list
        if (IsInReplacer(frame_id))
            return;
        w_list.push_front(frame_id);
        page_iters[frame_id] = w_list.begin();
    }

    //Retrona la cantidad de frames en el replacer
    size_t MRU::Size()
    {
        return w_list.size();
    }

    // Retorna el estado en el replacer
    bool MRU::IsInReplacer(int frame_id)
    {
        return page_iters[frame_id] != std::list<int>::iterator{};
    }
}