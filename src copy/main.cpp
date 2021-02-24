#include "iris_cer.h"

#include <iostream>
#include <string>

#define LOG(x) std::cout << x << '\n'

struct Mesh : iris::cer::Serializable
{
    std::vector<float> vertices;
    std::vector<int> indices;
    std::vector<std::string> strings;

    virtual v_vp_string get_string_vectors()
    {
        return {
            &strings
        };
    }

    virtual v_vp_float get_float_vectors() {
        return {
            &vertices
        };
    }

    virtual v_vp_int get_int_vectors() {
        return {
            &indices
        };
    }

    void print()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            LOG(vertices[i]);
        }

        for (int i = 0; i < strings.size(); i++)
        {
            LOG(strings[i]);
        }

        // for (int i = 0; i < indices.size(); i++)
        // {
        //     LOG(indices[i]);
        // }
    }
};

int main()
{
    Mesh m1;
    // for (int i = 0; i < 200; i++)
    // {
    //     // m1.strings.emplace_back(std::to_string(i));
    //     m1.vertices.emplace_back(i);
    // }
    // m1.save("m1");
    m1.load("m1");
    m1.print();
}


// #include <fstream>
// #include <ostream>

// #include <iostream>
// #include <vector>
// #include <map>

// #define LOG(x) std::cout << x << '\n'

// class Serializable
// {
// protected:
//     std::string name;

//     unsigned int size /* in bytes */ { 0 };

//     Serializable(const std::string& name)
//     {
//         this->name = name;
//     }

//     Serializable() {}

// private:
//     template <typename T>
//     inline static unsigned int write_vector(std::ofstream &ofs, std::vector<T> vec)
//     {
//         unsigned int memory = 0;
        
//         for (int i = 0; i < vec.size(); i++)
//         {
//             ofs.write((char *)&vec[i], sizeof(T));
//             memory += sizeof(T);
//         }

//         return memory;
//     }

//     template <typename T>
//     inline static void populate_vector(std::vector<T> &vec, T *array, int size)
//     {
//         vec.resize(size);
//         for (int i = 0; i < size; i++)
//         {
//             vec[i] = array[i];
//         }
//     }

//     unsigned int save_name(std::ofstream &ofs)
//     {
//         unsigned int memory = 0;

//         int name_size = name.size();
//         ofs.write((char*)&name_size, sizeof(int));

//         for (int i = 0; i < name.size(); i++)
//         {
//             ofs.write((char*) &name[i], sizeof(char));
//         }

//         return memory;
//     }

//     unsigned int save_sizes_of_float_vectors(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_float_vectors().size(); i++)
//         {
//             std::vector<float> &vector = *get_float_vectors()[i];
//             int size = vector.size();
//             ofs.write((char *)&size, sizeof(int));
//             memory += sizeof(int);
//         }

//         return memory;
//     }

//     unsigned int save_sizes_of_int_vectors(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_int_vectors().size(); i++)
//         {
//             std::vector<int> &vector = *get_int_vectors()[i];
//             int size = vector.size();
//             ofs.write((char *)&size, sizeof(int));
//             memory += sizeof(int);
//         }

//         return memory;
//     }

//     unsigned int save_float_vectors(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_float_vectors().size(); i++)
//         {
//             std::vector<float> &vector = *get_float_vectors()[i];
//             memory += write_vector(ofs, vector);
//         }

//         return memory;
//     }

//     unsigned int save_int_vectors(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_int_vectors().size(); i++)
//         {
//             std::vector<int> &vector = *get_int_vectors()[i];
//             memory += write_vector(ofs, vector);
//         }

//         return memory;
//     }

//     unsigned int save_floats(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_floats().size(); i++)
//         {
//             ofs.write((char *)get_floats()[i], sizeof(float));
//             memory += sizeof(float);
//         }

//         return memory;
//     }

