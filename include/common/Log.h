#pragma once
//
// logging system is based on the spdlog logging library (https://github.com/gabime/spdlog)
//
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <map>

namespace ChatApp {

	class Log
	{
	public:
		enum class Type : uint8_t
		{
			Common = 0, Client = 1
		};
		enum class Level : uint8_t
		{
			Trace = 0, Info, Warn, Error, Fatal
		};
		struct TagDetails
		{
			bool Enabled = true;
			Level LevelFilter = Level::Trace;
		};

	public:
		static void Init();
		static void Shutdown();

		inline static std::shared_ptr<spdlog::logger>& GetCommonLogger() { return s_CommonLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		static bool HasTag(const std::string& tag) { return s_EnabledTags.find(tag) != s_EnabledTags.end(); }
		static std::map<std::string, TagDetails>& EnabledTags() { return s_EnabledTags; }

		template<typename... Args>
		static void PrintMessage(Log::Type type, Log::Level level, std::string_view tag, Args&&... args);

		template<typename... Args>
		static void PrintAssertMessage(Log::Type type, std::string_view prefix, Args&&... args);

	public:
		// Enum utils
		static const char* LevelToString(Level level)
		{
			switch (level)
			{
				case Level::Trace: return "Trace";
				case Level::Info:  return "Info";
				case Level::Warn:  return "Warn";
				case Level::Error: return "Error";
				case Level::Fatal: return "Fatal";
			}
			return "";
		}
		static Level LevelFromString(std::string_view string)
		{
			if (string == "Trace") return Level::Trace;
			if (string == "Info")  return Level::Info;
			if (string == "Warn")  return Level::Warn;
			if (string == "Error") return Level::Error;
			if (string == "Fatal") return Level::Fatal;

			return Level::Trace;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CommonLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		inline static std::map<std::string, TagDetails> s_EnabledTags;
	};

	class ScopeForLog {
	public:
		ScopeForLog();
		~ScopeForLog();
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tagged logs (prefer these!)                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Common logging
#define CA_COMMON_TRACE_TAG(tag, ...) ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Trace, tag, __VA_ARGS__)
#define CA_COMMON_INFO_TAG(tag, ...)  ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Info, tag, __VA_ARGS__)
#define CA_COMMON_WARN_TAG(tag, ...)  ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Warn, tag, __VA_ARGS__)
#define CA_COMMON_ERROR_TAG(tag, ...) ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Error, tag, __VA_ARGS__)
#define CA_COMMON_FATAL_TAG(tag, ...) ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Fatal, tag, __VA_ARGS__)

// Client logging
#define CA_TRACE_TAG(tag, ...) ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Trace, tag, __VA_ARGS__)
#define CA_INFO_TAG(tag, ...)  ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Info, tag, __VA_ARGS__)
#define CA_WARN_TAG(tag, ...)  ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Warn, tag, __VA_ARGS__)
#define CA_ERROR_TAG(tag, ...) ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Error, tag, __VA_ARGS__)
#define CA_FATAL_TAG(tag, ...) ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Fatal, tag, __VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Common Logging
#define CA_COMMON_TRACE(...)  ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Trace, "", __VA_ARGS__)
#define CA_COMMON_INFO(...)   ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Info, "", __VA_ARGS__)
#define CA_COMMON_WARN(...)   ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Warn, "", __VA_ARGS__)
#define CA_COMMON_ERROR(...)  ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Error, "", __VA_ARGS__)
#define CA_COMMON_FATAL(...)  ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Common, ::ChatApp::Log::Level::Fatal, "", __VA_ARGS__)

// Client Logging
#define CA_TRACE(...)   ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Trace, "", __VA_ARGS__)
#define CA_INFO(...)    ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Info, "", __VA_ARGS__)
#define CA_WARN(...)    ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Warn, "", __VA_ARGS__)
#define CA_ERROR(...)   ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Error, "", __VA_ARGS__)
#define CA_FATAL(...)   ::ChatApp::Log::PrintMessage(::ChatApp::Log::Type::Client, ::ChatApp::Log::Level::Fatal, "", __VA_ARGS__)

namespace ChatApp {

	template<typename... Args>
	void Log::PrintMessage(Log::Type type, Log::Level level, std::string_view tag, Args&&... args)
	{
		auto detail = s_EnabledTags[std::string(tag)];
		if (detail.Enabled && detail.LevelFilter <= level)
		{
			auto logger = (type == Type::Common) ? GetCommonLogger() : GetClientLogger();
			std::string logString = tag.empty() ? "{0}{1}" : "[{0}] {1}";
			std::string formattedMessage = fmt::format(logString, tag, fmt::format(std::forward<Args>(args)...));
            switch (level)
            {
            case Level::Trace:
                logger->trace(formattedMessage);
                break;
            case Level::Info:
                logger->info(formattedMessage);
                break;
            case Level::Warn:
                logger->warn(formattedMessage);
                break;
            case Level::Error:
                logger->error(formattedMessage);
                break;
            case Level::Fatal:
                logger->critical(formattedMessage);
                break;
            }
		}
	}


	template<typename... Args>
	void Log::PrintAssertMessage(Log::Type type, std::string_view prefix, Args&&... args)
	{
		auto logger = (type == Type::Common) ? GetCommonLogger() : GetClientLogger();
		logger->error("{0}: {1}", prefix, fmt::vformat(fmt::make_format_args(args...)));
	}

	template<>
	inline void Log::PrintAssertMessage(Log::Type type, std::string_view prefix)
	{
		auto logger = (type == Type::Common) ? GetCommonLogger() : GetClientLogger();
		logger->error("{0}", prefix);
	}
}
