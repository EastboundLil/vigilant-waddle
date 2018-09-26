#pragma once

//write log to console, should become obsolete
#include <iostream>
#define LOG(msg) std::cout << __FILE__ << ": " << __FUNCTION__ << " (" << __LINE__ << "): " << msg << std::endl

#include <fstream>
#include <string>

#define LOG_FILE(msg) Logger::getInstance().log(msg)

class Logger
{
public:
	static Logger& getInstance()
	{
		static Logger instance;
		return instance;
	}

	void log(std::string msg)
	{
		file.open("worms.log");
		file << __FILE__ << ": " << __FUNCTION__ << " (" << __LINE__ << "): " << msg << std::endl;
		file.close();
	}

	~Logger()
	{

	}

private:
	Logger()
	{

	}

	std::fstream file;
};