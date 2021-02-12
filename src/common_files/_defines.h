/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


#define __STDC_WANT_SECURE_LIB__ 1 //-V2573


typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint;
typedef unsigned long long uint64;
typedef const char        *pchar;


#define SAFE_DELETE(x) if(x != nullptr) { delete x; x = nullptr; }
