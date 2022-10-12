/*	WARNING: COPYRIGHT (C) 2018 XSENS TECHNOLOGIES OR SUBSIDIARIES WORLDWIDE. ALL RIGHTS RESERVED.
	THIS FILE AND THE SOURCE CODE IT CONTAINS (AND/OR THE BINARY CODE FILES FOUND IN THE SAME
	FOLDER THAT CONTAINS THIS FILE) AND ALL RELATED SOFTWARE (COLLECTIVELY, "CODE") ARE SUBJECT
	TO A RESTRICTED LICENSE AGREEMENT ("AGREEMENT") BETWEEN XSENS AS LICENSOR AND THE AUTHORIZED
	LICENSEE UNDER THE AGREEMENT. THE CODE MUST BE USED SOLELY WITH XSENS PRODUCTS INCORPORATED
	INTO LICENSEE PRODUCTS IN ACCORDANCE WITH THE AGREEMENT. ANY USE, MODIFICATION, COPYING OR
	DISTRIBUTION OF THE CODE IS STRICTLY PROHIBITED UNLESS EXPRESSLY AUTHORIZED BY THE AGREEMENT.
	IF YOU ARE NOT AN AUTHORIZED USER OF THE CODE IN ACCORDANCE WITH THE AGREEMENT, YOU MUST STOP
	USING OR VIEWING THE CODE NOW, REMOVE ANY COPIES OF THE CODE FROM YOUR COMPUTER AND NOTIFY
	XSENS IMMEDIATELY BY EMAIL TO INFO@XSENS.COM. ANY COPIES OR DERIVATIVES OF THE CODE (IN WHOLE
	OR IN PART) IN SOURCE CODE FORM THAT ARE PERMITTED BY THE AGREEMENT MUST RETAIN THE ABOVE
	COPYRIGHT NOTICE AND THIS PARAGRAPH IN ITS ENTIRETY, AS REQUIRED BY THE AGREEMENT.
*/

#ifndef ABSTRACTADDITIONALLOGGER_H
#define ABSTRACTADDITIONALLOGGER_H

#include "journalloglevel.h"
#include <string>

/*! \class AbstractAdditionalLogger
	Interface for all additional loggers that can be attached to the Journaller
*/
class AbstractAdditionalLogger {
public:
	/*! \returns true if loglevel \a level should be logged, false otherwise
		\param[in] level The log level to check
	*/
	virtual bool logLevel(JournalLogLevel level) const = 0;

	/*! \returns the current log level
	*/
	virtual JournalLogLevel logLevel() const = 0;

	/*! \returns the current debug log level
	*/
	virtual JournalLogLevel debugLevel() const = 0;

	/*! \brief Set the current log level
		\param[in] level The new log level
	*/
	virtual void setLogLevel(JournalLogLevel level) = 0;

	/*! \brief Set the current debug log level
		\param[in] level The new debug log level
	*/
	virtual void setDebugLevel(JournalLogLevel level) = 0;

	/*! \brief Perform a logging
		\param[in] level The log level
		\param[in] file The name of the file from which the logging originates
		\param[in] line The line number from which the logging originates
		\param[in] function The name of the function from which the logging originates
		\param[in] msg The actual log message
	*/
	virtual void log(JournalLogLevel level, char const * file, int line, char const * function, std::string const & msg) = 0;

	/*! \brief Perform a logging without decoration
		\param[in] level The log level
		\param[in] file The name of the file from which the logging originates
		\param[in] line The line number from which the logging originates
		\param[in] function The name of the function from which the logging originates
		\param[in] msg The actual log message
	*/
	virtual void logNoDecoration(JournalLogLevel level, char const * file, int line, char const * function, std::string const & msg) = 0;
};

#endif