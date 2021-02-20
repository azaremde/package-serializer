#include <fstream>
#include <ostream>

#include <iostream>
#include <vector>

class Serializable
{
private:
    template <typename T>
    inline static void write_vector(std::ofstream &ofs, std::vector<T> vec)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            ofs.write((char *)&vec[i], sizeof(T));
        }
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

    void save_sizes_of_float_vectors(std::ofstream& ofs)
    {
        for (int i = 0; i < get_float_vectors().size(); i++)
        {
            std::vector<float> &vector = *get_float_vectors()[i];
            int size = vector.size();
            ofs.write((char *)&size, sizeof(int));
        }
    }

    void save_sizes_of_int_vectors(std::ofstream& ofs)
    {
        for (int i = 0; i < get_int_vectors().size(); i++)
        {
            std::vector<int> &vector = *get_int_vectors()[i];
            int size = vector.size();
            ofs.write((char *)&size, sizeof(int));
        }
    }

    void save_float_vectors(std::ofstream& ofs)
    {
        for (int i = 0; i < get_float_vectors().size(); i++)
        {
            std::vector<float> &vector = *get_float_vectors()[i];
            write_vector(ofs, vector);
        }
    }

    void save_int_vectors(std::ofstream& ofs)
    {
        for (int i = 0; i < get_int_vectors().size(); i++)
        {
            std::vector<int> &vector = *get_int_vectors()[i];
            write_vector(ofs, vector);
        }
    }

    void save_floats(std::ofstream& ofs)
    {
        for (int i = 0; i < get_floats().size(); i++)
        {
            ofs.write((char *)get_floats()[i], sizeof(float));
        }
    }

    void save_ints(std::ofstream& ofs)
    {
        for (int i = 0; i < get_ints().size(); i++)
        {
            ofs.write((char *)get_ints()[i], sizeof(int));
        }        
    }

    void save_sizes_of_strings(std::ofstream& ofs)
    {
        p_strings &strings = get_strings();
        for (int i = 0; i < strings.size(); i++)
        {
            int size = strings[i]->size();
            ofs.write((char *)&size, sizeof(int));
        }
    }

    void save_strings(std::ofstream& ofs)
    {
        p_strings &strings = get_strings();
        for (int i = 0; i < strings.size(); i++)
        {
            std::string &str = *strings[i];
            for (int j = 0; j < str.size(); j++)
            {
                ofs.write((char *)&str[j], sizeof(char));
            }
        }
    }

    std::vector<int>* load_sizes_of_float_vectors(std::ifstream& ifs)
    {
        v_vp_float &float_vectors = get_float_vectors();
        std::vector<int>* float_vectors_sizes = new std::vector<int>();
        float_vectors_sizes->resize(float_vectors.size());

        for (int i = 0; i < float_vectors.size(); i++)
        {
            ifs.read((char *)&(*float_vectors_sizes)[i], sizeof(int));
        }

        return float_vectors_sizes;
    }

    std::vector<int>* load_sizes_of_int_vectors(std::ifstream& ifs)
    {        
        v_vp_int &int_vectors = get_int_vectors();
        std::vector<int>* int_vectors_sizes = new std::vector<int>();
        int_vectors_sizes->resize(int_vectors.size());

        for (int i = 0; i < int_vectors.size(); i++)
        {
            ifs.read((char *)&(*int_vectors_sizes)[i], sizeof(int));
        }

        return int_vectors_sizes;
    }

    void load_float_vectors(std::ifstream& ifs, std::vector<int>* float_vectors_sizes)
    {
        for (int i = 0; i < float_vectors_sizes->size(); i++)
        {
            int size = (*float_vectors_sizes)[i];
            Serializable::f_buffer = new float[size];
            for (int i = 0; i < size; i++)
            {
                ifs.read((char *)&Serializable::f_buffer[i], sizeof(float));
            }
            populate_vector(*get_float_vectors()[i], Serializable::f_buffer, size);
        }
    }

    void load_int_vectors(std::ifstream& ifs, std::vector<int>* int_vectors_sizes)
    {
        for (int i = 0; i < int_vectors_sizes->size(); i++)
        {
            int size = (*int_vectors_sizes)[i];
            Serializable::i_buffer = new int[size];
            for (int i = 0; i < size; i++)
            {
                ifs.read((char *)&Serializable::i_buffer[i], sizeof(float));
            }
            populate_vector(*get_int_vectors()[i], Serializable::i_buffer, size);
        }
    }

    void load_floats(std::ifstream& ifs)
    {
        for (int i = 0; i < get_floats().size(); i++)
        {
            ifs.read((char *)get_floats()[i], sizeof(float));
        }
    }

    void load_ints(std::ifstream& ifs)
    {
        for (int i = 0; i < get_ints().size(); i++)
        {
            ifs.read((char *)get_ints()[i], sizeof(int));
        }
    }

    std::vector<int>* load_sizes_of_strings(std::ifstream& ifs)
    {
        p_strings strings = get_strings();
        std::vector<int>* string_sizes = new std::vector<int>();
        string_sizes->resize(strings.size());
        for (int i = 0; i < strings.size(); i++)
        {
            ifs.read((char *)&(*string_sizes)[i], sizeof(int));
        }

        for (int i = 0; i < string_sizes->size(); i++)
        {
            strings[i]->resize((*string_sizes)[i]);
        }

        return string_sizes;
    }

    void load_strings(std::ifstream& ifs, std::vector<int>* string_sizes)
    {
        p_strings strings = get_strings();
        for (int i = 0; i < string_sizes->size(); i++)
        {
            std::string &str = *strings[i];
            for (int j = 0; j < strings[i]->size(); j++)
            {
                ifs.read((char *)&str[j], sizeof(char));
            }
        }
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

    void serialize(std::ofstream &ofs)
    {
        save_sizes_of_float_vectors(ofs);
        save_sizes_of_int_vectors(ofs);
        save_sizes_of_strings(ofs);

        save_float_vectors(ofs);
        save_int_vectors(ofs);
        save_strings(ofs);
        
        save_floats(ofs);
        save_ints(ofs);
    }

    void deserialize(std::ifstream &ifs)
    {
        std::vector<int>* float_vectors_sizes = load_sizes_of_float_vectors(ifs);
        std::vector<int>* int_vectors_sizes = load_sizes_of_int_vectors(ifs);
        std::vector<int>* string_sizes = load_sizes_of_strings(ifs);

        load_float_vectors(ifs, float_vectors_sizes);
        load_int_vectors(ifs, int_vectors_sizes);
        load_strings(ifs, string_sizes);

        load_floats(ifs);
        load_ints(ifs);

        delete float_vectors_sizes;
        delete int_vectors_sizes;
        delete string_sizes;
    }

    void save(const std::string& path)
    {
        std::ofstream ofs(path);
        serialize(ofs);
        ofs.close();
    }

    void load(const std::string& path)
    {
        std::ifstream ifs(path);
        deserialize(ifs);
        ifs.close();
    }
};

class MyClass : public Serializable
{
public:
    std::string greetings;

    inline virtual p_strings get_strings()
    {
        return 
        {
            &greetings
        };
    }
};

// #define SAVE

#define LOG(x) std::cout << x << '\n'

int main()
{
#ifdef SAVE

    MyClass m1;
    m1.greetings = "Hello!";
    m1.save("my-class");

#else

    MyClass m2;
    m2.load("my-class");
    LOG(m2.greetings);

#endif

    return 0;
}
