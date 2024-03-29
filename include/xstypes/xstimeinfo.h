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

#ifndef XSTIMEINFO_H
#define XSTIMEINFO_H

#include "xstypesconfig.h"
#include "pstdint.h"

#ifdef __cplusplus
extern "C"
{
#endif
#ifndef __cplusplus
#define XSTIMEINFO_INITIALIZER	{ 0, 0 ,0, 0, 0, 0, 0, 0, 0}
#endif
struct XsTimeInfo;

XSTYPES_DLL_API void XsTimeInfo_currentTime(struct XsTimeInfo * thisPtr);
XSTYPES_DLL_API void XsTimeInfo_currentLocalTime(struct XsTimeInfo * thisPtr);
XSTYPES_DLL_API void XsTimeInfo_makeUtc(struct XsTimeInfo * thisPtr);

#ifdef __cplusplus
} // extern "C"
#endif

/*! \brief A structure for storing Time values. */
struct XsTimeInfo {
	uint32_t	m_nano;			//!< \brief Nanosecond part of the time
	uint16_t	m_year;			//!< \brief The year (if date is valid)
	uint8_t		m_month;		//!< \brief The month (if date is valid)
	uint8_t		m_day;  		//!< \brief The day of the month (if date is valid)
	uint8_t		m_hour;			//!< \brief The hour (if time is valid)
	uint8_t		m_minute;		//!< \brief The minute (if time is valid)
	uint8_t		m_second;		//!< \brief The second (if time is valid)
	uint8_t		m_valid;		//!< \brief Validity indicator \details When received: bit (0) - UTC Date is valid; bit (1) - UTC Time of Day is valid; bit (2) - UTC Time of Day has been fully resolved (i.e. no seconds uncertainty).
	int16_t		m_utcOffset;	//!< \brief Offset to UTC time in minutes. This value can be added to the stored time to get UTC time.

#ifdef __cplusplus
	/*! \copydoc XsTimeInfo_currentTime
		\return The current UTC Time
	*/
	inline static XsTimeInfo currentTime()
	{
		XsTimeInfo tmp;
		XsTimeInfo_currentTime(&tmp);
		return tmp;
	}

	/*! \copydoc XsTimeInfo_currentLocalTime
		\return The current local Time
	*/
	inline static XsTimeInfo currentLocalTime()
	{
		XsTimeInfo tmp;
		XsTimeInfo_currentLocalTime(&tmp);
		return tmp;
	}

	/*! \brief Returns true if all fields of this and \a other are exactly identical */
	inline bool operator == (const XsTimeInfo& other) const
	{
		return	m_nano		== other.m_nano &&
				m_year		== other.m_year &&
				m_month		== other.m_month &&
				m_day		== other.m_day &&
				m_hour		== other.m_hour &&
				m_minute	== other.m_minute &&
				m_second	== other.m_second &&
				m_valid		== other.m_valid &&
				m_utcOffset	== other.m_utcOffset;
	}

	/*! \brief Removes the local time information, making the object pure UTC */
	void makeUtc()
	{
		if (m_utcOffset)
			XsTimeInfo_makeUtc(this);
	}
#endif
};
typedef struct XsTimeInfo XsTimeInfo;

#endif
