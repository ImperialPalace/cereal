//
// Created by syh on 2022/3/30.
//

#include "smart_ptr.h"


///////////////////WeightInfo////////////////////
WeightInfo::WeightInfo()
{
}

WeightInfo::WeightInfo(int weightNo)
        : WeightNo(weightNo)
{
}

int WeightInfo::getWeightNo() const
{
    return WeightNo;
}

void WeightInfo::setWeightNo(int value)
{
    WeightNo = value;
}


///////////////////WeightSequence////////////////////
WeightSequence::WeightSequence()
{
}

WeightSequence::WeightSequence(int jumpTime)
        : JumpTime(jumpTime)
{
}

int WeightSequence::getJumpTime() const
{
    return JumpTime;
}

void WeightSequence::setJumpTime(int value)
{
    JumpTime = value;
}


int main()
{
    cout << "Hello Smart Ptr" << endl;
    unique_ptr<WeightInfo> w(new WeightInfo(10));

    cout << w->getWeightNo() << endl;
}
