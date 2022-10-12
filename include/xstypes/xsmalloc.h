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

#ifndef XSMALLOC_H
#define XSMALLOC_H

#include "xstypesconfig.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

XSTYPES_DLL_API void* xsMalloc(size_t sz);
XSTYPES_DLL_API void* xsRealloc(void* ptr, size_t sz);
XSTYPES_DLL_API void  xsFree(void* ptr);

XSTYPES_DLL_API void* xsAlignedMalloc(size_t sz);
XSTYPES_DLL_API void* xsAlignedRealloc(void* ptr, size_t sz);
XSTYPES_DLL_API void  xsAlignedFree(void* ptr);

#ifndef xsMathMalloc
#define xsMathMalloc(n)		xsAlignedMalloc(n)
#endif

#ifndef xsMathRealloc
#define xsMathRealloc(p, n)	xsAlignedRealloc(p,n)
#endif

#ifndef xsMathFree
#define xsMathFree(p)		xsAlignedFree(p)
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif
