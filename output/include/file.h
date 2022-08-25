#pragma once
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream> 
#include <sstream> 
#include "page.h"

namespace DB
{
    struct FileHeader
    {
        int num_pages;        // Numero de paginas alojadas en el file
        int first_free_pages; // Numero de la primera pagina marcada como "used" en el file.
        int num_free_pages;   // Numero de paginas alojadas pero sin usar en el file.
        int first_used_page;  // Numero de la primera pagina sin usar en el file.
    };

    class File
    {
    private:
        FileHeader header;
        std::string filename;
        std::vector<Page> pages;

    public:
        File(std::string &name);
        ~File();                                // escribe en txt
        void open(char separator);              // abre un archivo txt y lee su informacion
        void remove(std::string &filename);     // elimina un archivo txt
        void close(std::string &filename);      // actualiza y cierra el archivo txt 
        bool isOpen(std::string &filename);     // comprueba si un archivo txt esta abierto
        bool exists(std::string &filename);     // comprueba si un archivo txt existe
        
        int allocatePage();                                 // aloja una pagina dentro del file
        Page* readPage(int page_id);                        // lee una pagina dentro del file
        void write_page(int page_id, Page* new_page);       // escribe pagina dentro del file
        void deletePage(int page_id);                       // borra pagina dentro del file

        bool validate_page_id(int page_id);
        int get_num_pages(){ return pages.size(); }
        void set_filename(std::string& filename_){ filename = filename_; }

        std::vector<Page>::iterator begin(){ return pages.begin(); }
        std::vector<Page>::iterator end(){ return pages.end(); }

        std::map<std::string, int> open_counts;
    };

    File::File(std::string &name)
    {
        filename = name;
        header.num_pages = 0;
        header.first_free_pages = 0;
        header.num_free_pages = 0;
        header.first_used_page = 0;
    }

    File::~File()
    {
        close(filename);
    }

    void File::remove(std::string &filename)
    {
        if (!exists(filename))
        {
            std::cout << "File " << filename << " no encontrado\n";
            return;
        }
        if (isOpen(filename))
        {
            std::cout << "No se puede borrar el file " << filename << ", ya que esta en uso.\n";
            return;
        }
        std::remove(&filename[0]);
    }

    void File::open(char separator)
    { 
        if(!exists(filename))       // if there is no a file called filename and the filename is not changed, 
        {                           // then a blank file is created
            std::cout<<"el archivo "<<filename<<" no existe\n";
            return;
        }
        std::fstream in;
        in.open(filename, std::ios::in);
        open_counts[filename]++;
        std::string line;
        while(getline(in, line)) 
        {
            int rid = allocatePage();
            Page new_page(rid);        // crea pagina
            std::stringstream record_(line);
            std::string col;
            while(std::getline(record_, col, separator))
                new_page.insert_record(col);
            write_page(new_page.page_number(),&new_page);
        }
        in.close();
    }

    void File::close(std::string &filename) 
    {
        std::fstream out; 
        out.open(filename, std::ios::out);
        open_counts[filename]--;
        if(open_counts[filename] <= 0) open_counts.erase(filename);
        for(Page p : pages) 
        {
            auto it = p.begin(); 
            while(it != p.end()) 
            {
                out << it -> record << "$";
                it++;
            } 
            out << "\n"; 
        }      
    }

    bool File::isOpen(std::string &filename)
    {
        if (!exists(filename))
        {
            std::cout << "El archivo "<< filename <<"no existe\n";
            return false;
        }
        if (!open_counts.count(filename))
            return false;
        if (open_counts[filename] > 0)
            return true;
        return true;
    }

    bool File::exists(std::string &filename)
    {
        std::fstream aux_file(filename);
        if (aux_file)
        {
            aux_file.close();
            return true;
        }
        return false;
    }

    int File::allocatePage()
    {
        Page new_page(header.num_pages);

        pages.push_back(new_page);
        header.num_pages++;
        header.num_free_pages++;

        return new_page.page_number();
    }

    Page* File::readPage(int page_id)
    {
        Page* current_page = NULL;
        if(!validate_page_id(page_id))
            return current_page;

        for(int i=0 ; i<pages.size() ; ++i)
            if(pages[i].page_number() == page_id)
                current_page = &pages[i];
        return current_page;
    }

    void File::write_page(int page_id, Page *new_page)
    {
        // pages[page_id] = *new_page;
        for(int i=0 ; i<pages.size() ; ++i)
            if(pages[i].page_number() == page_id)
                pages[i] = *new_page;
    }

    void File::deletePage(int page_id)
    {
        if(!validate_page_id(page_id))
            return;
        int k=0;
        for(int i=0 ; i<pages.size() ; ++i)
            if(pages[i].page_number() == page_id)
                pages.erase(pages.begin() + page_id);
        while(k<pages.size())
        {
            pages[k].set_page_number(k);
            pages[k].set_next_page_number(k+1);
            k++;
        }
        header.num_pages--;
        header.num_free_pages--; // falta corregir logica
    }

    bool File::validate_page_id(int page_id)
    {
        if(page_id >= header.num_pages)
        {
            std::cout << "Requerimiento dirigido a pagina invalida."
                    << "pagina= " << page_id << '\n';
            return false;
        }
        return true;
    }
}
