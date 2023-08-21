#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stdio.h>

enum LogPriority {
    TRACE, DEBUG, INFO, WARN, ERROR, CRITICAL
};

class Logger {
    public:
        static void setPriority(LogPriority new_priority) {
            priority = new_priority;
        }

        template<typename... Args>
        static void Trace(const char* message, Args... args) {
            if (priority <= TRACE) {
                printf("[TRACE]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        template<typename... Args>
        static void Debug(const char* message, Args... args) {
            if (priority <= DEBUG) {
                printf("[DEBUG]\t");
                printf(message, args...);
                printf("\n");
            }
        }
        
        template<typename... Args>
        static void Info(const char* message, Args... args) {
            if (priority <= INFO) {
                printf("[INFO]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        template<typename... Args>
        static void Warn(const char* message, Args... args) {
            if (priority <= WARN) {
                printf("[WARN]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        template<typename... Args>
        static void Error(const char* message, Args... args) {
            if (priority <= ERROR) {
                printf("[ERROR]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        template<typename... Args>
        static void Critical(const char* message, Args... args) {
            if (priority <= CRITICAL) {
                printf("[CRITICAL]\t");
                printf(message, args...);
                printf("\n");
            }
        }
    
    private:
        inline static LogPriority priority = DEBUG;
};

#endif