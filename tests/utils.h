#pragma once

#include <string>


namespace dgb
{
    namespace utils
    {
        std::string tolower(const std::string& oldStr)
        {
            std::string newStr = oldStr;
            for (std::string::size_type i = 0; i < oldStr.length(); ++i)
            {
                newStr[i] = std::tolower(oldStr[i]);
            }
            return newStr;
        }
    };
};


