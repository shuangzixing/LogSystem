#pragma once
#include<string>
#include<fstream>
#include<unordered_map>
#include<time.h>
#include<vector>
#include<iostream>
#include<sstream>
#include<mutex>


#define LOG_INIT(str1, str2, str3, str4) Log::getInstance(str1, str2, str3, str4)
#define LOG_DEBUG(str1) Log::getInstance()->writeLog((std::ostringstream()<<str1).str(), Log::LOG_LEVEL::DEBUG, __FILE__, std::to_string(__LINE__))
#define LOG_INFO(str1) Log::getInstance()->writeLog((std::ostringstream()<<str1).str(), Log::LOG_LEVEL::INFO, __FILE__, std::to_string(__LINE__))
#define LOG_ERROR(str1) Log::getInstance()->writeLog((std::ostringstream()<<str1).str(), Log::LOG_LEVEL::ERROR, __FILE__, std::to_string(__LINE__))
#define LOG_FATAL(str1) Log::getInstance()->writeLog((std::ostringstream()<<str1).str(), Log::LOG_LEVEL::FATAL, __FILE__, std::to_string(__LINE__))

class Log
{
public:
	// log level
	enum class LOG_LEVEL
	{
		DEBUG,
		INFO,
		ERROR,
		FATAL
	};
	// log target
	enum class LOG_TARGET
	{
		CONSOLE,
		FILE,
		ALL
	};
public:
	Log();
	~Log();
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;
public:
	// init class member
	void init(const std::string& filename, LOG_LEVEL level, LOG_TARGET target, const std::string& str);


	void writeLog(const std::string& log, LOG_LEVEL level, const std::string& file, const std::string& line);
	static Log* getInstance(const std::string& filename, LOG_LEVEL level, LOG_TARGET target, const std::string& str)
	{
		if (instance == nullptr)
		{
			instance = new Log;
			instance->init(filename, level, target, str);
		}
		return instance;
	}
	static Log* getInstance()
	{
		return instance;
	}
private:
	// print to console
	void printToConsole();
	// save to file
	void saveToFile();
private:
	LOG_LEVEL m_level;
	LOG_TARGET m_target;
	// output file stream
	std::ofstream m_ofs;
	// the priproty of each part of the log and wheather to store
	// for example: "level, datetime, log, source, line" represent first process log level, 
	// last process log line and save five parts.
	std::vector<std::string> m_saveMember;
	// use hashmap store data to process temporarily
	std::unordered_map<std::string, std::string> m_data;
	// buffer string stream, to support stream operation
	static Log* instance;
	std::mutex m_mutexForWriteLog;
};

const std::string currentDateTime();
// parse instruction
void split(const std::string& str, std::vector<std::string>& tokens, char ch = '_');