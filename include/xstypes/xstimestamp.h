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

#ifndef XSTIMESTAMP_H
#define XSTIMESTAMP_H

#include "xstypesconfig.h"
#include "pstdint.h"

#ifdef __cplusplus
#ifndef XSENS_NO_STL
#include "xsstring.h"
#endif
#include "xstimeinfo.h"
extern "C" {
#endif
#ifndef __cplusplus
#define XSTIMESTAMP_INITIALIZER	{ 0 }
#endif

struct XsTimeStamp;
struct XsTimeInfo;
struct XsString;

XSTYPES_DLL_API void XsTimeStamp_setMilliSecondTime(struct XsTimeStamp* thisPtr, int64_t t);
XSTYPES_DLL_API double XsTimeStamp_timeOfDay(const struct XsTimeStamp* thisPtr);
XSTYPES_DLL_API int64_t XsTimeStamp_secondTime(const struct XsTimeStamp* thisPtr);
XSTYPES_DLL_API int32_t XsTimeStamp_milliSecondPart(const struct XsTimeStamp* thisPtr);
XSTYPES_DLL_API int32_t XsTimeStamp_secondPart(const struct XsTimeStamp* thisPtr);
XSTYPES_DLL_API int32_t XsTimeStamp_minutePart(const struct XsTimeStamp* thisPtr);
XSTYPES_DLL_API int32_t XsTimeStamp_hourPart(const struct XsTimeStamp* thisPtr);
XSTYPES_DLL_API int64_t XsTimeStamp_now(struct XsTimeStamp* thisPtr);
XSTYPES_DLL_API int64_t XsTimeStamp_maxValue(void);

XSTYPES_DLL_API int64_t XsTimeStamp_fromTimeInfo(struct XsTimeStamp* thisPtr, const struct XsTimeInfo* info);
XSTYPES_DLL_API void XsTimeStamp_toTimeInfo(struct XsTimeStamp const* thisPtr, struct XsTimeInfo* info);
#ifndef XSENS_NO_STL
XSTYPES_DLL_API void XsTimeStamp_toString(struct XsTimeStamp const* thisPtr, struct XsString* result);
#endif
XSTYPES_DLL_API void XsTimeStamp_utcToLocalTime(struct XsTimeStamp const* thisPtr, struct XsTimeStamp* local);
XSTYPES_DLL_API void XsTimeStamp_localToUtcTime(struct XsTimeStamp const* thisPtr, struct XsTimeStamp* utc);
XSTYPES_DLL_API void XsTimeStamp_utcToLocalTime2(struct XsTimeStamp const* thisPtr, struct XsTimeStamp* local, const struct XsTimeInfo* info);
XSTYPES_DLL_API void XsTimeStamp_localToUtcTime2(struct XsTimeStamp const* thisPtr, struct XsTimeStamp* utc, const struct XsTimeInfo* info);

#ifdef __cplusplus
} // extern "C"
#endif

/*!	\struct XsTimeStamp
	\brief Class for managing timestamps in a unified way.
*/
struct XsTimeStamp {
#ifdef __cplusplus
	/*! \brief Construct a timestamp with \a t as the time in milliseconds. */
	inline XsTimeStamp(int64_t t = 0) : m_msTime(t) {}

	/*! \brief Construct a timestamp with \a t as the time in milliseconds. */
	inline XsTimeStamp(int t) : m_msTime(t) {}

	/*! \brief Construct a timestamp with \a t as the time in seconds. */
	inline explicit XsTimeStamp(double t) : m_msTime((int64_t)(t*1000.0)) {}

	/*! \brief Construct a copy of \a other. */
	inline XsTimeStamp(const XsTimeStamp& other) : m_msTime(other.m_msTime) {}

	/*! \brief Construct from \a utc */
	inline XsTimeStamp(const XsTimeInfo& info)
	{
		XsTimeStamp_fromTimeInfo(this, &info);
	}

	/*! \brief Convert this timestamp to UTC time */
	inline XsTimeInfo toTimeInfo() const
	{
		XsTimeInfo info;
		XsTimeStamp_toTimeInfo(this, &info);
		return info;
	}

