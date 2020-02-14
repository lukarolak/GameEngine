#pragma once
#include <iostream>
#include <string>
#ifndef NDEBUG
void __M_Assert(const char* expr_str, bool expr, const char* file, int line);
void __M_Assert(const char* expr_str, bool expr, const char* file, const char* msg, int line);

#define ENG_ASSERT_EXPR_MSG(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg);
#define ENG_ASSERT_EXPR(Expr) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__);

#define GET_MACRO(_1, _2, NAME, ...) NAME
#define ENG_ASSERT(...) GET_MACRO(__VA_ARGS__, ENG_ASSERT_EXPR_MSG, ENG_ASSERT_EXPR)(__VA_ARGS__)

#else
#define ENG_ASSERT(Expr, Msg)
#define ENG_ASSERT(Expr)
#endif