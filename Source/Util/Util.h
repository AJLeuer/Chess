#pragma once

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

using namespace std;

typedef unsigned long UniqueNumericIdentifier;


extern wstring_convert <std::codecvt_utf8 <wchar_t>> stringConverter;

string convertToString (const wstring & wide_string);

