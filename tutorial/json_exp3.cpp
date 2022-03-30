//
// Created by syh on 2022/3/29.
//


#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <fstream>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <iostream>
#include <sstream>

using namespace std;
class Student
{
public:
    Student(){}
    Student(string name, int age)
            : m_strName(name),
              nAge(age)
    {
    }

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(cereal::make_nvp("m_strName__", m_strName), CEREAL_NVP(nAge)); // serialize things by passing them to the archive
    }

public:
    string m_strName;
    int nAge;

};


class MyData
{
public:
    MyData(int x = 100, int y = 200, int z = 300)
            : m_x(x),
              m_y(y),
              m_z(z)
    {
        unique_ptr<Student> st1(new Student("Jane", 26));
        unique_ptr<Student> st2(new Student("sun", 25));

        m_gStudent.push_back(std::move(st1));

        m_gStudent.push_back(std::move(st2));
    }
    int m_x, m_y, m_z;
    std::vector<int> idx = {1, 2, 3, 4, 5};

    std::vector<std::unique_ptr<Student> > m_gStudent;


    // This method lets cereal know which data members to serialize
    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(m_x), CEREAL_NVP(m_y), CEREAL_NVP(m_z), CEREAL_NVP(idx)); // serialize things by passing them to the archive
        archive(CEREAL_NVP(m_gStudent)); // serialize things by passing them to the archive
    }
};

int main()
{
    std::ofstream out;
    {
        out.open("out3.json", ios::trunc); // ios::trunc means clear the file before opening the file, because it is written, the file is created if it does not exist

        cereal::JSONOutputArchive cout_archive(std::cout);

        cereal::JSONOutputArchive archive(out);

        MyData m1;
        archive(cereal::make_nvp("m1", m1));
        cout_archive(cereal::make_nvp("m1", m1));
    }
    out.close();

    std::ifstream in;
    MyData m1;
    {
        in.open("out3.json", ios::in);
        cereal::JSONInputArchive archive(in);

        // Read out of order
        archive(cereal::make_nvp("m1", m1));
    }
    in.close();
}
