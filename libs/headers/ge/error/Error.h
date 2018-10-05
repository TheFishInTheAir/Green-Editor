//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <string>
#include <vector>
#include <ge/util/PreprocessorUtil.h>
#define ge_Error_GENERATE(m) {ge::Error __generatedErr(m); ge_Error_ADDTRACE(__generatedErr); return __generatedErr;}
#define ge_Error_ADDTRACE(t) {if(t.isError())t.stack.push_back(std::string(__FILENAME__)+" : "+std::string(__FUNCTION__)+"("+std::to_string(__LINE__)+")\n");}

namespace ge
{
    struct Error
    {
        Error();

        Error(std::string err);
        ~Error();

        void addTrace()
        {
        }

        std::vector<std::string> stack;

        bool isError();

    private:

        std::string _msg;

        bool _caught;

        bool _isError;
    };
}