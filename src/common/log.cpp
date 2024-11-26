#include "common/log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <filesystem>
#define WL_HAS_CONSOLE 1

namespace ChatApp {

	std::shared_ptr<spdlog::logger> Log::s_CommonLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
#if LOG_WITH_FILE
		// Create "logs" directory if doesn't exist
		std::string logsDirectory = "logs";
		if (!std::filesystem::exists(logsDirectory))
			std::filesystem::create_directories(logsDirectory);
#endif
		std::vector<spdlog::sink_ptr> commonSinks =
		{
#if LOG_WITH_FILE	
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/COMMON.log", true),
#elif WL_HAS_CONSOLE
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
#endif
		};

		std::vector<spdlog::sink_ptr> appSinks =
		{
#if LOG_WITH_FILE
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/APP.log", true),
#elif WL_HAS_CONSOLE
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>()
#endif
		};
#if LOG_WITH_FILE
		hazelSinks[0]->set_pattern("[%T] [%l] %n: %v");
		appSinks[0]->set_pattern("[%T] [%l] %n: %v");
		hazelSinks[1]->set_pattern("%^[%T] %n: %v%$");
		appSinks[1]->set_pattern("%^[%T] %n: %v%$");

#elif WL_HAS_CONSOLE
		commonSinks[0]->set_pattern("%^[%T] %n: %v%$");
		appSinks[0]->set_pattern("%^[%T] %n: %v%$");
#endif

		s_CommonLogger = std::make_shared<spdlog::logger>("Common", commonSinks.begin(), commonSinks.end());
		s_CommonLogger->set_level(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", appSinks.begin(), appSinks.end());
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::Shutdown()
	{
		s_ClientLogger.reset();
		s_CommonLogger.reset();
		spdlog::drop_all();
	}

}
