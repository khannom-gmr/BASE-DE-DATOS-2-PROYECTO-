#pragma once 
#include "page.h"
#include "replacer.h"
#include "clock.h"
#include "LRU.h"
#include "MRU.h"
#include "file.h"
#include <unordered_map>
#include <iostream>

namespace DB
{
    struct Frame
    {
        Page *page;         
        int dirty_page;                             // pagina modificada
        int pin_count;                              // contador de acceso
    };

    class Buffer
    {
    private:
        size_t s_pool;                               
        Replacer *replacer_;                        // Clase abstracta (polimorfismo)
        std::list<int> free_blist;                  
        std::unordered_map<int, int> page_table_;  
        File *file_;
        
    public:
        Buffer(size_t pool_size, File *file);
        Page* NewPageImpl(int *page_id);
        Page* FetchPageImpl(int page_id);
        bool FlushPageImpl(int page_id);
        bool DeletePageImpl(int page_id);
        bool UnpinPageImpl(int page_id, bool is_dirty);
        void FlushAllPagesImpl();
        ~Buffer();
        std::vector<Frame> buffer_pool;
    };

    //Constructor con tamanio de buffer_pool y puntero al File
    Buffer::Buffer(size_t pool_size, File *file) : s_pool(pool_size), file_(file)
    {
        buffer_pool = std::vector<Frame>(pool_size);
        //Inicializamos el replacer con el algoritmo de remplazamiento elegido 
        replacer_ = new Clock(pool_size);
        for (int32_t i = 0; i < pool_size; i++)
        {
            //Inicializamos las listas en 0
            free_blist.emplace_back(static_cast<int>(i));
            buffer_pool[i].dirty_page = 0;
            buffer_pool[i].pin_count = 0;
        }
    }

    //Obtener pagina solicitada por id
    Page* Buffer::FetchPageImpl(int page_id) 
    {
        //Si la pagina se encuentra ya en el buffer.
        if(page_table_.find(page_id)!= page_table_.end())
        {
            //Actualiza metadata de la pagina en el Buffer
            int target = page_table_[page_id];      // devuelve frame_id
            replacer_->Pin(target);
            buffer_pool[target].pin_count++;
            //Retorna el puntero la pagina encontrada
            return buffer_pool[target].page;
        }
        //En caso la pagina solicitada, NO se encuentre en el buffer
        else
        {
            //Seteamos un entero que reciba el indice a utilizar
            int target;
            if(!free_blist.empty())     //Si existen espacios disponibles
            {
                target = free_blist.front();
                free_blist.pop_front();
                //Target se setea como el espacio encontrado
                replacer_->Unpin(target);
                //Actualizamos los contenidos de la page_table y el buffer_pool
                page_table_.insert({page_id, target});
                buffer_pool[target].pin_count++;
                buffer_pool[target].page = file_->readPage(page_id);
                buffer_pool[target].dirty_page = 0;
                //Retornamos el puntero a la pagina requerida 
                return buffer_pool[target].page;
            }
            else        //Sino, utilizamos el algoritmo de remplazamiento 
            {
                if(!replacer_->Victim(&target)) 
                    return nullptr;
                int target_page_id = buffer_pool[target].page->page_number(); // page_id de la pagina que se eliminara del buffer
                std::cout << "page_id_to_replace: " << target_page_id << "\n"; 
                
                if(buffer_pool[target].dirty_page)
                    if(!FlushPageImpl(target_page_id)) 
                        return nullptr;

                replacer_->Pin(target);
                buffer_pool[target].pin_count++;
                //Actualizamos los contenidos de la page_table y el buffer_pool
                page_table_.erase(target_page_id);          // borra la pagina del buffer
                page_table_.insert({page_id, target});
                buffer_pool[target].page = file_->readPage(page_id);    // lee nueva pagina del file
                buffer_pool[target].dirty_page = 0;
                //Retornamos el puntero a la pagina requerida 
                return buffer_pool[target].page;
            }
            
        }
        return nullptr;
    }

