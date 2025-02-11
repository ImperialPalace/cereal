//
// Created by syh on 2022/3/29.
//

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <iostream>
#include <fstream>

using namespace std;

class MyData
{
public:
    MyData(int x = 100, int y = 200, int z = 300)
            : m_x(x),
              m_y(y),
              m_z(z)
    {
    }
    int m_x, m_y, m_z;
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // This method lets cereal know which data members to serialize
    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(m_x, m_y, m_z, CEREAL_NVP(vec)); // serialize things by passing them to the archive
    }
};

int main()
{
    std::ofstream out;
    {
        out.open("out.json", ios::trunc); // ios::trunc means clear the file before opening the file, because it is written, the file is created if it does not exist

        cereal::JSONOutputArchive archive(out);
        bool arr[] = {true, false};
        std ::vector<int> vec = {1, 2, 3, 4, 5};

        MyData m1;
        archive(cereal::make_nvp("vector", vec), CEREAL_NVP(arr));
    }
    out.close();

    std::ifstream in;
    bool arr[] = {0};
    std ::vector<int> vec = {};
    {
        in.open("out.json", ios::in);
        cereal::JSONInputArchive archive(in);

        // Read out of order
        archive(CEREAL_NVP(arr));
        archive(cereal::make_nvp("vector", vec));
    }
    in.close();
}
