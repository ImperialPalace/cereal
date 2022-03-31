/*
 * @Description: desc
 * @Author: Firmin.Sun
 * @Date: 2022-03-31 11:31:53
 * @FilePath: /tutorial/vec_unique_ptr.cpp
 */

#include <iostream>
#include <memory>
#include <vector>

struct Base {
    void dispaly(){}
};

struct Derived : public Base {
    int name;
};


std::unique_ptr<Base> get()
{
    std::unique_ptr<Derived> derivedObject;
    derivedObject->name=11;

    std::vector<std::unique_ptr<Base>> vec;

    vec.push_back(std::move(derivedObject));
    vec.at(0).get();

    return std::move(vec.at(0)) ;
}


int main()
{
    std::unique_ptr<Derived> derivedObject;
    derivedObject->name=11;

    std::vector<std::unique_ptr<Base>> vec;
    
    vec.push_back(std::move(derivedObject));
    vec.push_back(get());

    vec.at(0)->dispaly();

//    auto a = vec.at(0).get();

}