#include "iris_cer.h"

struct Mesh : Ser
{
    std::vector<float> pos;

    std::vector<float>* get_float_vector1()
    {
        return &pos;
    }

    void print()
    {
        for (float p : pos)
            LOG(p);
    }
};

int main()
{
    Mesh mesh;

    for (int i = 0; i < 200; i++)
    {
        mesh.pos.emplace_back(i);
    }

    mesh.save("mesh.i"); 
    mesh.pos.clear();
    mesh.load("mesh.i");

    mesh.print();

    return 0;
}