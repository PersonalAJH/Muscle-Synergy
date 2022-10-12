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

#ifdef CALLTRACER_H
XSENS_COMPILER_WARNING("X0008", "calltracer.h should only be included ONCE and NEVER in a header file")
#else
#define CALLTRACER_H
#endif

//#define TRACECALLS	// define before including this header file to enable semi-automatic calltracing
#ifdef TRACECALLS
#if JLDEF_BUILD <= JLL_TRACE
#include <xstypes/xstime.h>
#include "journaller.h"

/*! \brief The CallTracer class is used to log function entry and exit.
	\details Usually the class is instantiated through one of the TRACETHIS, TRACEGLOBAL or
	TRACETHIS2 macros, but it can be created manually if desired. The class writes a log-line
	during creation and another one when it gets destroyed, if a minimum time has passed since
	construction.
*/
class CallTracer {
public:
	Journaller* m_journal;
	std::string m_msg;

	/*! \brief Constructor, writes an entry logline and starts timing the function
		\param functionName The name of the function that contains the CallTracer object (or some other identifying string)
		\param object A pointer to an object, usually the this pointer of the containing function. Used to separate nested and concurrent calls to the same function.
		\param minTime The minimum time in ms to pass for an exit logline to be created. Set to 0 to always write an exit line.
	*/
	CallTracer(Journaller* journal, const std::string& functionName, const void* object)
		: m_journal(journal)
		, m_msg(functionName)
	{
		if (object)
		{
			char ptr[32];
			sprintf(ptr, " [%p]", object);
			m_msg += ptr;
		}
		JLTRACE_NODEC(m_journal, m_msg << " entry");
	}

	/*! \brief Destructor, writes an exit logline if at least m_minimumTime has passed
	*/
	~CallTracer()
	{
		JLTRACE_NODEC(m_journal, m_msg << " exit");
	}
};
#define TRACEFUNC(journal) CallTracer trAceR(journal, std::string(__FILE__) + ":" + __FUNCTION__, NULL)
#define TRACETHIS(journal) CallTracer trAceR(journal, std::string(__FILE__) + ":" + __FUNCTION__, this)
#else
#define TRACEFUNC(j)	((void) 0)
#define TRACETHIS(j)	((void) 0)
#endif
#else
#define TRACEFUNC(j)	((void) 0)
#define TRACETHIS(j)	((void) 0)
#endif
