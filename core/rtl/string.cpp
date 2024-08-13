#include "core/rtl/string.h"
#include <string.h>


bool rtl::operator==(const char* str1, const rtl::string& str2)
{
    return strcmp(str1, str2.c_str()) == 0;
}

bool rtl::operator!=(const char* str1, const rtl::string& str2)
{
    return strcmp(str1, str2.c_str()) != 0;
}

bool rtl::operator>(const char* str1, const rtl::string& str2)
{
    return strcmp(str1, str2.c_str()) > 0;
}

bool rtl::operator<(const char* str1, const rtl::string& str2)
{
    return strcmp(str1, str2.c_str()) < 0;
}

rtl::string rtl::operator+(const char* str1, const rtl::string& str2)
{
    rtl::string temp = str2;
    temp += str1;
    return temp;
}
