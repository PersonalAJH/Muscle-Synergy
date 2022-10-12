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

#ifndef XSENS_MATH_THROW_H
#define XSENS_MATH_THROW_H

#include "xstypesconfig.h"

#ifndef XSENS_NO_EXCEPTIONS
	#include "xsexception.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef XSENS_NO_EXCEPTIONS
	// support for exceptions is disabled, just do whatever assert(0) does
	#ifdef XSENS_DEBUG
		#include <assert.h>
		#define XM_THROW(a)			XSENS_FW_ASSERT_FUNC(a, __FILE__, (unsigned) __LINE__)
		#define XM_THROW_DEFINED	1
	#else
		#define XM_THROW(a)			((void) 0)
		#define XM_THROW_DEFINED	0
	#endif
#else
	#define XM_THROW_DEFINED	1
	#ifdef XSEXCEPTION_H
		#ifdef _MSC_VER
			#define XETHROW(a)	throw XsException(XRV_ERROR, XsString(__FUNCTION__ " ") << XsString(a))
		#elif defined __GNUC__
			#define XETHROW(a)	throw XsException(XRV_ERROR, XsString(__PRETTY_FUNCTION__) << " " << XsString(a))
		#else
			#define XETHROW(a)	throw XsException(XRV_ERROR, XsString(__func__) << " " << XsString(a))
		#endif
	#else
		#define XETHROW(a)	throw (a)
	#endif

	#if defined(XSENS_DEBUG) && defined(_WIN32) // && !defined(_WIN64) unclear why this clause was added in xsens_math.h rev 871 by RZA
		XSTYPES_DLL_API void xsensMathThrowBreakFunc();
		#define XM_THROW(a) do { xsensMathThrowBreakFunc(); XETHROW(a); } while(0)
	#else
		#define XM_THROW(a) do { XETHROW(a); } while(0)
	#endif
#endif

	XSTYPES_DLL_API void XsDebugTools_enableFloatingPointExceptions();
	XSTYPES_DLL_API void XsDebugTools_disableFloatingPointExceptions();

#ifdef __cplusplus
} // extern "C"

namespace xsens {
	namespace DebugTools {
		static inline void enableFloatingPointExceptions() { XsDebugTools_enableFloatingPointExceptions(); }	//!< \copydoc XsDebugTools_enableFloatingPointExceptions
		static inline void disableFloatingPointExceptions() { XsDebugTools_disableFloatingPointExceptions(); }	//!< \copydoc XsDebugTools_disableFloatingPointExceptions
	} // namespace DebugTools
} // namespace xsens

#endif

#endif
