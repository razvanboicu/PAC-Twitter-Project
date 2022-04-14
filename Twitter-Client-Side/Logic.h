#pragma once
#include "Client.h"
#include <vector>
#include <string>

class Logic
{
public:
	Logic(int ClientHandle);

	std::vector<std::string> TokenizeString(const std::string& toTokenize);

protected:
	int m_clientHandle;
};

