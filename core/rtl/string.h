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
bool operator==(const string& str1, const string& str2);

bool operator!=(const char* str1, const string& str2);
bool operator>(const char* str1, const string& str2);
bool operator<(const char* str1, const string& str2);

/// append str1 to str2
string operator+(const char* str1, const string& str2);
string operator+(const string& str1, const string& str2);



bool is_integer(const rtl::string& str);
bool is_integer(const char* str);
bool is_float(const rtl::string& str);
bool is_float(const char* str);



} // rtl

#endif // CORE_RTL_STRING_H_ 