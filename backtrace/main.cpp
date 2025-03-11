#include <cstring>
#include <iostream>
#include <execinfo.h>
#include <cxxabi.h>
#include <cstdlib>
#include <string>


void print_function(  std::ostream& stream, std::string str)
{
    int status;
    char *demangled = abi::__cxa_demangle(&str.c_str()[1], nullptr, nullptr, &status);
    stream << demangled << std::endl;
    std::free(demangled);
}

void stack_dump(int depth, std::ostream& stream)
{
    char    **buff;
    char    *begin, 
            *end;
    void    *callstack[128];
    int     frames;

    frames = backtrace(callstack, 128);
    buff = backtrace_symbols(callstack, frames);

    if (depth > frames)
        depth = frames;

    for (int i = 0; i < depth; ++i) {
        char *begin = strchr(buff[i], '(');
        char *end = strchr(buff[i], '+');
        print_function(stream ,{begin, end});
    }

    std::free(buff);
}

void function_b()
{
    stack_dump(3, std::cout); 
}

void function_a()
{ 
    function_b(); 
}

int main()
{
    function_a();
    return 0;
}