    bool Buffer::UnpinPageImpl(int page_id, bool is_dirty)
    {
        if(page_table_.find(page_id) == page_table_.end())
            return true;
        int target = page_table_[page_id];
        if(buffer_pool[target].pin_count <= 0)
            return false;
        else 
        {
            buffer_pool[target].pin_count--;
            buffer_pool[target].dirty_page |= is_dirty;
            if(buffer_pool[target].pin_count == 0)
                replacer_->Unpin(target);
            return true;
        }
    }

    bool Buffer::FlushPageImpl(int page_id) 
    {
        if(page_id == -1)
            return false;
        if(page_table_.find(page_id) == page_table_.end())
            return false;
        else 
        {
            int target = page_table_[page_id];
            if(!buffer_pool[target].dirty_page)
                return true;
            file_->write_page(page_id, buffer_pool[target].page);
            buffer_pool[target].dirty_page = 0;
            return true;
        }
    }

    Page *Buffer::NewPageImpl(int *page_id) 
    {
        if(!free_blist.empty())                         // Si existe un frame libre, lo toma y asigna.
        {
            int free_frame = free_blist.front();        // Indice de frame libre
            free_blist.pop_front();                     // Elimina indice
            *page_id = file_->allocatePage();           // Page_id guarda id nueva pagina
            page_table_[*page_id] = free_frame;         // Guarda frame
            replacer_->Pin(free_frame);                 // Marca la pagina como "En Uso"
            buffer_pool[free_frame].page = new Page(*page_id); // Guarda nueva pagina en el frame
            buffer_pool[free_frame].pin_count = 1;                  // Uno en uso
            buffer_pool[free_frame].dirty_page = false;              // no esta modificado

            return buffer_pool[free_frame].page;        // Devuelve puntero a la pagina
        }
        else                                            // Si no hay frames disponibles 
        {
            int victim;         
            if(!replacer_->Victim(&victim))             // Algoritmo de remplazamiento
                return nullptr;

            if(buffer_pool[victim].dirty_page)           // Si ha sido modificado
                if(!FlushPageImpl(buffer_pool[victim].page->page_number()))  // Lo manda al file
                    return nullptr;
            
            // Coloca la pagina nueva en el buffer
            int victim_page_id = buffer_pool[victim].page->page_number();
            page_table_.erase(victim_page_id);              // borra 
            *page_id = file_->allocatePage();               // nuevo page_id
            page_table_[*page_id] = victim;                 // guarda frame_id
            replacer_->Pin(victim);                         // que mrd hace esto
            buffer_pool[victim].page = new Page(*page_id);  // nueva pagina
            buffer_pool[victim].pin_count = 1;              // uno en uso
            buffer_pool[victim].dirty_page = false;          // no esta modificado

            return buffer_pool[victim].page;    // devuelve puntero a la pagina
        }
    }

    bool Buffer::DeletePageImpl(int page_id) {
        if(page_table_.find(page_id) == page_table_.end())
            return false;
        else
        {
            int target = page_table_[page_id];      // devuelve frame_id
            if(buffer_pool[target].pin_count != 0)      // si esta siendo usado no elimina
                return false;
            else
            {
                page_table_.erase(page_id);             // elimina
                buffer_pool[target].page = nullptr;     // vacio
                buffer_pool[target].dirty_page = false;  // pagina no modificada 
                free_blist.push_back(target);           // indice del frame libre
                return true;
            }
        }
        return false;
    }

    void Buffer::FlushAllPagesImpl() 
    {
        for(size_t i = 0; i < s_pool; ++i)
            if(buffer_pool[i].dirty_page)
                if(!FlushPageImpl(buffer_pool[i].page->page_number())){}
    }

    Buffer::~Buffer(){
        delete replacer_;
    }
}