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

#ifndef JOURNALLERBASE_H
#define JOURNALLERBASE_H

#include "journalloglevel.h"
#include "abstractadditionallogger.h"
#include <sstream>
#ifndef JL_NOTEMPLATE
#include <iomanip>
#endif
#include <xstypes/xsstring.h>

class JournalFile;

class Journaller
{
public:
	Journaller(const char* pathfile, bool purge = true, JournalLogLevel initialLogLevel = JLL_Alert);
	Journaller(const XsString& pathfile, bool purge = true, JournalLogLevel initialLogLevel = JLL_Alert);
	Journaller(Journaller const& attachTo);
	virtual ~Journaller();

	virtual void log(JournalLogLevel level, const std::string& msg);
	void writeCallstack(JournalLogLevel level);

	void setLogLevel(JournalLogLevel level, bool writeLogLine = true);

	//! \returns The log level for logging to file
	inline JournalLogLevel logLevel() const { return m_level; }

	/*! \brief Compares a log/debug level with a set one
		\param level The log level to compare with
		\returns True if a set log/debug level is equal or higher than the compared one
	*/
	inline bool logLevel(JournalLogLevel level) const { return level >= m_level || level >= m_debugLevel; }

	void setDebugLevel(JournalLogLevel level, bool writeLogLine = true);

	//! \returns The log level for logging to debug output
	inline JournalLogLevel debugLevel() const { return m_debugLevel; }

	void setFlushLevel(JournalLogLevel level, bool writeLogLine = true);

	//! \returns The flush level
	inline JournalLogLevel flushLevel() const { return m_flushLevel; }

	virtual void writeFileHeader(const std::string& appName);
	void setUseDateTime(bool yes);

	void writeTime();
	void writeThread();
	void writeTag();
	void writeLevel(JournalLogLevel level);
	void writeMessage(const std::string& msg);
	void flush();

	const XsString filename() const;

	void setTag(const std::string &tag);
	virtual std::string tag() const;

	static void setAdditionalLogger(AbstractAdditionalLogger* additionalLogger);

	//! \returns True if it has an additional logger
	inline static bool hasAdditionalLogger() { return m_additionalLogger != nullptr; }

	//! \returns The additional logger
	inline static AbstractAdditionalLogger* additionalLogger() { return m_additionalLogger; }

	static std::string tagFromFilename(const std::string &fn);
	void changeLogFile(const XsString& pathfile, bool purge);

private:
	void init(XsString pathfile, bool purge);
	void flushLine();
	static JournalFile* getOrCreateFile(const XsString& fn, bool purge);

	JournalFile* m_file;
	std::string m_tag;
	std::string m_appName;
	JournalLogLevel m_level;
	JournalLogLevel m_debugLevel;
	JournalLogLevel m_flushLevel;

	bool m_useDateTime;

	static AbstractAdditionalLogger* m_additionalLogger;

	// no copying allowed
	Journaller& operator = (Journaller const&);
};

#if 1 && (defined(MSC_VER) || 1)	// add exceptions to compilers here that do not (yet) support constexpr. These will fall back to the full path. If the first 1 is set to 0, no path stripping will be done in any case.
inline static constexpr char const* jlStrippedPath(char const* a, char const* b)
{
	return (a[0] ? (a[0] == '/' || a[0] == '\\' ? jlStrippedPath(a+1, a+1) : jlStrippedPath(a+1, b) ) : b);
}
inline static constexpr char const* jlStrippedPathFile(char const* a)
{
	return jlStrippedPath(a,a);
}
#define STRIPPEDFILE	jlStrippedPathFile(__FILE__)
#else
#define STRIPPEDFILE	__FILE__
#endif

#if !defined(JLNOLINEINFO)
#define JLGENERIC_LINEINFO	STRIPPEDFILE << "(" << __LINE__ << ") "
#else
#define JLGENERIC_LINEINFO	""
#endif

#define JLGENERIC(journal, level, msg)\
	do { /*lint --e{506}*/ \
		if (journal && journal->logLevel(level)) \
		{ \
			std::ostringstream os; \
			os << JLGENERIC_LINEINFO << __FUNCTION__ << " " << msg; \
			journal->log(level, os.str()); \
		} \
		if (Journaller::hasAdditionalLogger() && Journaller::additionalLogger()->logLevel(level)) \
		{ \
			std::ostringstream os; \
			os << msg; \
			Journaller::additionalLogger()->log(level, STRIPPEDFILE, __LINE__, __FUNCTION__, os.str()); \
		} \
	} while(0)

