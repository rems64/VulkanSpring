#include <SpringEngine/Misc/Logger.hpp>


SE_API std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> SE::Log::m_fileCoreLogger;
SE_API std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> SE::Log::m_stdCoreLogger;
SE_API std::shared_ptr<spdlog::logger> SE::Log::m_coreLogger;
SE_API std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> SE::Log::m_fileAppLogger;
SE_API std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> SE::Log::m_stdAppLogger;
SE_API std::shared_ptr<spdlog::logger> SE::Log::m_appLogger;

void SE::Log::init()
{
	//spdlog::set_pattern("%^[%T] [%=n] %v%$");
	//spdlog::set_pattern("[%=n] %v%$"); // Right
	spdlog::init_thread_pool(8192, 2);
	
	m_stdCoreLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	m_stdCoreLogger->set_pattern("[%=n] %v%$");
	m_fileCoreLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("log/core_log.log", 1024*10, 3);
	m_fileCoreLogger->set_pattern("[%=n] %v%$");
	
	std::vector<spdlog::sink_ptr> coreSinks{ m_fileCoreLogger, m_stdCoreLogger };
	m_coreLogger = std::make_shared<spdlog::async_logger>("ENGINE", coreSinks.begin(), coreSinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	spdlog::register_logger(m_coreLogger);

	m_coreLogger->set_level(spdlog::level::trace);
	m_stdCoreLogger->set_level(spdlog::level::trace);
	m_fileCoreLogger->set_level(spdlog::level::trace);


	m_stdAppLogger = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	m_stdAppLogger->set_pattern("[%=n] %v%$");
	m_fileAppLogger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("log/app_log.log", 1024 * 10, 3);
	m_fileAppLogger->set_pattern("[%=n] %v%$");

	std::vector<spdlog::sink_ptr> appSinks{ m_fileAppLogger, m_stdAppLogger };
	m_appLogger = std::make_shared<spdlog::async_logger>("APP", appSinks.begin(), appSinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	spdlog::register_logger(m_appLogger);

	m_appLogger->set_level(spdlog::level::trace);
	m_stdAppLogger->set_level(spdlog::level::trace);
	m_fileAppLogger->set_level(spdlog::level::trace);
}

void SE::Log::setCoreLogLevel(SE::LOG_LVL logLevel)
{
	m_coreLogger->set_level((spdlog::level::level_enum)logLevel);
	m_stdCoreLogger->set_level((spdlog::level::level_enum)logLevel);
	m_fileCoreLogger->set_level((spdlog::level::level_enum)logLevel);
}

void SE::Log::setAppLogLevel(SE::LOG_LVL logLevel)
{
	m_appLogger->set_level((spdlog::level::level_enum)logLevel);
	m_stdAppLogger->set_level((spdlog::level::level_enum)logLevel);
	m_fileAppLogger->set_level((spdlog::level::level_enum)logLevel);
}
