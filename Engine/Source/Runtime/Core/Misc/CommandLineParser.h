﻿#pragma once

#include "CommandLineArguments.h"
#include "Core/CoreTypes.h"

class CCommandLineParser
{
public:
    static bool Param(const CCommandLineArguments& CommandLineArguments, const std::string& Argument);
    
    static bool Value(const CCommandLineArguments& CommandLineArguments, const std::string& Argument, int32* Value);
    static bool Value(const CCommandLineArguments& CommandLineArguments, const std::string& Argument, float* Value);
    static bool Value(const CCommandLineArguments& CommandLineArguments, const std::string& Argument, double* Value);
    static bool Value(const CCommandLineArguments& CommandLineArguments, const std::string& Argument, std::string* Value);
};
