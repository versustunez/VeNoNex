#include "StringUtils.h"

std::vector<std::string> VeNo::StringUtils::split (std::string input, std::string separator)
{
    std::vector<std::string> result;
    std::string_view::size_type position, start = 0;

    while (std::string_view::npos != (position = input.find (separator, start)))
    {
        result.push_back (input.substr (start, position - start));
        start = position + separator.size ();
    }

    result.push_back (input.substr (start));
    return result;
}