	/*! \brief Convert this timestamp to a XsTimeInfo object \a info */
	inline void toTimeInfo(XsTimeInfo& info) const
	{
		XsTimeStamp_toTimeInfo(this, &info);
	}

#ifndef XSENS_NO_STL
	/*! \brief Convert this timestamp to a string in format YYYY/MM/DD hh:mm:ss.nnn */
	inline XsString toString() const
	{
		XsString result;
		XsTimeStamp_toString(this, &result);
		return result;
	}
#endif

	/*! \brief Assign the contents of the \a other timestamp to this timestamp. */
	inline XsTimeStamp& operator = (const XsTimeStamp& other)
	{
		//lint --e{1529} trivial assignment
		m_msTime = other.m_msTime;
		return *this;
	}

	/*! \brief Get the stored time as milliseconds. */
	inline int64_t msTime(void) const
	{ return m_msTime; }

	/*! \brief Set the stored time to \a t milliseconds. */
	inline void setMsTime(int64_t t)
	{ m_msTime = t; }

	/*! \brief Get the time of day component of the stored timestamp in seconds as a double precision value.
	*/
	inline double timeOfDay() const
	{ return XsTimeStamp_timeOfDay(this); }

	/*! \brief Get the time of day component of the stored timestamp in milliseconds
	*/
	inline int64_t msTimeOfDay() const
	{ return m_msTime % (24*60*60*1000); }

	/*! \brief Return the time as seconds */
	inline double secTime() const
	{ return ((double)m_msTime)*0.001; }

	/*! \brief Set the time as seconds */
	inline void setSecTime(double t)
	{ m_msTime = (int64_t) (t*1000.0); }

	/*! \brief Get the sum of the current and the given \a other timestamp. \param other The value to add to this \returns The added timestamp values */
	inline XsTimeStamp operator + (const XsTimeStamp& other) const
	{ return XsTimeStamp(m_msTime + other.m_msTime); }

	/*! \brief Get the current minus the given \a other timestamp. \param other The value to subtract from this \returns The subtracted timestamp values */
	inline XsTimeStamp operator - (const XsTimeStamp& other) const
	{ return XsTimeStamp(m_msTime - other.m_msTime); }

	/*! \brief Get the result of adding the given \a other timestamp to the current timestamp. */
	inline XsTimeStamp& operator += (const XsTimeStamp& other)
	{ m_msTime += other.m_msTime; return *this; }

	/*! \brief Get the result of subtracting the given \a other timestamp from the current timestamp. */
	inline XsTimeStamp& operator -= (const XsTimeStamp& d)
	{ m_msTime -= d.m_msTime; return *this; }

	/*! \brief Test if the given \a other timestamp is smaller than the current timestamp. */
	inline bool operator <  (const XsTimeStamp& other) const
	{ return m_msTime <  other.m_msTime; }

	/*! \brief Test if the given \a other timestamp is smaller than or equal to the current timestamp. */
	inline bool operator <= (const XsTimeStamp& other) const
	{ return m_msTime <= other.m_msTime; }

	/*! \brief Test if the given \a other timestamp is equal to the current timestamp. */
	inline bool operator == (const XsTimeStamp& other) const
	{ return m_msTime == other.m_msTime; }

	/*! \brief Test if the given \a other timestamp is larger than the current timestamp. */
	inline bool operator >  (const XsTimeStamp& other) const
	{ return m_msTime >  other.m_msTime; }

	/*! \brief Test if the given \a other timestamp is larger than or equal to the current timestamp. */
	inline bool operator >= (const XsTimeStamp& other) const
	{ return m_msTime >= other.m_msTime; }

	/*! \brief Test if the given \a other timestamp is not equal to the current timestamp. */
	inline bool operator != (const XsTimeStamp& other) const
	{ return m_msTime != other.m_msTime; }

	/*! \brief Test if the given \a other is smaller than the current timestamp. */
	inline bool operator <  (int other) const
	{ return m_msTime <  other; }

	/*! \brief Test if the given \a other is smaller than or equal to the current timestamp. */
	inline bool operator <= (int other) const
	{ return m_msTime <= other; }

	/*! \brief Test if the given \a other is equal to the current timestamp. */
	inline bool operator == (int other) const
	{ return m_msTime == other; }

	/*! \brief Test if the given \a other is larger than the current timestamp. */
	inline bool operator >  (int other) const
	{ return m_msTime >  other; }

