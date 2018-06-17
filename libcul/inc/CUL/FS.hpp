#pragma once
#include <CUL/CUL.hpp>
#include "CUL/STD_string.hpp"
namespace CUL
{
    namespace FS
    {
        class CULLib_API FSApi
        {
        public:
            FSApi();
            virtual ~FSApi();
            static std::string getCurrentDir();
        };
    }
}