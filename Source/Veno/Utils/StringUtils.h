//
// Created by Maurice on 08.07.2020.
//

#ifndef VENO_STRINGUTILS_H
#define VENO_STRINGUTILS_H


#include <string>
#include <vector>

namespace VeNo
{
    class StringUtils
    {
    public:
        static std::vector<std::string> split (std::string input, std::string separator = " ");
    };

}

#endif //VENO_STRINGUTILS_H
