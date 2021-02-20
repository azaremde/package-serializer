#include <fstream>
#include <ostream>

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << '\n'

class Serializable
{
protected:
    std::string name;

    unsigned int size /* in bytes */ { 0 };

    Serializable(const std::string& name)
    {
        this->name = name;
    }

    Serializable() {}

private:
    template <typename T>
    inline static unsigned int write_vector(std::ofstream &ofs, std::vector<T> vec)
    {
        unsigned int memory = 0;
        
        for (int i = 0; i < vec.size(); i++)
        {
            ofs.write((char *)&vec[i], sizeof(T));
            memory += sizeof(T);
        }

        return memory;
    }

    template <typename T>
    inline static void populate_vector(std::vector<T> &vec, T *array, int size)
    {
        vec.resize(size);
        for (int i = 0; i < size; i++)
        {
            vec[i] = array[i];
        }
    }

    unsigned int save_sizes_of_float_vectors(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_float_vectors().size(); i++)
        {
            std::vector<float> &vector = *get_float_vectors()[i];
            int size = vector.size();
            ofs.write((char *)&size, sizeof(int));
            memory += sizeof(int);
        }

        return memory;
    }

    unsigned int save_sizes_of_int_vectors(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_int_vectors().size(); i++)
        {
            std::vector<int> &vector = *get_int_vectors()[i];
            int size = vector.size();
            ofs.write((char *)&size, sizeof(int));
            memory += sizeof(int);
        }

        return memory;
    }

    unsigned int save_float_vectors(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_float_vectors().size(); i++)
        {
            std::vector<float> &vector = *get_float_vectors()[i];
            memory += write_vector(ofs, vector);
        }

        return memory;
    }

    unsigned int save_int_vectors(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_int_vectors().size(); i++)
        {
            std::vector<int> &vector = *get_int_vectors()[i];
            memory += write_vector(ofs, vector);
        }

        return memory;
    }

    unsigned int save_floats(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_floats().size(); i++)
        {
            ofs.write((char *)get_floats()[i], sizeof(float));
            memory += sizeof(float);
        }

        return memory;
    }

    unsigned int save_ints(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_ints().size(); i++)
        {
            ofs.write((char *)get_ints()[i], sizeof(int));
            memory += sizeof(int);
        }       

        return memory; 
    }

    unsigned int save_sizes_of_strings(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        p_strings &strings = get_strings();
        for (int i = 0; i < strings.size(); i++)
        {
            int size = strings[i]->size();
            ofs.write((char *)&size, sizeof(int));
            memory += sizeof(int);
        }

        return memory;
    }

    unsigned int save_strings(std::ofstream& ofs)
    {
        unsigned int memory = 0;

        p_strings &strings = get_strings();
        for (int i = 0; i < strings.size(); i++)
        {
            std::string &str = *strings[i];
            for (int j = 0; j < str.size(); j++)
            {
                ofs.write((char *)&str[j], sizeof(char));
                memory += sizeof(char);
            }
        }

        return memory;
    }

    unsigned int load_sizes_of_float_vectors(std::ifstream& ifs, std::vector<int>* float_vectors_sizes)
    {
        unsigned int memory = 0;

        v_vp_float &float_vectors = get_float_vectors();
        float_vectors_sizes->resize(float_vectors.size());

        for (int i = 0; i < float_vectors.size(); i++)
        {
            ifs.read((char *)&(*float_vectors_sizes)[i], sizeof(int));
            memory += sizeof(int);
        }

        return memory;
    }

    unsigned int load_sizes_of_int_vectors(std::ifstream& ifs, std::vector<int>* int_vectors_sizes)
    {   
        unsigned int memory = 0;     

        v_vp_int &int_vectors = get_int_vectors();
        int_vectors_sizes->resize(int_vectors.size());

        for (int i = 0; i < int_vectors.size(); i++)
        {
            ifs.read((char *)&(*int_vectors_sizes)[i], sizeof(int));
        }

        return memory;
    }

    unsigned int load_float_vectors(std::ifstream& ifs, std::vector<int>* float_vectors_sizes)
    {
        unsigned int memory = 0;
        
        for (int i = 0; i < float_vectors_sizes->size(); i++)
        {
            int size = (*float_vectors_sizes)[i];
            Serializable::f_buffer = new float[size];
            for (int i = 0; i < size; i++)
            {
                ifs.read((char *)&Serializable::f_buffer[i], sizeof(float));
                memory += sizeof(float);
            }
            populate_vector(*get_float_vectors()[i], Serializable::f_buffer, size);
        }

        return memory;
    }

    unsigned int load_int_vectors(std::ifstream& ifs, std::vector<int>* int_vectors_sizes)
    {
        unsigned int memory = 0;

        for (int i = 0; i < int_vectors_sizes->size(); i++)
        {
            int size = (*int_vectors_sizes)[i];
            Serializable::i_buffer = new int[size];
            for (int i = 0; i < size; i++)
            {
                ifs.read((char *)&Serializable::i_buffer[i], sizeof(float));
                memory += sizeof(float);
            }
            populate_vector(*get_int_vectors()[i], Serializable::i_buffer, size);
        }

        return memory;
    }

    unsigned int load_floats(std::ifstream& ifs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_floats().size(); i++)
        {
            ifs.read((char *)get_floats()[i], sizeof(float));
            memory += sizeof(float);
        }

        return memory;
    }

    unsigned int load_ints(std::ifstream& ifs)
    {
        unsigned int memory = 0;

        for (int i = 0; i < get_ints().size(); i++)
        {
            ifs.read((char *)get_ints()[i], sizeof(int));
            memory += sizeof(int);
        }

        return memory;
    }

    unsigned int load_sizes_of_strings(std::ifstream& ifs, std::vector<int>* string_sizes)
    {
        unsigned int memory = 0;

        p_strings strings = get_strings();
        string_sizes->resize(strings.size());
        for (int i = 0; i < strings.size(); i++)
        {
            ifs.read((char *)&(*string_sizes)[i], sizeof(int));
        }

        for (int i = 0; i < string_sizes->size(); i++)
        {
            strings[i]->resize((*string_sizes)[i]);
        }

        return memory;
    }

    unsigned int load_strings(std::ifstream& ifs, std::vector<int>* string_sizes)
    {
        unsigned int memory = 0;

        p_strings strings = get_strings();
        for (int i = 0; i < string_sizes->size(); i++)
        {
            std::string &str = *strings[i];
            for (int j = 0; j < strings[i]->size(); j++)
            {
                ifs.read((char *)&str[j], sizeof(char));
                memory += sizeof(char);
            }
        }

        return memory;
    }

    inline static double *d_buffer { nullptr };
    inline static float *f_buffer { nullptr };
    inline static int *i_buffer { nullptr };

public:

    using v_vp_float = std::vector<std::vector<float> *>;
    using v_vp_int = std::vector<std::vector<int> *>;
    using p_ints = std::vector<int *>;
    using p_floats = std::vector<float *>;
    using p_strings = std::vector<std::string *>;

    virtual v_vp_float get_float_vectors() { return {}; };
    virtual v_vp_int get_int_vectors() { return {}; };
    virtual p_ints get_ints() { return {}; };
    virtual p_floats get_floats() { return {}; };
    virtual p_strings get_strings() { return {}; };

    unsigned int serialize(std::ofstream &ofs)
    {
        size = 0;

        int name_size = name.size();
        ofs.write((char*)&name_size, sizeof(int));

        for (int i = 0; i < name.size(); i++)
        {
            ofs.write((char*) &name[i], sizeof(char));
        }

        size += save_sizes_of_float_vectors(ofs);
        size += save_sizes_of_int_vectors(ofs);
        size += save_sizes_of_strings(ofs);

        size += save_float_vectors(ofs);
        size += save_int_vectors(ofs);

        size += save_strings(ofs);        
        size += save_floats(ofs);
        size += save_ints(ofs);

        return size;
    }

    unsigned int deserialize(std::ifstream &ifs)
    {
        size = 0;

        int name_size;

        ifs.read((char*)&name_size, sizeof(int));

        name.resize(name_size);

        for (int i = 0; i < name_size; i++)
        {
            ifs.read((char*) &name[i], sizeof(char));
        }

        std::vector<int> float_vectors_sizes;
        std::vector<int> int_vectors_sizes;
        std::vector<int> string_sizes;

        size += load_sizes_of_float_vectors(ifs, &float_vectors_sizes);
        size += load_sizes_of_int_vectors(ifs, &int_vectors_sizes);
        size += load_sizes_of_strings(ifs, &string_sizes);

        size += load_float_vectors(ifs, &float_vectors_sizes);
        size += load_int_vectors(ifs, &int_vectors_sizes);

        size += load_strings(ifs, &string_sizes);
        size += load_floats(ifs);
        size += load_ints(ifs);

        return size;
    }

    unsigned int save(const std::string& path)
    {
        std::ofstream ofs(path);
        serialize(ofs);
        ofs.close();

        return size;
    }

    unsigned int load(const std::string& path)
    {
        std::ifstream ifs(path);
        deserialize(ifs);
        ifs.close();

        return size;
    }

    unsigned int get_size() const
    {
        return size;
    }
};

struct Mesh : public Serializable
{
    std::vector<float> pos;
    std::vector<int> ind;
    std::vector<float> nor;
    std::vector<float> uvs;

    virtual v_vp_float get_float_vectors() override
    {
        return {
            &pos,
            &nor,
            &uvs
        };
    }

    virtual v_vp_int get_int_vectors() override
    {
        return {
            &ind
        };
    }

    void print()
    {
        LOG("pos");
        for (float p : pos)
            LOG(p);
        LOG("ind");
        for (int p : ind)
            LOG(p);
        LOG("nor");
        for (float p : nor)
            LOG(p);
        LOG("uvs");
        for (float p : uvs)
            LOG(p);
    }

    Mesh(const std::string name) : Serializable(name) {}
    Mesh() : Serializable() {}
};

int main()
{
    Mesh m1("Quad");
    m1.pos = { 1, 2, 3 };
    m1.ind = { 62, 27, 28, 92, 210 };
    m1.nor = { 10 };
    m1.uvs = { 2.1f, 2.2f, 10.1f };

    // Mesh m2("Cube");
    // m2.pos = { 113, 22, 53, 4, 6 };
    // m2.ind = { 211 };
    // m2.nor = { 123 };
    // m2.uvs = { 15.1f };
    
    std::ofstream ofs("meshes");
    int m1size = m1.serialize(ofs);
    // int m2size = m2.serialize(ofs);
    ofs.close();

    Mesh m3;
    m3.load("meshes"); 

    return 0;
}
