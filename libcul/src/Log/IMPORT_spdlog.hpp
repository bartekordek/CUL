#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/sinks/wincolor_sink.h"
#include "spdlog/sinks/ansicolor_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

#ifdef _MSC_VER
#pragma warning( pop )
#endif