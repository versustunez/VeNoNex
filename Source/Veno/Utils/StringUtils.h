#ifndef VENO_STRINGUTILS_H
#define VENO_STRINGUTILS_H


#include <string>
#include <vector>

namespace VeNo
{
    class StringUtils
    {
    public:
        static std::vector<std::string> split (const std::string& input, const std::string& separator = " ");
    };

}

#endif //VENO_STRINGUTILS_H
