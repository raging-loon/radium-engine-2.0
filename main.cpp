#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include "core/rtl/basic_string.h"
#include "core/memory/Memory.h"


int main(int argc, char** argv)
{

	rtl::basic_string<char> sd;

	sd.resize(10);
	
	sd = "hello";
	printf("%s\n", sd.data());
	printf("%c\n", sd[0]);
	sd[0] = 'j';
	printf("%s\n", sd.data());
	printf("Size = %zd\n",sd.length());
	
	return 0;
} 