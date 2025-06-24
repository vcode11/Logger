#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <thread>
#include <mutex>
#include <ctime>

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger {
    public:
        Logger() = delete;

         template<typename ...Args>
        static void Debug(const char *msg, Args... args){
            log(LogLevel::DEBUG, "DEBUG", msg, args...);
        }
        
        template<typename ...Args>
        static void Info(const char *msg, Args... args){
            log(LogLevel::INFO, "INFO", msg, args...);
            
            
        }
        
        template<typename ...Args>
        static void Warn(const char *msg, Args... args){
            log(LogLevel::WARN, "WARN", msg, args...);
            
        }

        template<typename ...Args>
        static void Error(const char *msg, Args... args){
            log(LogLevel::ERROR, "ERROR", msg, args...);
            
        }

        template<typename ...Args>
        static void Fatal(const char *msg, Args... args){
            log(LogLevel::FATAL, "FATAL", msg, args...);
        }

        static void setLogLevel(LogLevel level_){
            level = level_;
        }


    private:
        static LogLevel level;
        inline static std::mutex log_mutex; // without inline it has some linker issues

        template<typename ...Args>
        static void log(const LogLevel msg_level, const char *level_string, const char *msg, Args... args) {
            std::lock_guard<std::mutex> lock(log_mutex);
            if(level <= msg_level)
            {       
                std::time_t current_time = std::time(0);
                std::tm* timestamp = std::localtime(&current_time);
                char buffer[80];
                strftime(buffer, 80, "%c", timestamp);
                printf("%s\t", buffer);
                printf("%s:\t", level_string);
                printf(msg, args...);
                printf("\n");
            }
        }
        
};

LogLevel Logger::level = LogLevel::INFO;
#endif // LOGGER_H