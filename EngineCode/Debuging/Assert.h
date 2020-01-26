#pragma once
#include <iostream>

#ifndef NDEBUG
void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg)
{
    if (!expr)
    {
        std::cerr << "Assert failed:\t" << msg << "\n"
            << "Expected:\t" << expr_str << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}
void __M_Assert(const char* expr_str, bool expr, const char* file, int line)
{
    if (!expr)
    {
        std::cerr << "Expected:\t" << expr_str << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

#define ENG_ASSERT(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#define ENG_ASSERT(Expr) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__)
#else
#define ENG_ASSERT(Expr, Msg) ;
#define ENG_ASSERT(Expr)
#endif