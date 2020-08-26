#include<stdio.h>
#include<iostream>
#include "log.h"



void funlog(void)
{

}

int main()
{
	Log* logger = Log::getInstance("log.txt", Log::LOG_LEVEL::INFO, Log::LOG_TARGET::ALL, "level_datetime_log_source_line");
	try
	{
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	funlog();
	logger->debug("Hello main Debug", __FILE__, std::to_string(__LINE__));
	logger->info("Hello main infor", __FILE__, std::to_string(__LINE__));
	logger->error("Hello main error", __FILE__, std::to_string(__LINE__));
	logger->debug("Hello main Debug", __FILE__, std::to_string(__LINE__));
	logger->fatal("Hello main fatal", __FILE__, std::to_string(__LINE__));

	Log* loggger2 = Log::getInstance("log.txt", Log::LOG_LEVEL::INFO, Log::LOG_TARGET::CONSOLE, "level_datetime_log_source_line");
	//std::cout << "logger: " << logger << std::endl;
	//std::cout << "logger2: " << loggger2 << std::endl;
}
