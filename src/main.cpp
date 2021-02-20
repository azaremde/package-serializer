#include <fstream>
#include <ostream>

#include <iostream>
#include <vector>

#define LOG(x) std::cout << x << '\n'


struct Mesh
{
    unsigned int positions_size { 0 };
    unsigned int indices_size   { 0 };
    unsigned int normals_size   { 0 };
    unsigned int uvs_size       { 0 };

    float* positions    { nullptr };
    int* indices        { nullptr };
    float* normals      { nullptr };
    float* uvs          { nullptr };

    void set_sizes()
    {
        positions_size = sizeof(positions) / sizeof(float) + 1;
        indices_size = sizeof(indices) / sizeof(int) + 1;
        normals_size = sizeof(normals) / sizeof(float) + 1;
        uvs_size = sizeof(uvs) / sizeof(float) + 1;
    }
};


int main()
{
    Mesh m1;
    m1.positions = new float[] { 1.1, 2.2, 3.3 };
    m1.indices = new int[] { -1, -2, -3, -4, -5, -6, 7, 8, 9, 10, 11, 12, 13 };
    m1.normals = new float[] { -1.5f, -2.5f };
    m1.uvs = new float[] { -5.5f, -8.5f, -13.5f, 25.3f, 12.8f };

    m1.set_sizes();
    LOG(m1.positions_size);
    LOG(m1.indices_size);
    LOG(m1.normals_size);
    LOG(m1.uvs_size);

    return 0;
}