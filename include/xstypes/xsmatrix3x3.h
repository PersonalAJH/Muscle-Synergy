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

#ifndef XSMATRIX3X3_H
#define XSMATRIX3X3_H

#include "xsmatrix.h"

struct XsMatrix3x3;
#ifdef __cplusplus
extern "C" {
#endif
#ifndef __cplusplus
typedef struct XsMatrix3x3 XsMatrix3x3;
#endif


XSTYPES_DLL_API void XsMatrix3x3_construct(XsMatrix3x3* thisPtr);
XSTYPES_DLL_API void XsMatrix3x3_assign(XsMatrix3x3* thisPtr, const XsReal* src, XsSize srcStride);
XSTYPES_DLL_API void XsMatrix3x3_destruct(XsMatrix3x3* thisPtr);
XSTYPES_DLL_API void XsMatrix3x3_copy(XsMatrix* copy, XsMatrix3x3 const* src);

#ifdef __cplusplus
} // extern "C"

  /* This is allowed since the C standard says that no padding appears before the first member of a struct.
	Basically we're defining a union between a C++ inherited type and a C encapsulated type.
*/
struct XsMatrix3x3 : public XsMatrix {
XSCPPPROTECTED
#endif
#ifndef __cplusplus
struct XsMatrix3x3 {
	struct XsMatrix m_matrix;	//!< The underlying XsMatrix
#endif
	XsReal XSCCONST m_fixedData[9];			//!< Fixed storage for the elements of the matrix

#ifdef __cplusplus
public:
	//! \brief Constructs an XsMatrix3x3
	XsMatrix3x3() : XsMatrix(m_fixedData, 3, 3, 3, XSDF_FixedSize)
	{
	}

	//! \brief Constructs an XsMatrix3x3 from an \a other XsMatrix
	XsMatrix3x3(const XsMatrix& other) : XsMatrix(other, m_fixedData, 3, 3, 3, XSDF_FixedSize)
	{
	}

	//! \brief Constructs an XsMatrix3x3 from an \a other XsMatrix
	XsMatrix3x3(const XsMatrix3x3& other) : XsMatrix(other, m_fixedData, 3, 3, 3, XSDF_FixedSize)
	{
	}

	//! \brief Constructs an XsMatrix3x3 from a set of values
	XsMatrix3x3(XsReal r1c1, XsReal r1c2, XsReal r1c3,
				XsReal r2c1, XsReal r2c2, XsReal r2c3,
				XsReal r3c1, XsReal r3c2, XsReal r3c3) : XsMatrix(m_fixedData, 3, 3, 3, XSDF_FixedSize)
	{
		m_fixedData[0] = r1c1;
		m_fixedData[1] = r1c2;
		m_fixedData[2] = r1c3;
		m_fixedData[3] = r2c1;
		m_fixedData[4] = r2c2;
		m_fixedData[5] = r2c3;
		m_fixedData[6] = r3c1;
		m_fixedData[7] = r3c2;
		m_fixedData[8] = r3c3;
	}
//	using XsMatrix::operator=;
//	using XsMatrix::operator[];
#endif
};
#if 0
}	// for Qt lupdate parser
#endif

#endif
