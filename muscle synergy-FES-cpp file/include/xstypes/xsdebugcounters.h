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

#ifndef XSDEBUGCOUNTERS_H
#define XSDEBUGCOUNTERS_H

#include "xstypesconfig.h"

#ifdef XSENS_USE_DEBUG_COUNTERS
#ifdef __cplusplus
extern "C" {
#endif

extern XSTYPES_DLL_API int XsVector_resetDebugCounts();
extern XSTYPES_DLL_API int XsVector_allocCount();
extern XSTYPES_DLL_API int XsVector_freeCount();
extern int XsVector_incAllocCount();
extern int XsVector_incFreeCount();

extern XSTYPES_DLL_API int XsMatrix_resetDebugCounts();
extern XSTYPES_DLL_API int XsMatrix_allocCount();
extern XSTYPES_DLL_API int XsMatrix_freeCount();
extern int XsMatrix_incAllocCount();
extern int XsMatrix_incFreeCount();

extern XSTYPES_DLL_API int XsArray_resetDebugCounts();
extern XSTYPES_DLL_API int XsArray_allocCount();
extern XSTYPES_DLL_API int XsArray_freeCount();
extern int XsArray_incAllocCount();
extern int XsArray_incFreeCount();

#ifdef __cplusplus
} // extern "C"
#endif

#else

inline static int XsVector_resetDebugCounts()	{ return 0; }
inline static int XsVector_allocCount()			{ return 0; }
inline static int XsVector_freeCount()			{ return 0; }
inline static int XsVector_incAllocCount()		{ return 0; }
inline static int XsVector_incFreeCount()		{ return 0; }

inline static int XsMatrix_resetDebugCounts()	{ return 0; }
inline static int XsMatrix_allocCount()			{ return 0; }
inline static int XsMatrix_freeCount()			{ return 0; }
inline static int XsMatrix_incAllocCount()		{ return 0; }
inline static int XsMatrix_incFreeCount()		{ return 0; }

inline static int XsArray_resetDebugCounts()	{ return 0; }
inline static int XsArray_allocCount()			{ return 0; }
inline static int XsArray_freeCount()			{ return 0; }
inline static int XsArray_incAllocCount()		{ return 0; }
inline static int XsArray_incFreeCount()		{ return 0; }

#endif


#endif
