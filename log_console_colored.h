
#ifndef _LOGGING_LOGCONSOLE_COLORED
#define _LOGGING_LOGCONSOLE_COLORED

#ifdef _WIN32

    #include <windows.h>
    #include "logging.h"

    namespace core {
        namespace logging {

                class log_console_colored : public log_console {
                    public:
                        static void on_log(const e_severity &severity, const std::string &preamble, const std::string &log) {
                            switch(severity) {
                                case LOG_SEVERITY_ERROR:
                                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_RED );
                                    break;
                                case LOG_SEVERITY_WARN:
                                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 6 );
                                    break;
                                case LOG_SEVERITY_INFO:
                                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 3 );
                                    break;
                                case LOG_SEVERITY_DEBUG:
                                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 5 );
                                    break;
                                default:
                                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
                                    break;
                                }
                            log_console::on_log(severity, preamble, log);
                            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 ); //<--Turn the output to white again
                            };
                    };

            }
        }
#else

    #pragma message("'core::logging::log_console_colored' not implemented for non _WIN32; defaults to 'core::logging::log_console'")

    #include "logging.h"

    namespace core {
        namespace logging {
            typedef log_console log_console_colored;
            }
        }

#endif

#endif