#define JLGENERIC_NODEC(journal, level, msg)\
	do { \
		if (journal && journal->logLevel(level)) \
		{ \
			std::ostringstream os; \
			os << msg; \
			journal->log(level, os.str()); \
		} \
		if (Journaller::hasAdditionalLogger() && Journaller::additionalLogger()->logLevel(level)) \
		{ \
			std::ostringstream os; \
			os << msg; \
			Journaller::additionalLogger()->logNoDecoration(level, STRIPPEDFILE, __LINE__, __FUNCTION__, os.str()); \
		} \
	} while(0)

#if !defined(JLDEBUG)

#if JLDEF_BUILD > JLL_TRACE
#define JLTRACE(...)	((void)0)
#define JLTRACE_NODEC(...)	((void)0)
#else
#define JLTRACE(journal, msg)	JLGENERIC(journal, JLL_Trace, msg)
#define JLTRACE_NODEC(journal, msg)	JLGENERIC_NODEC(journal, JLL_Trace, msg)
#endif

#if JLDEF_BUILD > JLL_DEBUG
#define JLDEBUG(...)	((void)0)
#define JLDEBUG_NODEC(...)	((void)0)
#else
#define JLDEBUG(journal, msg)	JLGENERIC(journal, JLL_Debug, msg)
#define JLDEBUG_NODEC(journal, msg)	JLGENERIC_NODEC(journal, JLL_Debug, msg)
#endif

#if JLDEF_BUILD > JLL_ALERT
#define JLALERT(...)	((void)0)
#define JLALERT_NODEC(...)	((void)0)
#else
#define JLALERT(journal, msg)	JLGENERIC(journal, JLL_Alert, msg)
#define JLALERT_NODEC(journal, msg)	JLGENERIC_NODEC(journal, JLL_Alert, msg)
#endif

#if JLDEF_BUILD > JLL_ERROR
#define JLERROR(...)	((void)0)
#define JLERROR_NODEC(...)	((void)0)
#else
#define JLERROR(journal, msg)	JLGENERIC(journal, JLL_Error, msg)
#define JLERROR_NODEC(journal, msg)	JLGENERIC_NODEC(journal, JLL_Error, msg)
#endif

#if JLDEF_BUILD > JLL_FATAL
#define JLFATAL(...)	((void)0)
#define JLFATAL_NODEC(...)	((void)0)
#else
#define JLFATAL(journal, msg)	JLGENERIC(journal, JLL_Fatal, msg)
#define JLFATAL_NODEC(journal, msg)	JLGENERIC_NODEC(journal, JLL_Fatal, msg)
#endif

#define JLWRITE(journal, msg)		JLGENERIC(journal, JLL_None, msg)
#define JLWRITE_NODEC(journal, msg)	JLGENERIC_NODEC(journal, JLL_None, msg)

// some convenience macros, since we almost always use a global gJournal Journaller
#define JLTRACEG(msg)	JLTRACE(gJournal, msg)
#define JLDEBUGG(msg)	JLDEBUG(gJournal, msg)
#define JLALERTG(msg)	JLALERT(gJournal, msg)
#define JLERRORG(msg)	JLERROR(gJournal, msg)
#define JLFATALG(msg)	JLFATAL(gJournal, msg)
#define JLWRITEG(msg)	JLWRITE(gJournal, msg)

#endif

#define JLIF(journal, level, todo)	do { if(journal && journal->logLevel(level)) { todo; } } while(0)

#ifndef JL_NOTEMPLATE

/*! \class JlHexLogger
	\brief A support class of journaller that is used for the logging of hex values
*/
template <typename T>
class JlHexLogger {
public:
	T m_value; //!< A hex value

	/*! \brief Constructor
	*/
	explicit JlHexLogger(T i)
		: m_value(i)
	{
	}
};

template <typename T>
std::ostream& operator << (std::ostream& os, JlHexLogger<T> const& hex)
{
	std::ios_base::fmtflags f = os.flags();
	os << std::hex << std::uppercase << hex.m_value << std::setiosflags(f);
	return os;
}
template <> std::ostream& operator << (std::ostream& os, JlHexLogger<char> const& hex);

#define JLHEXLOG_BARE(d)	JlHexLogger<decltype(d)>(d)	// C++0x11 only!
#else
#define JLHEXLOG_BARE(d)	std::hex << std::uppercase << (int) d << std::nouppercase << std::dec
#endif
#define JLHEXLOG(d)			"0x" << JLHEXLOG_BARE(d)
#define JLVARLOG(a)			#a ": " << a << " "

#define JLPRECISE2(msg, prec)\
	[&](){\
		std::ostringstream os; \
		os.precision(prec); \
		os << msg; \
		return os.str();\
	}()