	/*! \brief Test if the given \a other is larger than or equal to the current timestamp. */
	inline bool operator >= (int other) const
	{ return m_msTime >= other; }

	/*! \brief Test if the given \a other is not equal to the current timestamp. */
	inline bool operator != (int other) const
	{ return m_msTime != other; }

	/*! \brief Returns the number of seconds elapsed since the epoch as stored in the XsTimeStamp */
	inline int64_t secondTime() const
	{ return m_msTime/1000; }

	/*! \brief Returns the millisecond part of the time (in the range 0-999) */
	inline int32_t milliSecondPart() const
	{ return (int32_t) (m_msTime % 1000); }

	/*! \brief Returns the seconds part of the time (in the range 0-59) */
	inline int32_t secondPart() const
	{ return (int32_t) ((m_msTime/(1000))%60); }

	/*! \brief Returns the minutes part of the time (in the range 0-59) */
	inline int32_t minutePart() const
	{ return (int32_t) ((m_msTime/(60*1000))%60); }

	/*! \brief Returns the hours part of the time (in the range 0-23) */
	inline int32_t hourPart() const
	{ return (int32_t) ((m_msTime/(60*60*1000))%24); }

	/*! \brief Returns the current time in ms since the epoch (Jan 1st 1970) */
	inline static XsTimeStamp now()
	{
		XsTimeStamp tmp;
		XsTimeStamp_now(&tmp);
		return tmp;
	}

	/*! \brief Returns the current time in ms since the epoch (Jan 1st 1970) */
	inline static int64_t nowMs()
	{
		XsTimeStamp tmp;
		XsTimeStamp_now(&tmp);
		return tmp.msTime();
	}

	/*! \brief Returns the maximum value of an %XsTimeStamp */
	inline static XsTimeStamp maxValue()
	{
		return XsTimeStamp(int64_t(9223372036854775807LL));	//INT64_MAX
	}

	/*! \brief Increment the timestamp by one ms, prefix */
	XsTimeStamp operator++()
	{ return XsTimeStamp(++m_msTime); }

	/*! \brief Increment the timestamp by one ms, postfix */
	XsTimeStamp operator++(int)
	{ return XsTimeStamp(m_msTime++); }

	/*! \brief Decrement the timestamp by one ms, prefix */
	XsTimeStamp operator--()
	{ return XsTimeStamp(--m_msTime); }

	/*! \brief Decrement the timestamp by one ms, postfix */
	XsTimeStamp operator--(int)
	{ return XsTimeStamp(m_msTime--); }

	/*! \brief Convert the supplied time from (assumed) UTC to local time, using the system's local time zone knowledge
		\returns The converted time
		\note Make sure to call XsTime_initializeTime() before calling this function as well as when changing time zones.
	*/
	XsTimeStamp utcToLocalTime() const
	{
		XsTimeStamp local;
		XsTimeStamp_utcToLocalTime(this, &local);
		return local;
	}

	/*! \brief Convert the supplied time from (assumed) local time to UTC, using the system's local time zone knowledge
		\returns The converted time
		\note Make sure to call XsTime_initializeTime() before calling this function as well as when changing time zones.
	*/
	XsTimeStamp localToUtcTime() const
	{
		XsTimeStamp utc;
		XsTimeStamp_localToUtcTime(this, &utc);
		return utc;
	}

	/*! \brief Convert the supplied time from (assumed) UTC to local time, using the offset in \a info
		\param info The XsTimeInfo object containing the time offset to apply
		\returns The converted time
	*/
	XsTimeStamp utcToLocalTime(XsTimeInfo const& info) const
	{
		XsTimeStamp local;
		XsTimeStamp_utcToLocalTime2(this, &local, &info);
		return local;
	}

	/*! \brief Convert the supplied time from (assumed) local time to UTC, using the offset in \a info
		\param info The XsTimeInfo object containing the time offset to apply
		\returns The converted time
	*/
	XsTimeStamp localToUtcTime(XsTimeInfo const& info) const
	{
		XsTimeStamp utc;
		XsTimeStamp_localToUtcTime2(this, &utc, &info);
		return utc;
	}
private:
#endif

	int64_t m_msTime;		//!< The timestamp value
};

typedef struct XsTimeStamp XsTimeStamp;

#endif
