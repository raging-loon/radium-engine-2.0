#include <stdio.h>
#include "core/rtl/copy_on_write.h"
#include "core/rtl/string.h"
#include "core/memory/Memory.h"
#include "core/rtl/smart_ptr.h"

int main(int argc, char** argv)
{
	rtl::unique_ptr<int> t = rtl::make_unique<int>(1);

	rtl::unique_ptr<int> z = rtl::move(t);

	printf("%d\n", *z);

	return 0;
} 

