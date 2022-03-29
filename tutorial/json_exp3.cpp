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

// struct MyRecord
//{
//   uint8_t x, y;
//   float z;

//  template <class Archive>
//  void serialize( Archive & ar )
//  {
//    ar( x, y, z );
//  }
//};

// struct SomeData
//{
//   int32_t id;
//   MyRecord data;

//  template <class Archive>
//  void save( Archive & ar ) const
//  {
//    ar( data );
//  }

//  template <class Archive>
//  void load( Archive & ar )
//  {
//    static int32_t idGen = 0;
//    id = idGen++;
//    ar( data );
//  }
//};

// int main()
//{
//   std::ofstream os("out.cereal", std::ios::binary);
//   cereal::BinaryOutputArchive archive( os );

//  SomeData myData;
//  myData.id = 1000;
//  myData.data.x = 10;
//  myData.data.y = 20;
//  myData.data.z = 30;

//  archive( myData );

//  myData.save(archive);

//  SomeData myData1;

//  myData1.load(archive);
//  return 0;
//}

class MyData
{
public:
    MyData(int x = 100, int y = 200, int z = 300)
            : x(x),
              y(y),
              z(z)
    {
    }
    int x, y, z;
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // This method lets cereal know which data members to serialize
    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(x, y, z, CEREAL_NVP(vec)); // serialize things by passing them to the archive
    }
};

// int main()
//{
//   std::stringstream ss; // any stream can be used

//  {
//    cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

//    MyData m1, m2, m3;
//    oarchive(m1, m2, m3); // Write the data to the archive
//  }                       // archive goes out of scope, ensuring all contents are flushed

//  {
//    cereal::BinaryInputArchive iarchive(ss); // Create an input archive

//    MyData m4, m5, m6;
//    iarchive(m4, m5, m6); // Read the data from the archive
//  }
//}

// int main()
//{
//   {
//     std::ofstream os("data.xml");
//     cereal::XMLOutputArchive archive(os);

//    MyData m1;
//    int someInt;
//    double d;

//    archive( CEREAL_NVP(m1), // Names the output the same as the variable name
//             someInt,        // No NVP - cereal will automatically generate an enumerated name
//             cereal::make_nvp("this_name_is_way_better", d) ); // specify a name of your choosing
//  }

//  {
//    std::ifstream is("data.xml");
//    cereal::XMLInputArchive archive(is);

//    MyData m1;
//    int someInt;
//    double d;

//    archive( m1, someInt, d ); // NVPs not strictly necessary when loading
//                               // but could be used (even out of order)
//  }
//}

int main()
{
    //  std::ofstream os("data.json");
    //  cereal::JSONOutputArchive archive(os);
    ////  cereal::JSONOutputArchive archive(std::cout);
    //  MyData m1;

    ////  bool arr[] = {true, false};
    ////  std::vector<int> vec = {1, 2, 3, 4, 5};
    //  archive(m1,m1);

    //  std::ifstream is("data.json", ios_base::in);
    //  cereal::JSONInputArchive ar(is);

    //  ar( cereal::make_nvp("myData", m1) );

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
