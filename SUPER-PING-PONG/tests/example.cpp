#include <gtest/gtest.h>
#include "AppDelegate.h"
 
USING_NS_CC;
 
// Application::getInstance возвращает не nullptr
TEST(Application, getInstance)
{
    AppDelegate app;
    ASSERT_TRUE(Application::getInstance());
}
