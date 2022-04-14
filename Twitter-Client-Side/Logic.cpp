#include "Logic.h"
#include <sstream>

Logic::Logic(int ClientHandle):
	m_clientHandle(ClientHandle)
{
}

std::vector<std::string> Logic::TokenizeString(const std::string& toTokenize)
{
	std::vector<std::string> tokens;
	std::stringstream stream(toTokenize);
	std::string temp;
	while (std::getline(stream, temp, ';'))
	{
		tokens.push_back(temp);
	}
	return tokens;
}
