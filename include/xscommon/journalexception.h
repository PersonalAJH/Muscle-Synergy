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

#ifndef JOURNALEXCEPTION_H
#define JOURNALEXCEPTION_H

#include <string>
#include <xstypes/xsexception.h>

#include "journaller.h"

#ifndef XSENS_WINDOWS
#include <signal.h>
#include <cstring>
#endif

class JournalException : public XsException {
public:
	JournalException(std::string message);
	~JournalException() throw() {}

	const char *msg() const;
	const std::string& stack() const;

protected:
	std::string m_stack; //!< A string that contains a stack dump
	friend class JournalExceptionStackWalker;
};

//! Use this macro to throw an exception that includes callstack information
#define JLTHROW(msg)	do { std::ostringstream os; os << msg; throw JournalException(os.str()); } while(0)

extern bool gOnExceptionGotoDebugger;

#ifdef XSENS_WINDOWS
	#include <windows.h>
	LONG journallerExceptionFilter(EXCEPTION_POINTERS* pExPtrs, Journaller*);
#endif

#if JLDEF_BUILD > JLL_FATAL
	#define JOURNALCRASHES_SIGNAL_FUNCTIONS
	#define JOURNALCRASHES_BEGIN(journal)
	#define JOURNALCRASHES_END(journal)
#else
	#ifdef XSENS_WINDOWS
		#define JOURNALCRASHES_SIGNAL_FUNCTIONS
		#define JOURNALCRASHES_BEGIN(journal) \
			__try {

		#define JOURNALCRASHES_END(journal) \
			} __except (journallerExceptionFilter(GetExceptionInformation(), journal)) {}

	#else
		#define JOURNALCRASHES_SIGNAL_FUNCTIONS \
			Journaller *gSCJ = 0;\
			extern "C" void signal_handler(int signal, siginfo_t *, void *)\
			{\
				if (gSCJ)\
				{\
					JLFATAL_NODEC(gSCJ, strsignal(signal));\
					gSCJ->writeCallstack(JLL_Fatal);\
				}\
				_exit(-1);\
			}

		#define JOURNALCRASHES_BEGIN(journal) \
			do { \
				gSCJ = journal;\
				struct sigaction act;\
				memset(&act, 0, sizeof(act));\
				act.sa_flags = SA_SIGINFO;\
				act.sa_sigaction = &signal_handler;\
				sigaction(SIGSEGV, &act, NULL);\
				sigaction(SIGILL, &act, NULL);\
				sigaction(SIGABRT, &act, NULL);\
				sigaction(SIGFPE, &act, NULL);\
			} while (0);
		#define JOURNALCRASHES_END(journal)
	#endif
#endif

#if JLDEF_BUILD > JLL_ERROR
	#define JOURNALEXCEPTIONS_BEGIN(journal)		try {
	#define JOURNALEXCEPTIONS_END_NOTHROW(journal)	} catch(...) { }
	#define JOURNALEXCEPTIONS_END_RETHROW(journal)	} catch(...) { throw; }
#else
	#define JOURNALEXCEPTIONS_BEGIN(journal) \
		try {

	#define JOURNALEXCEPTIONS_END_NOTHROW(journal) \
		} catch (JournalException& e) { JLERROR(journal, e.msg()); JLERROR_NODEC(journal, e.stack()); }\
		catch (XsException& e) { JLERROR(journal, e.what()); }\
		catch (std::exception& e) { JLERROR(journal, e.what()); }

	#define JOURNALEXCEPTIONS_END_RETHROW(journal) \
		} catch (JournalException& e) { JLERROR(journal, e.msg()); JLERROR_NODEC(journal, e.stack()); throw; }\
		catch (XsException& e) { JLERROR(journal, e.what()); throw; }\
		catch (std::exception& e) { JLERROR(journal, e.what()); throw; }
#endif

#endif
