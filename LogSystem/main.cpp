#include<stdio.h>
#include<iostream>
#include<thread>
#include "log.h"

void funLog(void)
{
	LOG_DEBUG("Hello main Debug " << 2 << " from int");
	LOG_INFO("Hello main infor " << 2 << " from int");
	LOG_ERROR("Hello main error " << 2 << " from int");
	LOG_DEBUG("Hello main Debug " << 2 << " from int");
	LOG_FATAL("Hello main Fatal " << 2 << " from int");
}

void funLogEven()
{
	for (size_t i = 0; i < 10; i+=2)
	{
		LOG_DEBUG("Hello funLog Debug! even in 10: " << i);
	}
}

void funLogOdd()
{
	for (size_t i = 1; i < 10; i += 2)
	{
		LOG_DEBUG("Hello funLog Debug! even in 10: " << i);
	}
}

int main()
{
	try
	{
		LOG_INIT("log.txt", Log::LOG_LEVEL::DEBUG, Log::LOG_TARGET::ALL, "level_datetime_log_source_line");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	std::thread t1(funLogEven);
	std::thread t2(funLogOdd);
	t1.join();
	t2.join();

	LOG_DEBUG("Hello main Debug " << 3 << " from int");
	LOG_DEBUG("Hello main Debug " << 1 << " from int");
	LOG_INFO("Hello main infor " << 1 << " from int");
	LOG_ERROR("Hello main error " << 1 << " from int");
	LOG_DEBUG("Hello main Debug " << 1 << " from int");
	LOG_FATAL("Hello main Fatal " << 1 << " from int");
	funLog();
	delete Log::getInstance();
}
