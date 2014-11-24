#ifndef _CORE_LOGGING
#define _CORE_LOGGING

#ifndef _NO_LOGGING

    #include <iostream>
    #include <sstream>

    #include <string>

    #ifndef LOGGER // check if defined so it can be overriden by the final user.
        #define LOGGER core::logging::logger<>
    #endif

	#ifdef _DEBUG
        #define LOG_DEBUG_(logger, std_string)  {std::stringstream ss; ss << std_string; logger::debug(ss.str(), __FILE__, __FUNCTION__, __LINE__);} void(0)
        #define LOG_WARN_(logger, std_string)   {std::stringstream ss; ss << std_string; logger::warn(ss.str(), __FILE__, __FUNCTION__, __LINE__);} void(0)

        #define LOG_DEBUG(std_string)	LOG_DEBUG_(LOGGER, std_string)
		#define LOG_WARN(std_string)	LOG_WARN_(LOGGER, std_string)


    #else
		#define LOG_DEBUG(std_string)	void(0)
		#define LOG_WARN(std_string)	void(0)

        #define LOG_DEBUG_(logger, std_string) void(0)
        #define LOG_WARN_(logger, std_string) void(0)
    #endif

    #define LOG_INFO_(logger, std_string)   {std::stringstream ss; ss << std_string; logger::info(ss.str(), __FILE__, __FUNCTION__, __LINE__);} void(0)
    #define LOG_ERROR_(logger, std_string)  {std::stringstream ss; ss << std_string; logger::error(ss.str(), __FILE__, __FUNCTION__, __LINE__);} void(0)

	#define LOG_INFO(std_string)	LOG_INFO_(LOGGER, std_string)
    #define LOG_ERROR(std_string)   LOG_ERROR_(LOGGER, std_string)
    #define LOG_PARAMS(params)	params


    namespace core {
        namespace logging {

            enum e_severity {LOG_SEVERITY_INFO, LOG_SEVERITY_DEBUG, LOG_SEVERITY_WARN, LOG_SEVERITY_ERROR };

            const std::string str_severity[] = {"INFO ", "DEBUG", "WARN ", "ERROR"};

            class log_console {
                public:
                    static void on_log(const e_severity &severity, const std::string &preamble, const std::string &log) {
                        if (severity == LOG_SEVERITY_ERROR) {
                            std::cerr << preamble << ": " << log << std::endl;
                            }
                        else {
                            std::cout << preamble << ": " << log << std::endl;
                            }
                        };
                };

            class default_format {
                public:

                    static const std::string preamble(const e_severity &severity, const std::string &file, const std::string &function, const unsigned int &line) {
                        std::stringstream ss; ss << str_severity[severity] << " " << str_place(file, function, line);
                        return ss.str();
                        };
                    static const std::string log(const e_severity &severity, const std::string &log_) {
                        return log_;
                        };
                protected:
                    static const std::string str_place(const std::string &file, const std::string &function, const unsigned int &line) {
                        size_t aux_ = file.find_last_of("/\\");
                        std::stringstream ss; ss << file.substr(aux_ + 1) << ":" << line;// << " ('" << function << "')";
                        return ss.str();
                        };
                };

            template <typename log_trait = log_console, typename format_trait = default_format>
            class logger {
                public:
					typedef log_trait log_trait_type;
                    typedef format_trait format_trait_type;

                public:
                    static void info(const std::string &log,  const std::string &file, const std::string &function, const unsigned int &line) {log_trait::on_log(LOG_SEVERITY_INFO,  format_trait::preamble(LOG_SEVERITY_INFO,  file, function, line), format_trait::log(LOG_SEVERITY_INFO,  log));};
                    static void debug(const std::string &log, const std::string &file, const std::string &function, const unsigned int &line) {log_trait::on_log(LOG_SEVERITY_DEBUG,  format_trait::preamble(LOG_SEVERITY_DEBUG, file, function, line), format_trait::log(LOG_SEVERITY_DEBUG,  log));};
                    static void warn(const std::string &log,  const std::string &file, const std::string &function, const unsigned int &line) {log_trait::on_log(LOG_SEVERITY_WARN,  format_trait::preamble(LOG_SEVERITY_WARN,  file, function, line), format_trait::log(LOG_SEVERITY_WARN,  log));};
                    static void error(const std::string &log, const std::string &file, const std::string &function, const unsigned int &line) {log_trait::on_log(LOG_SEVERITY_ERROR,  format_trait::preamble(LOG_SEVERITY_ERROR, file, function, line), format_trait::log(LOG_SEVERITY_ERROR,  log));};

                };


            }
        }

#else // if _NO_LOGGING defined...

	#define LOG_INFO(std_string)    void(0)
	#define LOG_DEBUG(std_string)	void(0)
	#define LOG_WARN(std_string)	void(0)
	#define LOG_ERROR(std_string)   void(0)

	#define LOG_INFO_(logger, std_string)    void(0)
	#define LOG_DEBUG_(logger, std_string)	void(0)
	#define LOG_WARN_(logger, std_string)	void(0)
	#define LOG_ERROR_(logger, std_string)   void(0)

    #define LOG_PARAMS(params)	    void(0)

#endif

#endif
