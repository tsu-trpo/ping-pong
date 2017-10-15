//
// Created by manmoleculo on 10.10.17.
//

#include "GlobalVariables.h"
static GlobalVariables *instanceOfGlobalVariables = NULL;
GlobalVariables * GlobalVariables::globalVariables()
{
    if (instanceOfGlobalVariables == NULL) {
        instanceOfGlobalVariables = new GlobalVariables();
        instanceOfGlobalVariables->init();
        instanceOfGlobalVariables->deviceType = 1;
    }
    return instanceOfGlobalVariables;
}
bool GlobalVariables::init()
{
    if ( !Node::init() ) {
        return false;
    }
    return true;
}
std::string GlobalVariables::addDeviceSuffix(std::string string)
{
    switch (deviceType) {
        case 1:
            string += ".png";
            break;
        case 2:
            string += "-ipad.png";
            break;
        default:
            break;
    }
    return string;
}