//     unsigned int save_ints(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_ints().size(); i++)
//         {
//             ofs.write((char *)get_ints()[i], sizeof(int));
//             memory += sizeof(int);
//         }       

//         return memory; 
//     }

//     unsigned int save_sizes_of_strings(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         p_strings &strings = get_strings();

//         for (int i = 0; i < strings.size(); i++)
//         {
//             int size = strings[i]->size();
//             ofs.write((char *)&size, sizeof(int));
//             memory += sizeof(int);
//         }

//         return memory;
//     }

//     unsigned int save_strings(std::ofstream& ofs)
//     {
//         unsigned int memory = 0;

//         p_strings &strings = get_strings();
//         for (int i = 0; i < strings.size(); i++)
//         {
//             std::string &str = *strings[i];
//             for (int j = 0; j < str.size(); j++)
//             {
//                 ofs.write((char *)&str[j], sizeof(char));
//                 memory += sizeof(char);
//             }
//         }

//         return memory;
//     }

//     unsigned int save_string_vectors(std::ofstream &ofs)
//     {
//         unsigned int memory = 0;

//         // Save amount of string vectors.
//         size_t amount_of_string_vectors = get_string_vectors().size();    
//         ofs.write((char*)&amount_of_string_vectors, sizeof(size_t));
//         memory += sizeof(size_t);

//         for (int i = 0; i < amount_of_string_vectors; i++)
//         {
//             // Save amount of strings in the current vector.
//             std::vector<std::string>& vector = *(get_string_vectors()[i]);
//             size_t strings_amount = vector.size();
//             ofs.write((char*)&strings_amount, sizeof(size_t));
//             memory += sizeof(size_t);

//             for (int j = 0; j < vector.size(); j++)
//             {
//                 // Save amount of characters in the current string.
//                 size_t amount_of_characters = vector[j].size();
//                 ofs.write((char*)&amount_of_characters, sizeof(size_t));
//                 memory += sizeof(size_t);
//             }

//             for (int j = 0; j < vector.size(); j++)
//             {
//                 for (int l = 0; l < vector[j].size(); l++)
//                 {
//                     // Save every single character.
//                     ofs.write((char*)&vector[j][l], sizeof(char));
//                     memory += sizeof(char);
//                 }
//             }
//         }

//         return memory;
//     }

//     unsigned int load_name(std::istream& ifs)
//     {
//         unsigned int memory = 0;

//         unsigned int name_size = 0;
//         ifs.read((char*)&name_size, sizeof(int));

//         if (name_size == 0) { return 0; }

//         memory += sizeof(int);

//         name.resize(name_size);
//         for (int i = 0; i < name_size; i++)
//         {
//             ifs.read((char*) &name[i], sizeof(char));
//             memory += sizeof(char);
//         }

//         return memory;
//     }

//     unsigned int load_sizes_of_float_vectors(std::ifstream& ifs, std::vector<int>* float_vectors_sizes)
//     {
//         unsigned int memory = 0;

//         v_vp_float &float_vectors = get_float_vectors();
//         float_vectors_sizes->resize(float_vectors.size());

//         for (int i = 0; i < float_vectors.size(); i++)
//         {
//             ifs.read((char *)&(*float_vectors_sizes)[i], sizeof(int));
//             memory += sizeof(int);
//         }

//         return memory;
//     }

//     unsigned int load_sizes_of_int_vectors(std::ifstream& ifs, std::vector<int>* int_vectors_sizes)
//     {   
//         unsigned int memory = 0;     

//         v_vp_int &int_vectors = get_int_vectors();
//         int_vectors_sizes->resize(int_vectors.size());

//         for (int i = 0; i < int_vectors.size(); i++)
//         {
//             ifs.read((char *)&(*int_vectors_sizes)[i], sizeof(int));
//         }

//         return memory;
//     }

//     unsigned int load_float_vectors(std::ifstream& ifs, std::vector<int>* float_vectors_sizes)
//     {
//         unsigned int memory = 0;
        
