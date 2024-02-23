﻿#pragma once

#include "Core/CoreTypes.h"

#include <string>
#include <vector>

class CCommandLineArguments
{
public:
    CCommandLineArguments(char** Arguments, int32 ArgumentCount);
    CCommandLineArguments() = default;

    bool IsEmpty() const { return m_CommandLineArguments.empty(); }

    std::vector<std::string>::iterator begin() { return m_CommandLineArguments.begin(); }
    std::vector<std::string>::iterator end() { return m_CommandLineArguments.end(); }
    std::vector<std::string>::const_iterator begin() const { return m_CommandLineArguments.begin(); }
    std::vector<std::string>::const_iterator end() const { return m_CommandLineArguments.end(); }
private:
    std::vector<std::string> m_CommandLineArguments = {};
};