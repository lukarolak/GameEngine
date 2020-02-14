#include "Assert.h"
#include <signal.h>
#ifndef NDEBUG
void __M_Assert(const char* expr_str, bool expr, const char* file, int line)
{
    if (!expr)
    {
        std::cerr << "Expected:\t" << expr_str << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

void __M_Assert(const char* expr_str, bool expr, const char* file, const char* msg, int line)
{
    if (!expr)
    {
        std::cerr << "Assert failed:\t" << msg << "\n"
            << "Expected:\t" << expr_str << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}
#endif
