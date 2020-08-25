#ifndef VENO_LOGGER_H
#define VENO_LOGGER_H

#include <iostream>

namespace VeNo
{
    class Logger
    {
    public:
        static void debugMessage (const std::string& message);

        static void infoDebugMessage (const std::string& message);
    };
}
#endif //VENO_LOGGER_H
