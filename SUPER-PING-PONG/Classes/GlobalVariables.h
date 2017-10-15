//
// Created by manmoleculo on 10.10.17.
//

#ifndef GlobalVariables_h
#define GlobalVariables_h
#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class GlobalVariables : public Node {
public:
CC_SYNTHESIZE(int, deviceType, DeviceType); // 1 is iphone, 2 is ipad
    static GlobalVariables * globalVariables();
    virtual bool init();
    std::string addDeviceSuffix(std::string string);
};
#endif /* GlobalVariables_h */