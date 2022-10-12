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

#ifndef XSENS_GENERIC_MATRIX_H
#define XSENS_GENERIC_MATRIX_H

#include "xsens_math_throw.h"

#ifndef XSENS_MATH_FIRMWARE
#	ifndef XSENS_EXCEPTION_H
#		include "xsexception.h"
#	endif
#endif

#ifdef XSENS_GENERIC_MATRIX_RANGE_CHECKS
#	ifdef _MSC_VER
#		define XSENS_GENERIC_MATRIX_THROW throw(...)
#	else
#		define XSENS_GENERIC_MATRIX_THROW
#	endif
#else
#	define XSENS_GENERIC_MATRIX_THROW
#endif

#ifndef XSENS_THROW_BAD_ALLOC
#	ifdef XSENS_NO_EXCEPTIONS
#       include <assert.h>
#       define XSENS_THROW_BAD_ALLOC XM_THROW("Bad alloc")
#   else
#       define XSENS_THROW_BAD_ALLOC throw std::bad_alloc()
#   endif
#endif

#ifndef _PSTDINT_H_INCLUDED
#include <xstypes/pstdint.h>
#endif

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
namespace xsens
{
namespace {
/*! \brief Swap the values of two objects of a basic type T through assignment */
template <typename T>
inline void swapb(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
}

/*! \brief Generic matrix class

	This class can store items of the given type.
	Items in the list can be accessed through the [] operator or the get() function.

	Do NOT use any item type that requires a constructor to work correctly. Pointers to these
	objects can work though.
*/
template <typename T>
class GenericMatrix
{
protected:
	T* m_data;					//!< The array containing the items.
	uint32_t m_rows;			//!< The number of rows currently in the matrix.
	uint32_t m_cols;			//!< The number of columns currently in the matrix.
	uint32_t m_allocSize;		//!< The number of elemens currently allocated for the matrix.
	int m_flags;				//!< Flags for data management.

public:
		//! Standard constructor, creates a 1x1 matrix.
	GenericMatrix();
		//! Construct a matrix with a capacity of at least the given size.
	explicit GenericMatrix(const uint32_t newRows, const uint32_t newCols, bool zeroValues = true);
		//! Construct a matrix as a direct copy of another one
	GenericMatrix(const GenericMatrix<T>& src);
		//! Construct a matrix as a copy of a raw data buffer
	explicit GenericMatrix(const uint32_t newRows, const uint32_t newCols, const T* src);
		//! Construct a matrix using the given buffer, useful when the matrix should be stack allocated.
	explicit GenericMatrix(const uint32_t newRows, const uint32_t newCols, T* buffer, XsDataFlags flags);
		//! Destroy the matrix. This does NOT automatically delete items IN the list.
	virtual ~GenericMatrix();

