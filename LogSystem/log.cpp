#include "log.h"

Log* Log::instance = nullptr;


Log::Log()
{
}

Log::~Log()
{
	m_ofs.close();
}

void Log::init(const std::string& filename, LOG_LEVEL level, LOG_TARGET target, const std::string& str)
{
	m_ofs = std::ofstream(filename.c_str(), std::ios::out | std::ios::trunc);
	if (!m_ofs)
		throw("can't open output file " + filename);
	m_level = level;
	m_target = target;
	split(str, m_saveMember);
}


void Log::writeLog(const std::string& log, Log::LOG_LEVEL level, const std::string& source, const std::string& line)
{
	std::lock_guard<std::mutex> lockForWritelog(m_mutexForWriteLog);
	if (level < m_level)
	{
		//m_oss.str("");
		return;
	}
	m_data["datetime"] = currentDateTime();
	switch (level)
	{
	case LOG_LEVEL::DEBUG:
		m_data["level"] = "DEBUG";
		break;
	case LOG_LEVEL::INFO:
		m_data["level"] = "INFO";
		break;
	case LOG_LEVEL::ERROR:
		m_data["level"] = "ERROR";
		break;
	case LOG_LEVEL::FATAL:
		m_data["level"] = "FATAL";
		break;
	default:
		m_data["level"] = "DEBUG";
		break;
	}
	m_data["log"] = log;
	//m_oss.str("");
	m_data["source"] = source;
	m_data["line"] = line;
	if (m_target == LOG_TARGET::CONSOLE)
	{
		printToConsole();
	}
	else if (m_target == LOG_TARGET::FILE)
	{
		saveToFile();
	}
	else
	{
		printToConsole();
		saveToFile();
	}
}


void Log::printToConsole()
{
	for (auto i : m_saveMember)
	{
		std::cout << m_data[i] << " ";
	}
	std::cout << std::endl;
}

void Log::saveToFile()
{
	for (auto i : m_saveMember)
	{
		m_ofs << m_data[i] << " ";
	}
	m_ofs << std::endl;
}


const std::string currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	return buf;
}

void split(const std::string& str, std::vector<std::string>& tokens, char delimiters)
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (pos != std::string::npos || std::string::npos != lastPos)
	{
		tokens.emplace_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}