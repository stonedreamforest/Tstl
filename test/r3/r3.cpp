#include "stdio.h"
#include <iostream>
#include <tlist.hpp>
#include "../test.hpp"

int main() {
    Test::__init();
    Test::test_g_class();
    Test::test_l_class();
    Test::__destory();
    return 1;
}