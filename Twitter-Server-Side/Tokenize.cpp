#include "Tokenize.h"
#include <vector>
#include <string>
#include <sstream>


std::vector<std::string> Tokenize::TokenizeString(const std::string& stringToTokenize)
{
	std::vector<std::string> tokens;
	std::stringstream stream(stringToTokenize);
	std::string temp;
	while (std::getline(stream, temp, ';'))
	{
		tokens.push_back(temp);
	}
	return tokens;
}
