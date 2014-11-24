
//#ifndef _LOGGING_LOGFILE
//#define _LOGGING_LOGFILE

#include "logging.h"

#include <iostream>
#include <fstream>

/*
    This is intented to work as follows:

    file.cpp

    #include "~/core/inline/log_file.h"
    const std::string core::logging::log_file::file_name = ACTUAL_FILENAME_LOGFILE;
    #define LOG_CONNECTION core::logging::logger<core::logging::log_file>

*/

#define ACTUAL_FILENAME_LOGFILE std::string(__FILE__).substr(std::string(__FILE__).find_last_of("/\\")+1) + ".log";
#define LOG_FILE(LOG_FILE_ID) const std::string core::logging::log_file::file_name = ACTUAL_FILENAME_LOGFILE; typedef core::logging::logger<core::logging::log_file> LOG_FILE_ID

namespace core {
    namespace logging {

        class log_file {
            public:
                static void on_log(const e_severity &severity, const std::string &preamble, const std::string &log) {
                    //get_file().open(LOG_FILE, std::ofstream::app|std::ofstream::out);
                    get_file() << preamble.c_str() << ": " << log.c_str() << std::endl;
                    //get_file().close();
                    };

                static std::ofstream& get_file() { // workaround to solve static class member variable definition linking problem.
                    static std::ofstream file(file_name.c_str());
                    return file;
                    };
                static const std::string file_name;
            };

        }
    }

//#endif