#ifndef CORE_RTL_STRING_H_
#define CORE_RTL_STRING_H_

#include "basic_string.h"
#include <math.h>
#include <string.h>
namespace rtl
{

using string = basic_string<char>;
using wstring = basic_string<wchar_t>;


bool operator==(const char* str1, const string& str2);
bool operator!=(const char* str1, const string& str2);
bool operator>(const char* str1, const string& str2);
bool operator<(const char* str1, const string& str2);

/// append str1 to str2
string operator+(const char* str1, const string& str2);







} // rtl

#endif // CORE_RTL_STRING_H_ 