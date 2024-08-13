#include <stdio.h>
#include "core/math/vec2.h"

int main(int argc, char** argv)
{
    rm::vec2 test(12.3352, 134);

    test *= 2;

    test = test.normalized();
    printf("%f, %f\n",test.x, test.y);
    return 0;
} 

  