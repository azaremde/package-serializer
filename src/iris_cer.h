#pragma once

#include <vector>
#include <fstream>
#include <ostream>
#include <iostream>

#define LOG(x) std::cout << x << '\n'

struct Ser
{
    virtual std::vector<float>* get_float_vector1() { return {}; }

    void save(const std::string& path)
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.unsetf(std::ios::skipws);

        std::vector<float>& vec = *get_float_vector1();
        size_t vec_size = vec.size();
        ofs.write((char*)&vec_size, sizeof(size_t));
        ofs.write((const char*)vec.data(), vec_size * sizeof(float));

        ofs.close();
    }
    
    void load(const std::string& path)
    {
        std::ifstream ifs(path, std::ios::binary);

        // Stop eating new lines in binary mode!!!
        ifs.unsetf(std::ios::skipws);

        std::vector<float>& vec = *get_float_vector1();
        size_t vec_size = 0;
        ifs.read((char*)&vec_size, sizeof(size_t));
        vec.resize(vec_size);
        ifs.read((char*)vec.data(), vec_size * sizeof(size_t));        

        ifs.close();
    }
    
};