#define JLPRECISE(msg)	JLPRECISE2(msg, 16)

#define JLCASE2(s, a, b)		case a: s << b << "(" << static_cast<int>(a) << ")"; break;
#define JLCASE(s, a)			case a: s << #a << "(" << static_cast<int>(a) << ")"; break;
#define JLDEFAULTCASE(s)		default: s << "Unknown case: " << static_cast<int>(e); break;
#define JLENUMEXPPROTO(E)		std::ostream& operator << (std::ostream& dbg, E const& e)
#define JLENUMEXPHDR(E, ...)			/*! \brief Translate \a e into a text representation */ JLENUMEXPPROTO(E) { __VA_ARGS__ switch(e) {
#define JLENUMCASE(a)			JLCASE(dbg, a)
#define JLENUMCASE2(a, b)		JLCASE2(dbg, a, b)
#define JLENUMEXPFTR()			JLDEFAULTCASE(dbg) } return dbg; }
/*! Use this macro to define enum expansion to a text stream. supply the type as parameter \a E and all
	enum values you want to expand as a sequence of JLENUMCASE(item) (no commas) */
#define JLENUMEXPANDER(E, items)	JLENUMEXPHDR(E) items JLENUMEXPFTR()

/*! Use this macro to define enum expansion to a text stream. supply the type as parameter \a E and all
	enum values you want to expand as a sequence of JLENUMCASE(item) (no commas) */
#define JLENUMEXPANDERHEX(E, items)	JLENUMEXPHDR(E, dbg.setf (std::ios_base::hex , std::ios_base::basefield); dbg.setf (std::ios_base::showbase | std::ios_base::uppercase);) items JLENUMEXPFTR()

#define JLQTDEBUGHANDLER	\
QtMessageHandler gOldQtMessageHandler = nullptr; \
Journaller* qtJournal = nullptr;	\
QtMessageHandler qtChecker = nullptr;	\
void jlQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {\
	if (qtChecker) qtChecker(type, context, msg); \
	if (!qtJournal)	return;\
	switch (type) {\
	case QtDebugMsg:\
		JLDEBUG_NODEC(qtJournal, (const char *)msg.toLatin1());\
		break;\
	case QtWarningMsg:\
		JLALERT_NODEC(qtJournal, (const char *)msg.toLatin1());\
		break;\
	case QtCriticalMsg:\
		JLERROR_NODEC(qtJournal, (const char *)msg.toLatin1());\
		break;\
	case QtFatalMsg:\
		JLFATAL_NODEC(qtJournal, (const char *)msg.toLatin1());\
		abort();\
	default:\
		break;\
	}\
	if (gOldQtMessageHandler)\
		gOldQtMessageHandler(type,context,msg);\
}

#define JLINSTALLQTDEBUGHANDLER(journal)	\
	qtJournal = journal;\
	if (journal) {\
		if (gOldQtMessageHandler == NULL) gOldQtMessageHandler = qInstallMessageHandler(jlQtMessageHandler);\
		else qInstallMessageHandler(jlQtMessageHandler);\
	} else if (gOldQtMessageHandler) {\
		qInstallMessageHandler(gOldQtMessageHandler);\
		gOldQtMessageHandler = NULL;\
	}

//////////////////////////////////////////////////////////////////////////////////////////
/*!	\class JournalValueJanitor
	\brief Class for journalling a referenced value when the janitor leaves scope
	\details The class stores a reference to the supplied object and uses streaming to output
	it to the journal. Like all journalling this means that for the supplied type T
	std::stringstream& std::stringstream::operator << (std::stringstream&, const T& value) must
	be defined.
*/
template <typename T = int>
class JournalValueJanitor {
private:
	const JournalValueJanitor& operator = (const JournalValueJanitor&);

	Journaller* m_journal;
	const T& m_value;
	std::string m_msg;
	JournalLogLevel m_level;
public:
	bool m_enabled; //!< Boolean value if set to true then the janitor is enabled
	
	/*! \brief Constructor
	*/
	JournalValueJanitor<T>(Journaller* journal, const T& value, const std::string& msg = std::string(), JournalLogLevel level = JLL_Debug, bool enabled = true)
		: m_journal(journal)
		, m_value(value)
		, m_msg(msg)
		, m_level(level)
		, m_enabled(enabled && journal)
	{}

	/*! \brief Destructor
	*/
	~JournalValueJanitor()
	{
		if (m_enabled)
		{
			std::stringstream os;
			os << m_msg << m_value;
			m_journal->log(m_level, os.str());
		}
	}
};

void jlTerminate(Journaller** gj);

#endif