		//! Sets the size of the matrix to the new dimensions. The contents should be considered garbage. If zeroValues is set to true a memset 0 is done on the newly created items
	void setSize(uint32_t newRows, uint32_t newCols, bool zeroValues = true);
		//! Retrieves the item at the given row,col. An index beyond the end causes an exception.
	T& get(const uint32_t row, const uint32_t cols) const XSENS_GENERIC_MATRIX_THROW;
		//! Retrieves a pointer to the first item of the given row. An index beyond the end causes an exception.
	T* operator [] (const uint32_t row) const XSENS_GENERIC_MATRIX_THROW;
		//! Returns the number of rows currently in the matrix.
	uint32_t rows(void) const { return m_rows; }
		//! Returns the number of cols currently in the matrix.
	uint32_t cols(void) const { return m_cols; }
		//! Returns the number of items currently in the matrix.
	uint32_t count(void) const { return m_rows*m_cols; }
		//! Returns the number of items currently in the matrix.
	uint32_t size(void) const { return m_rows*m_cols; }
		//! Copy a matrix into this one
	GenericMatrix<T>& operator = (const GenericMatrix<T>& src);
		//! Swap a matrix with this one
	void swap(GenericMatrix<T>& other);
		//! Calls memset 0 on the contents of the matrix
	void zeroValues();
};

template <typename T>
GenericMatrix<T>::GenericMatrix()
	: m_rows(1)
	, m_cols(1)
	, m_flags(XSDF_Managed)
{
	m_data = (T*)malloc(m_rows*m_cols * sizeof(T));

	if (!m_data)
		XSENS_THROW_BAD_ALLOC;

	m_allocSize = m_rows*m_cols;
}

template <typename T>
GenericMatrix<T>::GenericMatrix(uint32_t newRows, uint32_t newCols, bool zeroVals)
	: m_rows(newRows)
	, m_cols(newCols)
	, m_flags(XSDF_Managed)
{
	m_data = (T*)malloc(sizeof(T) * (size_t)m_rows*m_cols);

	if (!m_data)
		XSENS_THROW_BAD_ALLOC;

	m_allocSize = m_rows*m_cols;

	if (zeroVals)
		zeroValues();
}

template <typename T>
GenericMatrix<T>::GenericMatrix(const GenericMatrix<T>& src)
	: m_rows(src.m_rows)
	, m_cols(src.m_cols)
	, m_flags(XSDF_Managed)
{
	m_data = (T*)malloc(sizeof(T) * (size_t)m_rows*m_cols);

	if (!m_data)
		XSENS_THROW_BAD_ALLOC;

	m_allocSize = m_rows*m_cols;

	memcpy(m_data, src.m_data, sizeof(T) * (size_t)m_rows*m_cols);
}

template <typename T>
GenericMatrix<T>::GenericMatrix(const uint32_t newRows, uint32_t newCols, const T* src)
	: m_rows(newRows)
	, m_cols(newCols)
	, m_flags(XSDF_Managed)
{
	m_data = (T*)malloc(sizeof(T) * (size_t)m_rows*m_cols);

	if (!m_data)
		XSENS_THROW_BAD_ALLOC;

	m_allocSize = m_rows*m_cols;

	memcpy(m_data, src, sizeof(T) * (size_t)m_rows*m_cols);
}

template <typename T>
GenericMatrix<T>::GenericMatrix(const uint32_t newRows, const uint32_t newCols, T* const buffer, XsDataFlags flags)
	: m_rows(newRows)
	, m_cols(newCols)
	, m_flags(flags)
{
	if (m_flags & XSDF_FixedSize)
	{
		m_data = buffer;

		if (size() == 0)
			m_flags |= XSDF_Empty;
	}

	if (m_flags & XSDF_Managed)
		m_data = (T*)malloc(sizeof(T) * (size_t)m_rows*m_cols);

	if (!m_data)
		XSENS_THROW_BAD_ALLOC;

	m_allocSize = m_rows*m_cols;

	if (m_flags & XSDF_Managed)
		memcpy(m_data, buffer, sizeof(T) * (size_t)m_rows*m_cols);
}

template <typename T>
GenericMatrix<T>::~GenericMatrix()
{
	if (m_flags & XSDF_Managed)
		free(m_data);

	if (!(m_flags & XSDF_FixedSize))
		m_data = NULL;
	else
		m_flags |= XSDF_Empty;
}

template <typename T>
void GenericMatrix<T>::setSize(uint32_t newRows, uint32_t newCols, bool zeroVals)
{
	if (newRows == m_rows && newCols == m_cols)
	{
		if (zeroVals)
			zeroValues();

		return;
	}

#ifdef XSENS_MATH_RESTRICT_RESIZE
	if (m_data && !(m_flags & XSDF_Managed))
		XM_THROW("resizing of this object is not allowed");
#endif

	const uint32_t newSize = newRows * newCols;

	if (m_flags & XSDF_FixedSize)
	{
		if (newSize == 0)
		{
			m_flags |= XSDF_Empty;
			m_rows = newRows;
			m_cols = newCols;
			return;
		}

		assert(newSize <= size());
		m_flags &= ~XSDF_Empty;
	}

	if (newSize > m_allocSize || newSize == 0)
	{
		if (m_flags & XSDF_Managed)
		{
			free(m_data);
			m_data = 0;
			m_allocSize = 0;
		}

		if (newSize > 0)
		{
			m_data = (T*)malloc(sizeof(T) * (size_t)newRows*newCols);
			m_flags = XSDF_Managed;
			m_allocSize = newRows*newCols;
		}
	}

	m_rows = newRows;
	m_cols = newCols;

	if (!m_data)
	{
		XSENS_THROW_BAD_ALLOC;
	}

	if (zeroVals)
		zeroValues();
}

template <typename T>
T& GenericMatrix<T>::get(uint32_t row, uint32_t col) const XSENS_GENERIC_MATRIX_THROW
{
#ifdef XSENS_GENERIC_MATRIX_RANGE_CHECKS
	if (row >= m_rows || col >= m_cols)
		XM_THROW("index out of bounds");
#endif
	return m_data[row*m_cols + col];
}

template <typename T>
T* GenericMatrix<T>::operator [] (const uint32_t row) const XSENS_GENERIC_MATRIX_THROW
{
#ifdef XSENS_GENERIC_MATRIX_RANGE_CHECKS
	if (row >= m_rows)
		XM_THROW("index out of bounds");
#endif
	return &m_data[row*m_cols];
}

template <typename T>
void GenericMatrix<T>::zeroValues()
{
	memset(m_data, 0, sizeof(T) * (size_t)m_rows*m_cols);
}

template <typename T>
void GenericMatrix<T>::swap(GenericMatrix<T>& other)
{
	swapb(m_rows, other.m_rows);
	swapb(m_cols, other.m_cols);
	swapb(m_allocSize, other.m_allocSize);
	swapb(m_flags, other.m_flags);
	swapb(m_data, other.m_data);
}

template <typename T>
GenericMatrix<T>& GenericMatrix<T>::operator = (const GenericMatrix<T>& src)
{
	if (this != &src)
	{
		GenericMatrix temp(src);
		swap(temp);
	}
	return *this;
}

}

#endif
#endif
