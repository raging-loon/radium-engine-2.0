#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include "core/memory/Memory.h"


int main(int argc, char** argv)
{
	printf("Builded\n");
	
	rtl::copy_on_write<int> x;
	x.resize(10);

	rtl::copy_on_write<int> y = x;

	printf("x.size() = %d\ny.size() = %d\n", x.get_size(), y.get_size());


	x.resize(20);
	printf("x.size() = %d\ny.size() = %d\n", x.get_size(), y.get_size());

	return 0;
}