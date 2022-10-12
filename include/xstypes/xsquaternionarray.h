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

#ifndef XSQUATERNIONARRAY_H
#define XSQUATERNIONARRAY_H

#include "xsarray.h"

#ifdef __cplusplus
#include "xsquaternion.h"
extern "C" {
#endif

extern XsArrayDescriptor const XSTYPES_DLL_API g_xsQuaternionArrayDescriptor;

#ifndef __cplusplus
#define XSQUATERNIONARRAY_INITIALIZER	XSARRAY_INITIALIZER(&g_xsQuaternionArrayDescriptor)
struct XsQuaternion;

XSARRAY_STRUCT(XsQuaternionArray, struct XsQuaternion);
typedef struct XsQuaternionArray XsQuaternionArray;

XSTYPES_DLL_API void XsQuaternionArray_construct(XsQuaternionArray* thisPtr, XsSize count, struct XsQuaternion const* src);
#define XsQuaternionArray_destruct(thisPtr)		XsArray_destruct(thisPtr)
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
struct XsQuaternionArray : public XsArrayImpl<XsQuaternion, g_xsQuaternionArrayDescriptor, XsQuaternionArray> {
	//! \brief Constructs an XsQuaternionArray
	inline explicit XsQuaternionArray(XsSize sz = 0, XsQuaternion const* src = 0)
		 : ArrayImpl(sz, src)
	{
	}

	//! \brief Constructs an XsQuaternionArray as a copy of \a other
	inline XsQuaternionArray(XsQuaternionArray const& other)
		 : ArrayImpl(other)
	{
	}

	//! \brief Constructs an XsQuaternionArray that references the data supplied in \a ref
	inline explicit XsQuaternionArray(XsQuaternion* ref, XsSize sz, XsDataFlags flags = XSDF_None)
		: ArrayImpl(ref, sz, flags)
	{
	}

#ifndef XSENS_NOITERATOR
	//! \brief Constructs an XsQuaternionArray with the array bound by the supplied iterators \a beginIt and \a endIt
	template <typename Iterator>
	inline XsQuaternionArray(Iterator beginIt, Iterator endIt)
		: ArrayImpl(beginIt, endIt)
	{
	}
#endif

};
#endif

#endif