//         for (int i = 0; i < float_vectors_sizes->size(); i++)
//         {
//             int size = (*float_vectors_sizes)[i];
//             Serializable::f_buffer = new float[size];
//             for (int i = 0; i < size; i++)
//             {
//                 ifs.read((char *)&Serializable::f_buffer[i], sizeof(float));
//                 memory += sizeof(float);
//             }
//             populate_vector(*get_float_vectors()[i], Serializable::f_buffer, size);
//         }

//         return memory;
//     }

//     unsigned int load_int_vectors(std::ifstream& ifs, std::vector<int>* int_vectors_sizes)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < int_vectors_sizes->size(); i++)
//         {
//             int size = (*int_vectors_sizes)[i];
//             Serializable::i_buffer = new int[size];
//             for (int i = 0; i < size; i++)
//             {
//                 ifs.read((char *)&Serializable::i_buffer[i], sizeof(float));
//                 memory += sizeof(float);
//             }
//             populate_vector(*get_int_vectors()[i], Serializable::i_buffer, size);
//         }

//         return memory;
//     }

//     unsigned int load_floats(std::ifstream& ifs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_floats().size(); i++)
//         {
//             ifs.read((char *)get_floats()[i], sizeof(float));
//             memory += sizeof(float);
//         }

//         return memory;
//     }

//     unsigned int load_ints(std::ifstream& ifs)
//     {
//         unsigned int memory = 0;

//         for (int i = 0; i < get_ints().size(); i++)
//         {
//             ifs.read((char *)get_ints()[i], sizeof(int));
//             memory += sizeof(int);
//         }

//         return memory;
//     }

//     unsigned int load_sizes_of_strings(std::ifstream& ifs, std::vector<int>* string_sizes)
//     {
//         unsigned int memory = 0;

//         p_strings strings = get_strings();
//         string_sizes->resize(strings.size());
//         for (int i = 0; i < strings.size(); i++)
//         {
//             ifs.read((char *)&(*string_sizes)[i], sizeof(int));
//         }

//         for (int i = 0; i < string_sizes->size(); i++)
//         {
//             strings[i]->resize((*string_sizes)[i]);
//         }

//         return memory;
//     }

//     unsigned int load_strings(std::ifstream& ifs, std::vector<int>* string_sizes)
//     {
//         unsigned int memory = 0;

//         p_strings strings = get_strings();
//         for (int i = 0; i < string_sizes->size(); i++)
//         {
//             std::string &str = *strings[i];
//             for (int j = 0; j < strings[i]->size(); j++)
//             {
//                 ifs.read((char *)&str[j], sizeof(char));
//                 memory += sizeof(char);
//             }
//         }

//         return memory;
//     }

//     unsigned int load_string_vectors(std::ifstream &ifs)
//     {
//         unsigned int memory = 0;

//         // Load amount of string vectors.
//         size_t amount_of_string_vectors = 0;
//         ifs.read((char*)&amount_of_string_vectors, sizeof(size_t));
//         memory += sizeof(size_t);

//         v_vp_string string_vecs = get_string_vectors();
//         string_vecs.resize(amount_of_string_vectors);

//         for (int i = 0; i < amount_of_string_vectors; i++)
//         {
//             // Load amount of strings in the current vector.
//             size_t amount_of_strings = 0;
//             ifs.read((char*)&amount_of_strings, sizeof(size_t));
//             memory += sizeof(size_t);
//             string_vecs[i]->resize(amount_of_strings);

//             for (int j = 0; j < string_vecs[i]->size(); j++)
//             {
//                 // Load amount of characters.
//                 size_t amount_of_characters = 0;
//                 ifs.read((char*)&amount_of_characters, sizeof(size_t));
//                 memory += sizeof(size_t);
//                 (*string_vecs[i])[j].resize(amount_of_characters);
//             }

