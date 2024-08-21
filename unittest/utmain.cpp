#include <stdio.h>
#include <gtest/gtest.h>
#include "rtl_tests.h"
#include "ecs/ecs_tests.h"
#include <glm.hpp>

#include <core/debug/seh.h>
#include <core/debug/globlog.h>
int main(int argc, char** argv)
{
    radium::setSEHHandlers();
    radium::GlobLoggers::init();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}