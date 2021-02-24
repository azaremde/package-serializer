#include <fstream>
#include <ostream>

#include <vector>
#include <map>

#include <iostream>
#define LOG(x) std::cout << x << '\n'

namespace iris {
namespace cer {

class Serializable
{
protected:
    std::string name;

    Serializable(const std::string& name)
    {
        this->name = name;
    }

    Serializable() {}

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

    void save_name(std::ofstream &ofs)
    {
        int name_size = name.size();
        ofs.write((char*)&name_size, sizeof(int));

        for (int i = 0; i < name.size(); i++)
        {
            ofs.write((char*) &name[i], sizeof(char));
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

    void save_string_vectors(std::ofstream &ofs)
    {
        // Save amount of string vectors.
        size_t amount_of_string_vectors = get_string_vectors().size();    
        ofs.write((char*)&amount_of_string_vectors, sizeof(size_t));

        for (int i = 0; i < amount_of_string_vectors; i++)
        {
            // Save amount of strings in the current vector.
            std::vector<std::string>& vector = *(get_string_vectors()[i]);
            size_t strings_amount = vector.size();
            ofs.write((char*)&strings_amount, sizeof(size_t));

            for (int j = 0; j < vector.size(); j++)
            {
                // Save amount of characters in the current string.
                size_t amount_of_characters = vector[j].size();
                ofs.write((char*)&amount_of_characters, sizeof(size_t));
            }

            for (int j = 0; j < vector.size(); j++)
            {
                for (int l = 0; l < vector[j].size(); l++)
                {
                    // Save every single character.
                    ofs.write((char*)&vector[j][l], sizeof(char));
                }
            }
        }
    }

    void SAVE_FLOATS(std::ofstream &ofs)
    {
        // Save amount of string vectors.
        size_t amount_of_string_vectors = get_float_vectors().size();    
        ofs.write((char*)&amount_of_string_vectors, sizeof(size_t));

        for (int i = 0; i < amount_of_string_vectors; i++)
        {
            // Save amount of strings in the current vector.
            std::vector<float>& vector = *(get_float_vectors()[i]);
            size_t strings_amount = vector.size();
            ofs.write((char*)&strings_amount, sizeof(size_t));

            // for (int j = 0; j < vector.size(); j++)
            // {
            //     // Save amount of characters in the current string.
            //     size_t amount_of_characters = vector[j].size();
            //     ofs.write((char*)&amount_of_characters, sizeof(size_t));
            // }

            for (int j = 0; j < vector.size(); j++)
            {
                // for (int l = 0; l < vector[j].size(); l++)
                // {
                    // Save every single character.
                    ofs.write((char*)&vector[j], sizeof(float));
                // }
            }
        }
    }

    void load_name(std::istream& ifs)
    {
        unsigned int name_size = 0;
        ifs.read((char*)&name_size, sizeof(int));

        if (name_size == 0) { return; }

        name.resize(name_size);
        for (int i = 0; i < name_size; i++)
        {
            ifs.read((char*) &name[i], sizeof(char));
        }
    }

    void load_sizes_of_float_vectors(std::ifstream& ifs, std::vector<int>* float_vectors_sizes)
    {
        v_vp_float &float_vectors = get_float_vectors();
        float_vectors_sizes->resize(float_vectors.size());

        for (int i = 0; i < float_vectors.size(); i++)
        {
            ifs.read((char *)&(*float_vectors_sizes)[i], sizeof(int));
        }
    }

    void load_sizes_of_int_vectors(std::ifstream& ifs, std::vector<int>* int_vectors_sizes)
    {   
        v_vp_int &int_vectors = get_int_vectors();
        int_vectors_sizes->resize(int_vectors.size());

        for (int i = 0; i < int_vectors.size(); i++)
        {
            ifs.read((char *)&(*int_vectors_sizes)[i], sizeof(int));
        }
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

    void load_sizes_of_strings(std::ifstream& ifs, std::vector<int>* string_sizes)
    {
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

    void load_string_vectors(std::ifstream &ifs)
    {
        // Load amount of string vectors.
        size_t amount_of_string_vectors = 0;
        ifs.read((char*)&amount_of_string_vectors, sizeof(size_t));

        v_vp_string string_vecs = get_string_vectors();
        string_vecs.resize(amount_of_string_vectors);

        for (int i = 0; i < amount_of_string_vectors; i++)
        {
            // Load amount of strings in the current vector.
            size_t amount_of_strings = 0;
            ifs.read((char*)&amount_of_strings, sizeof(size_t));
            string_vecs[i]->resize(amount_of_strings);

            for (int j = 0; j < string_vecs[i]->size(); j++)
            {
                // Load amount of characters.
                size_t amount_of_characters = 0;
                ifs.read((char*)&amount_of_characters, sizeof(size_t));
                (*string_vecs[i])[j].resize(amount_of_characters);
            }

            for (int j = 0; j < (*string_vecs[i]).size(); j++)
            {
                std::string& str = (*string_vecs[i])[j];
                
                for (int l = 0; l < str.size(); l++)
                {
                    // Load every single character.
                    ifs.read((char*)&str[l], sizeof(char));
                }
            }
        }
    }

    void LOAD_FLOATS(std::ifstream &ifs)
    {
        // Load amount of string vectors.
        size_t amount_of_string_vectors = 0;
        ifs.read((char*)&amount_of_string_vectors, sizeof(size_t));

        v_vp_float string_vecs = get_float_vectors();
        string_vecs.resize(amount_of_string_vectors);

        for (int i = 0; i < amount_of_string_vectors; i++)
        {
            // Load amount of strings in the current vector.
            size_t amount_of_strings = 0;
            ifs.read((char*)&amount_of_strings, sizeof(size_t));
            string_vecs[i]->clear();
            string_vecs[i]->resize(amount_of_strings);

            // for (int j = 0; j < string_vecs[i]->size(); j++)
            // {
            //     // Load amount of characters.
            //     size_t amount_of_characters = 0;
            //     ifs.read((char*)&amount_of_characters, sizeof(size_t));
            //     (*string_vecs[i])[j].resize(amount_of_characters);
            // }

            for (int j = 0; j < (*string_vecs[i]).size(); j++)
            {
                float& str = (*string_vecs[i])[j];
                
                // for (int l = 0; l < str.size(); l++)
                // {
                    // Load every single character.
                // }
            }
            float* f = new float[amount_of_strings];
            ifs.read((char*)&f[0], sizeof(float) * amount_of_strings);
        }
    }

    inline static double *d_buffer { nullptr };
    inline static float *f_buffer { nullptr };
    inline static int *i_buffer { nullptr };

public:

    using v_vp_float = std::vector<std::vector<float> *>;
    using v_vp_int = std::vector<std::vector<int> *>;
    using v_vp_string = std::vector<std::vector<std::string> *>;
    using p_ints = std::vector<int *>;
    using p_floats = std::vector<float *>;
    using p_strings = std::vector<std::string *>;

    virtual v_vp_float get_float_vectors() { return {}; };
    virtual v_vp_int get_int_vectors() { return {}; };
    virtual v_vp_string get_string_vectors() { return {}; };
    virtual p_ints get_ints() { return {}; };
    virtual p_floats get_floats() { return {}; };
    virtual p_strings get_strings() { return {}; };

    std::string get_name() const
    {
        return name;
    }

    void serialize(std::ofstream &ofs)
    {
        save_name(ofs);

        // save_sizes_of_float_vectors(ofs);

        save_sizes_of_int_vectors(ofs);
        save_sizes_of_strings(ofs);

        // save_float_vectors(ofs);
        save_int_vectors(ofs);
        save_strings(ofs);

        save_floats(ofs);
        save_ints(ofs);

        save_string_vectors(ofs);

        SAVE_FLOATS(ofs);
    }

    void deserialize(std::ifstream &ifs)
    {
        std::vector<int> float_vectors_sizes;
        std::vector<int> int_vectors_sizes;
        std::vector<int> string_sizes;

        load_name(ifs);

        // load_sizes_of_float_vectors(ifs, &float_vectors_sizes);

        load_sizes_of_int_vectors(ifs, &int_vectors_sizes);
        load_sizes_of_strings(ifs, &string_sizes);

        // load_float_vectors(ifs, &float_vectors_sizes);
        load_int_vectors(ifs, &int_vectors_sizes);
        load_strings(ifs, &string_sizes);

        load_floats(ifs);
        load_ints(ifs);        

        load_string_vectors(ifs);

        LOAD_FLOATS(ifs);
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

struct Table : public Serializable
{
    std::string                 main_file;
    std::vector<std::string>    keys;
    std::vector<int>            values;

    p_strings   get_strings() override { return { &main_file }; }
    v_vp_string get_string_vectors() override { return { &keys }; }
    v_vp_int    get_int_vectors() override { return { &values }; }

    void push(const std::string& key, int value)
    {
        keys.emplace_back(key);
        values.emplace_back(value);
    }

    size_t size()
    {
        return keys.size();
    }

    int get(const std::string& key)
    {
        int index = -1;
        for (int i = 0; i < keys.size(); i++)
        {
            if (keys[i] == key)
            {
                index = i;
            }
        }

        return index == -1 ? index : values[index];
    }
};

template <typename T>
Table* create_table(std::vector<T> objects, const std::string& path)
{
    Table* result = new Table();
    result->main_file = path;

    std::ofstream ofs(path);
    for (int i = 0; i < objects.size(); i++)
    {
        int pos = ofs.tellp();
        objects[i].serialize(ofs);
        result->push(objects[i].get_name(), pos);
    }
    ofs.close();

    result->save(path + ".toc");

    return result;
}

template <typename T>
T* load_one(const std::string& package_path, const std::string& key)
{
    T* result = new T();

    Table* table = new Table();
    table->load(package_path + ".toc");

    int asset_position_in_file = table->get(key);
    std::ifstream ifs(package_path);
    ifs.seekg(asset_position_in_file);
    result->deserialize(ifs);
    ifs.close();

    return result;
}

template <typename T>
T* load_one(Table* table, const std::string& key)
{
    T* result = new T();

    int asset_position_in_file = table->get(key);
    std::ifstream ifs(table->main_file);
    ifs.seekg(asset_position_in_file);
    result->deserialize(ifs);
    ifs.close();

    return result;
}

}
}