//             for (int j = 0; j < (*string_vecs[i]).size(); j++)
//             {
//                 std::string& str = (*string_vecs[i])[j];
                
//                 for (int l = 0; l < str.size(); l++)
//                 {
//                     // Load every single character.
//                     ifs.read((char*)&str[l], sizeof(char));
//                     memory += sizeof(char);
//                 }
//             }
//         }

//         return memory;
//     }

//     inline static double *d_buffer { nullptr };
//     inline static float *f_buffer { nullptr };
//     inline static int *i_buffer { nullptr };

// public:

//     using v_vp_float = std::vector<std::vector<float> *>;
//     using v_vp_int = std::vector<std::vector<int> *>;
//     using v_vp_string = std::vector<std::vector<std::string> *>;
//     using p_ints = std::vector<int *>;
//     using p_floats = std::vector<float *>;
//     using p_strings = std::vector<std::string *>;

//     virtual v_vp_float get_float_vectors() { return {}; };
//     virtual v_vp_int get_int_vectors() { return {}; };
//     virtual v_vp_string get_string_vectors() { return {}; };
//     virtual p_ints get_ints() { return {}; };
//     virtual p_floats get_floats() { return {}; };
//     virtual p_strings get_strings() { return {}; };

//     std::string get_name() const
//     {
//         return name;
//     }

//     unsigned int serialize(std::ofstream &ofs)
//     {
//         size = 0;

//         size += save_name(ofs);

//         size += save_sizes_of_float_vectors(ofs);
//         size += save_sizes_of_int_vectors(ofs);
//         size += save_sizes_of_strings(ofs);

//         size += save_float_vectors(ofs);
//         size += save_int_vectors(ofs);

//         size += save_strings(ofs);        
//         size += save_floats(ofs);
//         size += save_ints(ofs);

//         size += save_string_vectors(ofs);

//         return size;
//     }

//     unsigned int deserialize(std::ifstream &ifs)
//     {
//         size = 0;

//         std::vector<int> float_vectors_sizes;
//         std::vector<int> int_vectors_sizes;
//         std::vector<int> string_sizes;

//         size += load_name(ifs);

//         size += load_sizes_of_float_vectors(ifs, &float_vectors_sizes);
//         size += load_sizes_of_int_vectors(ifs, &int_vectors_sizes);
//         size += load_sizes_of_strings(ifs, &string_sizes);

//         size += load_float_vectors(ifs, &float_vectors_sizes);
//         size += load_int_vectors(ifs, &int_vectors_sizes);

//         size += load_strings(ifs, &string_sizes);
//         size += load_floats(ifs);
//         size += load_ints(ifs);
        
//         size += load_string_vectors(ifs);

//         return size;
//     }

//     unsigned int save(const std::string& path)
//     {
//         std::ofstream ofs(path);
//         serialize(ofs);
//         ofs.close();

//         return size;
//     }

//     unsigned int load(const std::string& path)
//     {
//         std::ifstream ifs(path);
//         deserialize(ifs);
//         ifs.close();

//         return size;
//     }

//     unsigned int get_size() const
//     {
//         return size;
//     }
// };

// struct Mesh : public Serializable
// {
//     std::vector<float> pos;
//     std::vector<int> ind;
//     std::vector<float> nor;
//     std::vector<float> uvs;

//     virtual v_vp_float get_float_vectors() override
//     {
//         return {
//             &pos,
//             &nor,
//             &uvs
//         };
//     }

//     virtual v_vp_int get_int_vectors() override
//     {
//         return {
//             &ind
//         };
//     }

//     void print()
//     {
//         LOG("Name: " << name);

//         LOG("pos");
//         for (float p : pos)
//             LOG(p);
//         LOG("ind");
//         for (int p : ind)
//             LOG(p);
//         LOG("nor");
//         for (float p : nor)
//             LOG(p);
//         LOG("uvs");
//         for (float p : uvs)
//             LOG(p);
//     }

