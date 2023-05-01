#include "Profile.h"
#include <stdexcept>

#ifndef LOGGER_EXIT

#define LOGGER_EXIT(x) throw std::runtime_error(x)

#endif

#ifndef LOG_COLOR
#define LOG_COLOR Logger::Color::Green
#endif

#ifndef WARN_COLOR
#define WARN_COLOR Logger::Color::Yellow
#endif

#ifndef ERROR_COLOR
#define ERROR_COLOR Logger::Color::Red
#endif

namespace Logger {
	template<typename... Args>
	inline void Profile::Log(std::string format, Args... args) {
		InternalPrint("Log", LOG_COLOR, format, args...);
	}

	template<typename... Args>
	inline void Profile::Warn(std::string format, Args... args) {
		InternalPrint("Warn", WARN_COLOR, format, args...);
	}

	template<typename... Args>
	inline void Profile::Error(std::string format, Args... args) {
		InternalPrint("Error", ERROR_COLOR, format, args...);

		LOGGER_EXIT("");
	}

	template<typename... Args>
	inline void Profile::Assert(bool condition, std::string format, Args... args) {
		if (!condition) {
			Error(format, args...);
		}
	}

	template<typename... Args>
	inline void Profile::WarnAssert(bool condition, std::string format, Args... args) {
		if (!condition) {
			Warn(format, args...);
		}
	}

	// No Args

	template<typename... Args>
	inline void Profile::Log(std::string format) {
		InternalPrint("Log", LOG_COLOR, format);
	}

	template<typename... Args>
	inline void Profile::Warn(std::string format) {
		InternalPrint("Warn", WARN_COLOR, format);
	}

	template<typename... Args>
	inline void Profile::Error(std::string format) {
		InternalPrint("Error", ERROR_COLOR, format);

		LOGGER_EXIT("");
	}

	template<typename... Args>
	inline void Profile::Assert(bool condition, std::string format) {
		if (!condition) {
			Error(format);
		}
	}

	template<typename... Args>
	inline void Profile::WarnAssert(bool condition, std::string format) {
		if (!condition) {
			Warn(format);
		}
	}

	template<typename... Args>
	inline void Profile::InternalPrint(std::string type, uint8 foreground, std::string format, Args... args) {
		InternalPrint(type, foreground, Format(format, args...));
	}

	template<typename... Args>
	inline void Profile::InternalPrint(std::string type, uint8 foreground, std::string format) {
		std::stringstream message;

		if (name.size() != 0) {
			message << "[" << name << "]";
		}

		message << "[" << type << "]: ";
		uint8 spaceCount = message.str().size();

		for (uint32 i = 0; i < format.size(); i++) {
			if (format[i] == '\n') {
				message << '\n';

				for (uint8 u = 0; u < spaceCount; u++) {
					message << ' ';
				}
			} else {
				message << format[i];
			}
		}

		Print(message.str(), foreground);
	}
}