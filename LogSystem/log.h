#pragma once
#include<string>
#include<fstream>
#include<unordered_map>
#include<time.h>
#include<vector>
#include<iostream>

class Log
{
public:
	enum LOG_LEVEL
	{
		DEBUG,
		INFO,
		ERROR,
		FATAL
	};
	enum LOG_TARGET
	{
		CONSOLE,
		LOGFILE,
		ALL
	};
public:
	Log();
	//Log(const std::string& filename, LOG_LEVEL, LOG_TARGET);
	~Log();
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;
public:
	void set(const std::string& filename, LOG_LEVEL level, LOG_TARGET target, const std::string& str);

	void debug(const std::string& str, const std::string& file, const std::string& line);
	void info(const std::string& str, const std::string& file, const std::string& line);
	void error(const std::string& str, const std::string& file, const std::string& line);
	void fatal(const std::string& str, const std::string& file, const std::string& line);
	static Log* getInstance(const std::string& filename, LOG_LEVEL level, LOG_TARGET target, const std::string& str)
	{
		if (instance == nullptr)
		{
			instance = new Log;
			instance->set(filename, level, target, str);
		}
		return instance;
	}
private:
	void update(LOG_LEVEL, const std::string& str, const std::string& file, const std::string& line);
	void printToConsole();
	void saveToFile();
private:
	LOG_LEVEL m_level;
	LOG_TARGET m_target;
	std::ofstream m_ofs;
	std::vector<std::string> m_saveFlag;
	std::unordered_map<std::string, std::string> m_data;
	static Log* instance;
};

const std::string currentDateTime();
void split(const std::string& str, std::vector<std::string>& tokens, char ch = '_');