//     Mesh(const std::string name) : Serializable(name) {}
//     Mesh() : Serializable() {}
// };

// struct Table : public Serializable
// {
//     std::string                 main_file;
//     std::vector<std::string>    keys;
//     std::vector<int>            values;

//     p_strings   get_strings() override { return { &main_file }; }
//     v_vp_string get_string_vectors() override { return { &keys }; }
//     v_vp_int    get_int_vectors() override { return { &values }; }

//     void push(const std::string& key, int value)
//     {
//         keys.emplace_back(key);
//         values.emplace_back(value);
//     }

//     size_t size()
//     {
//         return keys.size();
//     }

//     int get(const std::string& key)
//     {
//         int index = -1;
//         for (int i = 0; i < keys.size(); i++)
//         {
//             if (keys[i] == key)
//             {
//                 index = i;
//             }
//         }

//         return index == -1 ? index : values[index];
//     }
// };

// template <typename T>
// Table* create_table(std::vector<T> objects, const std::string& path)
// {
//     Table* result = new Table();
//     result->main_file = path;

//     std::ofstream ofs(path);
//     for (int i = 0; i < objects.size(); i++)
//     {
//         int pos = ofs.tellp();
//         objects[i].serialize(ofs);
//         result->push(objects[i].get_name(), pos);
//     }
//     ofs.close();

//     result->save(path + ".toc");

//     return result;
// }

// template <typename T>
// T* load_one(const std::string& package_path, const std::string& key)
// {
//     T* result = new T();

//     Table* table = new Table();
//     table->load(package_path + ".toc");

//     int asset_position_in_file = table->get(key);
//     std::ifstream ifs(package_path);
//     ifs.seekg(asset_position_in_file);
//     result->deserialize(ifs);
//     ifs.close();

//     return result;
// }

// template <typename T>
// T* load_one(Table* table, const std::string& key)
// {
//     T* result = new T();

//     int asset_position_in_file = table->get(key);
//     std::ifstream ifs(table->main_file);
//     ifs.seekg(asset_position_in_file);
//     result->deserialize(ifs);
//     ifs.close();

//     return result;
// }

// int main()
// {
//     // Mesh m1("assets/cube.obj");
//     // m1.ind = { 1, 2, 3 };
//     // Mesh m2("assets/mesh.fbx");
//     // m2.pos = { 0, 2 };

//     // Table* t = create_table<Mesh>({ m1, m2 }, "meshes.iris");
//     // LOG(t->get("assets/cube.obj"));
//     // LOG(t->get("assets/mesh.fbx"));

//     Mesh* m1 = load_one<Mesh>("meshes.iris", "assets/mesh.fbx");
//     m1->print();

//     // std::ofstream ofs("m");
//     // m1.serialize(ofs);
//     // m2.serialize(ofs);
//     // ofs.close();

//     // std::ifstream ifs("m");
//     // m1.deserialize(ifs);
//     // ifs.close();

//     // m1.print();

//     // Mesh* m1 = load_t<Mesh>("meshes.iris", "assets/meshes/mesh.fbx");
//     // delete m1;

//     // std::vector<Mesh>* meshes = load_table<Mesh>("meshes.iris");

//     // delete meshes;

//     // std::string m1name = "assets/meshes/mesh.fbx";
//     // std::string m2name = "assets/meshes/chars/base.obj";

//     // Mesh m1(m1name);
//     // m1.pos = { 1, 2, 3 };

//     // Mesh m2(m2name);
//     // m2.ind = { 28, 29, 30, 31, 32, 33 };

//     // create_table({ m1, m2 }, "meshes.iris");

//     // std::ofstream ofs("meshes.iris");
//     // m1.serialize(ofs);
//     // m2.serialize(ofs);
//     // ofs.close();

//     // LOG(m1.get_size());
//     // LOG(m2.get_size());

//     return 0;
// }
