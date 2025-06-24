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

        static void setLogLevel(LogLevel level_){
            level = level_;
        }


        template<typename ...Args>
        static void Debug(int line, char* filename, const char *msg, Args... args){
            log(line, filename, LogLevel::DEBUG, "DEBUG", msg, args...);
        }
        
        template<typename ...Args>
        static void Info(int line, char* filename, const char *msg, Args... args){
            log(line, filename, LogLevel::INFO, "INFO", msg, args...);
            
            
        }
        
        template<typename ...Args>
        static void Warn(int line, char* filename, const char *msg, Args... args){
            log(line, filename,LogLevel::WARN, "WARN", msg, args...);
            
        }

        template<typename ...Args>
        static void Error(int line, char* filename, const char *msg, Args... args){
            log(line, filename, LogLevel::ERROR, "ERROR", msg, args...);
            
        }

        template<typename ...Args>
        static void Fatal(int line, char* filename, const char *msg, Args... args){
            log(line, filename, LogLevel::FATAL, "FATAL", msg, args...);
        }


    private:
        static LogLevel level;
        inline static std::mutex log_mutex; // without inline it has some linker issues

        template<typename ...Args>
        static void log(int line, char* filename, const LogLevel msg_level, const char *level_string, const char *msg, Args... args) {
            std::lock_guard<std::mutex> lock(log_mutex);
            if(level <= msg_level)
            {       
                std::time_t current_time = std::time(0);
                std::tm* timestamp = std::localtime(&current_time);
                char buffer[80];
                strftime(buffer, 80, "%c", timestamp);
                printf("%s ", buffer);
                printf("%s:%d ", filename, line);
                printf("%s: ", level_string);
                printf(msg, args...);
                printf("\n");
            }
        }
        
};

LogLevel Logger::level = LogLevel::INFO;
#define LOG_INFO(msg, ...) (Logger::Info(__LINE__, __FILE__, msg, __VA_ARGS__))
#define LOG_DEBUG(msg, ...) (Logger::Debug(__LINE__, __FILE__, msg, __VA_ARGS__))
#define LOG_WARN(msg, ...) (Logger::Warn(__LINE__, __FILE__, msg, __VA_ARGS__))
#define LOG_ERROR(msg, ...) (Logger::Error(__LINE__, __FILE__, msg, __VA_ARGS__))
#define LOG_FATAL(msg, ...) (Logger::Fatal(__LINE__, __FILE__, msg, __VA_ARGS__))



#endif // LOGGER_H