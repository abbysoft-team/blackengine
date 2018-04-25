//
// Created by popof on 24.04.2018.
//

#ifndef BLACKENGINE_LOGGER_H
#define BLACKENGINE_LOGGER_H

#include <logging/easylogging++.h>

namespace black {
    class Logger {
    public:
        static void initialize() {
            Logger::info("Initialize logger\n");
            el::Configurations defaultConf;
            defaultConf.setToDefault();
            defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "%datetime %logger: %level %msg");
            el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
            el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
            el::Loggers::reconfigureAllLoggers(defaultConf);
            el::Loggers::setLoggingLevel(el::Level::Info);
        }

        template<typename T, typename ...Args>
        static el::base::Writer &info(const char *message, const T& type, const Args&... args) {
            el::Loggers::getLogger("default")->info(message, type, args...);
        }

        static el::base::Writer &info(const char *message) {
            el::Loggers::getLogger("default")->info("%v", message);
        }

        template<typename T, typename ...Args>
        static el::base::Writer &error(const char *message, const T& type, const Args&... args) {
            el::Loggers::getLogger("default")->error(message, type, args...);
        }

        template<typename T, typename ...Args>
        static el::base::Writer &error(const char *message) {
            el::Loggers::getLogger("default")->error("%v", message);
        }

        template<typename T, typename ...Args>
        static el::base::Writer &debug(const char *message, const T& type, const Args&... args) {
            el::Loggers::getLogger("default")->debug(message, type, args...);
        }

        template<typename T, typename ...Args>
        static el::base::Writer &debug(const char *message) {
            el::Loggers::getLogger("default")->debug("%v", message);
        }

        /**
         * Returns a logger for channel 'channel'
         *
         * @param channel Channel name
         * @return Logger of that channel
         */
        static el::Logger *getChannelLogger(const std::string &channel) {
            return el::Loggers::getLogger(channel);
        }
    };
}


#endif //BLACKENGINE_LOGGER_H
