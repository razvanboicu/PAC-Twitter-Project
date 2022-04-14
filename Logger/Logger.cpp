#include "Logger.h"

Logger::Logger(std::ostream& out, Level levelValue) :
	m_out(out),
	m_minimLevel(levelValue)
{}
