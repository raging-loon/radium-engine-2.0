#include "core/rtl/string.h"
#include <string.h>


bool rtl::operator==(const char* str1, const rtl::string& str2)
{
    return strcmp(str1, str2.c_str()) == 0;
}

bool rtl::operator==(const rtl::string& str1, const rtl::string& str2)
{
    return strcmp(str1.c_str(), str2.c_str()) == 0;
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

rtl::string rtl::operator+(const rtl::string& str1, const rtl::string& str2)
{
    rtl::string temp = str1;
    temp += str2;
    return temp;

}
