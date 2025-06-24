#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <thread>
#include <mutex>

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
            if(level <= LogLevel::DEBUG){
                std::unique_lock<std::mutex> lock(log_mutex);
                printf("Debug:\t");
                printf(msg, args...);
                printf("\n");
            }
        }
        
        template<typename ...Args>
        static void Info(const char *msg, Args... args){
            std::unique_lock<std::mutex> lock(log_mutex);
            if(level <= LogLevel::INFO){
                printf("INFO:\t");
                printf(msg, args...);
                printf("\n");
            }
            
        }
        
        template<typename ...Args>
        static void Warn(const char *msg, Args... args){
            std::unique_lock<std::mutex> lock(log_mutex);
            if(level <= LogLevel::WARN) {
                printf("WARN:\t");
                printf(msg, args...);
                printf("\n");
            }
        }

        template<typename ...Args>
        static void Error(const char *msg, Args... args){
            std::unique_lock<std::mutex> lock(log_mutex);
            if(level <= LogLevel::ERROR)
            {
                printf("ERROR:\t");
                printf(msg, args...);
                printf("\n");
            }
        }

        template<typename ...Args>
        static void Fatal(const char *msg, Args... args){
            std::unique_lock<std::mutex> lock(log_mutex);
            if(level <= LogLevel::FATAL)
            {
                printf("FATAL:\t");
                printf(msg, args...);
                printf("\n");
            }
        }

        static void setLogLevel(LogLevel level_){
            level = level_;
        }


    private:
        static LogLevel level;
        inline static std::mutex log_mutex; // without inline it has some linker issues
        
};

LogLevel Logger::level = LogLevel::INFO;
#endif // LOGGER_H