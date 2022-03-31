//
// Created by syh on 2022/3/31.
//

/*
 * @Description: Main function
 * @Author: Firmin.Sun
 * @Date: 2022-03-15 18:52:31
 * @FilePath: /ibox-server_backend-grpc_cpp/IBoxServer/ibox-server.cpp
 */

//#include <iostream>
//#include <memory>
//#include <string>

//#include <grpcpp/ext/proto_server_reflection_plugin.h>
//#include <grpcpp/grpcpp.h>
//#include <grpcpp/health_check_service_interface.h>

//#include "protos/algroithm.grpc.pb.h"
//#include "AlgroithmServiceImpl.h"

//using grpc::Server;
//using grpc::ServerBuilder;
//using grpc::ServerContext;
//using grpc::Status;

//void RunServer()
//{
//    std::string server_address("0.0.0.0:50051");
//    AlgroithmServiceImpl service;

//    grpc::EnableDefaultHealthCheckService(true);
//    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
//    ServerBuilder builder;
//    // Listen on the given address without any authentication mechanism.
//    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//    // Register "service" as the instance through which we'll communicate with
//    // clients. In this case it corresponds to an *synchronous* service.
//    builder.RegisterService(&service);
//    // Finally assemble the server.
//    std::unique_ptr<Server> server(builder.BuildAndStart());
//    std::cout << "Server listening on " << server_address << std::endl;

//    // Wait for the server to shutdown. Note that some other thread must be
//    // responsible for shutting down the server for this call to ever return.
//    server->Wait();
//}


//class Student
//{
//public:
//    Student(){}
//    Student(string name, int age)
//            : m_strName(name),
//              nAge(age)
//    {
//    }

//    template <class Archive>
//    void serialize(Archive &archive)
//    {
//        archive(cereal::make_nvp("m_strName__", m_strName), CEREAL_NVP(nAge)); // serialize things by passing them to the archive
//    }

//public:
//    string m_strName;
//    int nAge;

//};


//class MyData
//{
//public:
//    MyData(int x = 100, int y = 200, int z = 300)
//            : m_x(x),
//              m_y(y),
//              m_z(z)
//    {
//        unique_ptr<Student> st1(new Student("Jane", 26));
//        unique_ptr<Student> st2(new Student("sun", 25));

//        m_gStudent.push_back(std::move(st1));

//        m_gStudent.push_back(std::move(st2));
//    }
//    int m_x, m_y, m_z;
//    std::vector<int> idx = {1, 2, 3, 4, 5};

//    std::vector<std::unique_ptr<Student> > m_gStudent;


//    // This method lets cereal know which data members to serialize
//    template <class Archive>
//    void serialize(Archive &archive)
//    {
//        archive(CEREAL_NVP(m_x), CEREAL_NVP(m_y), CEREAL_NVP(m_z), CEREAL_NVP(idx)); // serialize things by passing them to the archive
//        archive(CEREAL_NVP(m_gStudent)); // serialize things by passing them to the archive
//    }
//};

////int main(int argc, char **argv)
////{
//////    unique_ptr<BO_Request> m_boRequest(new BO_Request());
////    unique_ptr<MyData> m1(new MyData());
////    std::ofstream out;
////    {
////        out.open("out4.json", ios::trunc); // ios::trunc means clear the file before opening the file, because it is written, the file is created if it does not exist

////        cereal::JSONOutputArchive cout_archive(std::cout);

////        cereal::JSONOutputArchive archive(out);

////        //        archive(cereal::make_nvp("m_boRequest", m_boRequest));
////        archive(cereal::make_nvp("m1", m1));
////    }
////    out.close();

////    std::cout << "Current working directory: " << get_current_dir_name() << endl;

////    RunServer();

////    return 0;
////}




//
// Created by syh on 2022/3/29.
//


#include "cereal/types/unordered_map.hpp"
#include "cereal/types/memory.hpp"
#include <fstream>

#include "cereal/archives/binary.hpp"
#include "cereal/archives/portable_binary.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
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


class Bussiness
{
public:
    Bussiness(){
        this->m1=std::unique_ptr<MyData>(new MyData());
        this->m2=std::unique_ptr<MyData>(new MyData());
    }

public:
    void Serialize()
    {
        std::ofstream out;
        {
            out.open("out4.json", ios::trunc); // ios::trunc means clear the file before opening the file, because it is written, the file is created if it does not exist

            cereal::JSONOutputArchive cout_archive(std::cout);

            cereal::JSONOutputArchive archive(out);

            archive(cereal::make_nvp("m1", m1));
            cout_archive(cereal::make_nvp("m1", m1));
        }
        out.close();


        std::ifstream in;
        {
            in.open("out4.json", ios::in);
            cereal::JSONInputArchive archive(in);

            // Read out of order
            archive(cereal::make_nvp("m1", m2));
        }
        in.close();
    }


private:
    unique_ptr<MyData> m1;
    unique_ptr<MyData> m2;
};

void Serialize()
{
    unique_ptr<MyData> m1(new MyData());
    unique_ptr<MyData> m2(new MyData());

    std::ofstream out;
    {
        out.open("out4.json", ios::trunc); // ios::trunc means clear the file before opening the file, because it is written, the file is created if it does not exist

        cereal::JSONOutputArchive cout_archive(std::cout);

        cereal::JSONOutputArchive archive(out);

        archive(cereal::make_nvp("m1", m1));
        cout_archive(cereal::make_nvp("m1", m1));
    }
    out.close();


    std::ifstream in;
    {
        in.open("out4.json", ios::in);
        cereal::JSONInputArchive archive(in);

        // Read out of order
        archive(cereal::make_nvp("m1", m2));
    }
    in.close();
}

int main()
{
//    Bussiness* b1= new Bussiness();
//    b1->Serialize();

    Serialize();
    return 1;
}
