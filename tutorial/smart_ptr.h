//
// Created by syh on 2022/3/30.
//

#ifndef CEREAL_SMART_PTR_H
#define CEREAL_SMART_PTR_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

using namespace  std;

class WeightInfo
{
public:
    WeightInfo();
    WeightInfo(int weightNo);

public:
    int getWeightNo() const;
    void setWeightNo(int value);

private:
    int WeightNo;
};

class WeightSequence {
    public:
        WeightSequence();
        WeightSequence(int jumpTime);
        WeightSequence(const WeightSequence&) = delete;
        WeightSequence& operator=(const WeightSequence&) = delete;
        ~WeightSequence() = default;

    public:
        int getJumpTime() const;
        void setJumpTime(int value);

    private:
        int JumpTime;
        vector<std::unique_ptr<WeightInfo> > WeightInfoList;
public:
//    const vector<std::unique_ptr<WeightInfo>> &getWeightInfoList() const;

    void setWeightInfoList(const vector<std::unique_ptr<WeightInfo>> &weightInfoList);
};


#endif //CEREAL_SMART_PTR_H
