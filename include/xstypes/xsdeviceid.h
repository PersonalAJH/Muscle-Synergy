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

#ifndef XSDEVICEID_H
#define XSDEVICEID_H

#include "xstypesconfig.h"
#include "pstdint.h"
#include "xsstring.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifndef __cplusplus
#define XSDEVICEID_INITIALIZER	{ 0, 0, "", 0, 0 }
#endif

struct XsDeviceId;

XSTYPES_DLL_API int XsDeviceId_isLegacyDeviceId(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_legacyBit(struct XsDeviceId const* thisPtr);

XSTYPES_DLL_API int XsDeviceId_isMtiX(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtiX0(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtiX00(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtigX00(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtigX10(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtw(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtw2(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtx(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtx2(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isBodyPack(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isWirelessMaster(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwinda(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwindaStation(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwindaDongle(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwindaOem(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwinda2(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwinda2Station(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwinda2Dongle(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAwinda2Oem(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isSyncStation(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isSyncStation2(struct XsDeviceId const* thisPtr);

XSTYPES_DLL_API int XsDeviceId_isImu(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isVru(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isAhrs(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isGnss(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isContainerDevice(struct XsDeviceId const* thisPtr);

XSTYPES_DLL_API int XsDeviceId_isMt(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMti(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtig(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMark4(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMark5(struct XsDeviceId const* thisPtr);

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------

XSTYPES_DLL_API void XsDeviceId_toString(struct XsDeviceId const* thisPtr, XsString* str);
XSTYPES_DLL_API void XsDeviceId_fromString(struct XsDeviceId* thisPtr, XsString const* str);
XSTYPES_DLL_API int XsDeviceId_isValid(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API void XsDeviceId_swap(struct XsDeviceId* a, struct XsDeviceId* b);
XSTYPES_DLL_API int XsDeviceId_contains(struct XsDeviceId const* a, struct XsDeviceId const* b);
XSTYPES_DLL_API int XsDeviceId_isType(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API void XsDeviceId_typeName(struct XsDeviceId const* thisPtr, XsString* str);
XSTYPES_DLL_API uint32_t XsDeviceId_type(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API uint32_t XsDeviceId_deviceType(struct XsDeviceId const* thisPtr, int detailed);
XSTYPES_DLL_API uint32_t XsDeviceId_deviceTypeMask(struct XsDeviceId const* thisPtr, int detailed);

//============================================================================================================
//==== Deprecated methods follow                                                                         =====
//============================================================================================================
XSTYPES_DLL_API int XsDeviceId_isMtMk4(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_X(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_1(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_2(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_3(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_7(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_X0(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_10(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_20(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_30(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_X00(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_100(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_200(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_300(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_400(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_500(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_600(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_700(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_710(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_800(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk4_900(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_X0(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_10(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_20(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_30(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_X00(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_100(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_200(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_300(struct XsDeviceId const* thisPtr);
XSTYPES_DLL_API int XsDeviceId_isMtMk5_710(struct XsDeviceId const* thisPtr);
//============================================================================================================

#ifdef __cplusplus
} // extern "C"
#endif

struct XsDeviceId {
#ifdef __cplusplus
	/*! \brief Constructor that creates an XsDeviceId from the supplied \a deviceId */
	inline XsDeviceId(uint64_t serialNumber = 0)
		: m_deviceId(0)
		, m_serialNumber(serialNumber)
		, m_productCode()
	{
		m_productCode[0] = '\0';
		if (isLegacyDeviceId())
			m_deviceId = (uint32_t)m_serialNumber;
	}

	/*! \brief Constructor that creates an XsDeviceId from the supplied \a productcode, \a hardwareVersion, \a productVariant and \a serialNumber*/
	inline XsDeviceId(const char* productCode, uint16_t hardwareVersion, uint32_t productVariant, uint64_t serialNumber)
		: m_deviceId(0)
		, m_serialNumber(serialNumber)
		, m_productCode()
		, m_hardwareVersion(hardwareVersion)
		, m_productVariant(productVariant)
	{
		m_productCode[0] = '\0';
		if (!isLegacyDeviceId())
			strcpy(m_productCode, productCode);
	}

	/*! \brief Constructor that creates an XsDeviceId from the supplied XsDeviceId \a other */
	inline XsDeviceId(const XsDeviceId& other)
		: m_deviceId(other.m_deviceId)
		, m_serialNumber(other.m_serialNumber)
		, m_productCode()
		, m_hardwareVersion(other.m_hardwareVersion)
		, m_productVariant(other.m_productVariant)
	{
		m_productCode[0] = '\0';
		if (!isLegacyDeviceId())
			strcpy(m_productCode, other.m_productCode);
	}
	/*! \brief Assign the \a other deviceId to this XsDeviceId */
	inline const XsDeviceId& operator=(const XsDeviceId& other)
	{
		if (this != &other)
		{
			m_deviceId = other.m_deviceId;
			m_serialNumber = other.m_serialNumber;
			strcpy(m_productCode, other.m_productCode);
			m_hardwareVersion = other.m_hardwareVersion;
			m_productVariant = other.m_productVariant;
		}
		return *this;
	}
	/*! \brief Assign the \a serialNumber to this XsDeviceId */
	inline const XsDeviceId& operator=(uint64_t serialNumber)
	{
		m_serialNumber = serialNumber;
		if (isLegacyDeviceId())
			m_deviceId = (uint32_t)m_serialNumber;
		return *this;
	}
	/*! \brief \copybrief XsDeviceId_legacyBit(const struct XsDeviceId*) */
	inline uint32_t legacyBit() const
	{
		return XsDeviceId_legacyBit(this);
	}
	/*! \brief \copybrief XsDeviceId_isLegacyDeviceId(const struct XsDeviceId*) */
	inline bool isLegacyDeviceId() const
	{
		return 0 != XsDeviceId_isLegacyDeviceId(this);
	}
	/*! \brief Returns the deviceId as an unsigned integer */
	inline uint32_t toInt() const
	{
		return m_deviceId;
	}
	/*! \brief Returns the serialnumber as an unsigned integer */
	inline uint64_t toInt64() const
	{
		return m_serialNumber;
	}
	/*! \brief \copybrief XsDeviceId_isMtiX(const struct XsDeviceId*) */
	inline bool isMtiX() const
	{
		return 0 != XsDeviceId_isMtiX(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtiX0(const struct XsDeviceId*) */
	inline bool isMtiX0() const
	{
		return 0 != XsDeviceId_isMtiX0(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtiX00(const struct XsDeviceId*) */
	inline bool isMtiX00() const
	{
		return 0 != XsDeviceId_isMtiX00(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtigX00(const struct XsDeviceId*) */
	inline bool isMtigX00() const
	{
		return 0 != XsDeviceId_isMtigX00(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtigX10(const struct XsDeviceId*) */
	inline bool isMtigX10() const
	{
		return 0 != XsDeviceId_isMtigX10(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtw(const struct XsDeviceId*) */
	inline bool isMtw() const
	{
		return 0 != XsDeviceId_isMtw(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtw2(const struct XsDeviceId*) */
	inline bool isMtw2() const
	{
		return 0 != XsDeviceId_isMtw2(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtx(const struct XsDeviceId*) */
	inline bool isMtx() const
	{
		return 0 != XsDeviceId_isMtx(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtx2(const struct XsDeviceId*) */
	inline bool isMtx2() const
	{
		return 0 != XsDeviceId_isMtx2(this);
	}
	/*! \brief \copybrief XsDeviceId_isBodyPack(const struct XsDeviceId*) */
	inline bool isBodyPack() const
	{
		return 0 != XsDeviceId_isBodyPack(this);
	}
	/*! \brief \copybrief XsDeviceId_isWirelessMaster(const struct XsDeviceId*) */
	inline bool isWirelessMaster() const
	{
		return 0 != XsDeviceId_isWirelessMaster(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwinda(const struct XsDeviceId*) */
	inline bool isAwinda() const
	{
		return 0 != XsDeviceId_isAwinda(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwindaStation(const struct XsDeviceId*) */
	inline bool isAwindaStation() const
	{
		return 0 != XsDeviceId_isAwindaStation(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwindaDongle(const struct XsDeviceId*) */
	inline bool isAwindaDongle() const
	{
		return 0 != XsDeviceId_isAwindaDongle(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwindaOem(const struct XsDeviceId*) */
	inline bool isAwindaOem() const
	{
		return 0 != XsDeviceId_isAwindaOem(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwinda2(const struct XsDeviceId*) */
	inline bool isAwinda2() const
	{
		return 0 != XsDeviceId_isAwinda2(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwinda2Station(const struct XsDeviceId*) */
	inline bool isAwinda2Station() const
	{
		return 0 != XsDeviceId_isAwinda2Station(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwinda2Dongle(const struct XsDeviceId*) */
	inline bool isAwinda2Dongle() const
	{
		return 0 != XsDeviceId_isAwinda2Dongle(this);
	}
	/*! \brief \copybrief XsDeviceId_isAwinda2Oem(const struct XsDeviceId*) */
	inline bool isAwinda2Oem() const
	{
		return 0 != XsDeviceId_isAwinda2Oem(this);
	}
	/*! \brief \copybrief XsDeviceId_isSyncStation(const struct XsDeviceId*) */
	inline bool isSyncStation() const
	{
		return 0 != XsDeviceId_isSyncStation(this);
	}
	/*! \brief \copybrief XsDeviceId_isSyncStation2(const struct XsDeviceId*) */
	inline bool isSyncStation2() const
	{
		return 0 != XsDeviceId_isSyncStation2(this);
	}
	/*! \brief \copybrief XsDeviceId_isImu(const struct XsDeviceId*) */
	inline bool isImu() const
	{
		return 0 != XsDeviceId_isImu(this);
	}
	/*! \brief \copybrief XsDeviceId_isVru(const struct XsDeviceId*) */
	inline bool isVru() const
	{
		return 0 != XsDeviceId_isVru(this);
	}
	/*! \brief \copybrief XsDeviceId_isAhrs(const struct XsDeviceId*) */
	inline bool isAhrs() const
	{
		return 0 != XsDeviceId_isAhrs(this);
	}
	/*! \brief \copybrief XsDeviceId_isGnss(const struct XsDeviceId*) */
	inline bool isGnss() const
	{
		return 0 != XsDeviceId_isGnss(this);
	}
	/*! \brief \copybrief XsDeviceId_isContainerDevice(const struct XsDeviceId*) */
	inline bool isContainerDevice() const
	{
		return 0 != XsDeviceId_isContainerDevice(this);
	}
	/*! \brief \copybrief XsDeviceId_isMt(const struct XsDeviceId*) */
	inline bool isMt() const
	{
		return 0 != XsDeviceId_isMt(this);
	}
	/*! \brief \copybrief XsDeviceId_isMti(const struct XsDeviceId*) */
	inline bool isMti() const
	{
		return 0 != XsDeviceId_isMti(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtig(const struct XsDeviceId*) */
	inline bool isMtig() const
	{
		return 0 != XsDeviceId_isMtig(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMark4(const struct XsDeviceId*) */
	inline bool isMtMark4() const
	{
		return 0 != XsDeviceId_isMtMark4(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMark5(const struct XsDeviceId*) */
	inline bool isMtMark5() const
	{
		return 0 != XsDeviceId_isMtMark5(this);
	}
	/*! \brief Returns the deviceId as an XsString */
	inline XsString toString() const
	{
		XsString tmp;
		XsDeviceId_toString(this, &tmp);
		return tmp;
	}
	/*! \brief Fills the deviceId with the parsed value from the supplied string \a s
	\param s The string containing the device ID
	*/
	inline void fromString(const XsString &s)
	{
		XsDeviceId_fromString(this, &s);
	}
	/*! \brief \copybrief XsDeviceId_isValid(const struct XsDeviceId*) */
	inline bool isValid() const
	{
		return 0 != XsDeviceId_isValid(this);
	}
	/*! \copydoc XsDeviceId_contains(XsDeviceId const*, XsDeviceId const*) */
	inline bool contains(const XsDeviceId& other) const
	{
		return 0 != XsDeviceId_contains(this, &other);
	}
	/*! \brief Returns true if the ID is just a device type, not an actual device ID */
	inline bool isType() const
	{
		return 0 != XsDeviceId_isType(this);
	}
	/*! \brief Returns the name of the type of device identified by this id */
	inline XsString typeName() const
	{
		XsString rv;
		XsDeviceId_typeName(this, &rv);
		return rv;
	}
	/*! \brief Returns the type of device identified by this id */
	inline uint32_t type() const
	{
		return XsDeviceId_type(this);
	}
	/*! \brief Returns the (detailed) device type of this id
	\param detailed Boolean whether detailed information is returned
	\return The requested device type
	*/
	inline uint32_t deviceType(bool detailed = true) const
	{
		return XsDeviceId_deviceType(this, detailed ? 1 : 0);
	}
	/*! \brief Returns the detailed device type mask of this id
	\param detailed Boolean whether detailed information is returned
	\return The requested device type mask
	*/
	inline uint32_t deviceTypeMask(bool detailed = true) const
	{
		return XsDeviceId_deviceTypeMask(this, detailed ? 1 : 0);
	}

	/*! \brief Returns true if the \a other deviceId matches this deviceId */
	inline bool operator==(const XsDeviceId& other) const { return m_deviceId == other.m_deviceId; }
	/*! \brief Returns true if the \a other deviceId does not match this deviceId */
	inline bool operator!=(const XsDeviceId& other) const { return m_deviceId != other.m_deviceId; }
	/*! \brief Returns true if this deviceId is less than the \a other deviceId */
	inline bool operator<(const XsDeviceId& other) const { return m_deviceId < other.m_deviceId; }
	/*! \brief Returns true if this deviceId is less or equal to the \a other deviceId */
	inline bool operator<=(const XsDeviceId& other) const { return m_deviceId <= other.m_deviceId; }
	/*! \brief Returns true if this deviceId is larger than the \a other deviceId */
	inline bool operator>(const XsDeviceId& other) const { return m_deviceId > other.m_deviceId; }
	/*! \brief Returns true if this deviceId is larger or equal to the \a other deviceId */
	inline bool operator>=(const XsDeviceId& other) const { return m_deviceId >= other.m_deviceId; }


//============================================================================================================
//============================================================================================================
//==== Deprecated methods follow                                                                         =====
//============================================================================================================
//============================================================================================================

	/*! \brief \copybrief XsDeviceId_isMtMk4(const struct XsDeviceId*) */
	inline bool isMtMk4() const
	{
		return 0 != XsDeviceId_isMtMk4(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_X(const struct XsDeviceId*) */
	inline bool isMtMk4_X() const
	{
		return 0 != XsDeviceId_isMtMk4_X(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_1(const struct XsDeviceId*) */
	inline bool isMtMk4_1() const
	{
		return 0 != XsDeviceId_isMtMk4_1(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_2(const struct XsDeviceId*) */
	inline bool isMtMk4_2() const
	{
		return 0 != XsDeviceId_isMtMk4_2(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_3(const struct XsDeviceId*) */
	inline bool isMtMk4_3() const
	{
		return 0 != XsDeviceId_isMtMk4_3(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_7(const struct XsDeviceId*) */
	inline bool isMtMk4_7() const
	{
		return 0 != XsDeviceId_isMtMk4_7(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_X0(const struct XsDeviceId*) */
	inline bool isMtMk4_X0() const
	{
		return 0 != XsDeviceId_isMtMk4_X0(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_10(const struct XsDeviceId*) */
	inline bool isMtMk4_10() const
	{
		return 0 != XsDeviceId_isMtMk4_10(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_20(const struct XsDeviceId*) */
	inline bool isMtMk4_20() const
	{
		return 0 != XsDeviceId_isMtMk4_20(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_30(const struct XsDeviceId*) */
	inline bool isMtMk4_30() const
	{
		return 0 != XsDeviceId_isMtMk4_30(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_X00(const struct XsDeviceId*) */
	inline bool isMtMk4_X00() const
	{
		return 0 != XsDeviceId_isMtMk4_X00(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_100(const struct XsDeviceId*) */
	inline bool isMtMk4_100() const
	{
		return 0 != XsDeviceId_isMtMk4_100(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_200(const struct XsDeviceId*) */
	inline bool isMtMk4_200() const
	{
		return 0 != XsDeviceId_isMtMk4_200(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_300(const struct XsDeviceId*) */
	inline bool isMtMk4_300() const
	{
		return 0 != XsDeviceId_isMtMk4_300(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_400(const struct XsDeviceId*) */
	inline bool isMtMk4_400() const
	{
		return 0 != XsDeviceId_isMtMk4_400(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_500(const struct XsDeviceId*) */
	inline bool isMtMk4_500() const
	{
		return 0 != XsDeviceId_isMtMk4_500(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_600(const struct XsDeviceId*) */
	inline bool isMtMk4_600() const
	{
		return 0 != XsDeviceId_isMtMk4_600(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_700(const struct XsDeviceId*) */
	inline bool isMtMk4_700() const
	{
		return 0 != XsDeviceId_isMtMk4_700(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_710(const struct XsDeviceId*) */
	inline bool isMtMk4_710() const
	{
		return 0 != XsDeviceId_isMtMk4_710(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_800(const struct XsDeviceId*) */
	inline bool isMtMk4_800() const
	{
		return 0 != XsDeviceId_isMtMk4_800(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk4_900(const struct XsDeviceId*) */
	inline bool isMtMk4_900() const
	{
		return 0 != XsDeviceId_isMtMk4_900(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5(const struct XsDeviceId*) */
	inline bool isMtMk5() const
	{
		return 0 != XsDeviceId_isMtMk5(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_X0(const struct XsDeviceId*) */
	inline bool isMtMk5_X0() const
	{
		return 0 != XsDeviceId_isMtMk5_X0(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_10(const struct XsDeviceId*) */
	inline bool isMtMk5_10() const
	{
		return 0 != XsDeviceId_isMtMk5_10(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_20(const struct XsDeviceId*) */
	inline bool isMtMk5_20() const
	{
		return 0 != XsDeviceId_isMtMk5_20(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_30(const struct XsDeviceId*) */
	inline bool isMtMk5_30() const
	{
		return 0 != XsDeviceId_isMtMk5_30(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_X00(const struct XsDeviceId*) */
	inline bool isMtMk5_X00() const
	{
		return 0 != XsDeviceId_isMtMk5_X00(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_100(const struct XsDeviceId*) */
	inline bool isMtMk5_100() const
	{
		return 0 != XsDeviceId_isMtMk5_100(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_200(const struct XsDeviceId*) */
	inline bool isMtMk5_200() const
	{
		return 0 != XsDeviceId_isMtMk5_200(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_300(const struct XsDeviceId*) */
	inline bool isMtMk5_300() const
	{
		return 0 != XsDeviceId_isMtMk5_300(this);
	}
	/*! \brief \copybrief XsDeviceId_isMtMk5_710(const struct XsDeviceId*) */
	inline bool isMtMk5_710() const
	{
		return 0 != XsDeviceId_isMtMk5_710(this);
	}

//============================================================================================================

private:
#endif
	// Legacy device identification
	uint32_t m_deviceId;	//!< The actual device id

	// Future device identification
	uint64_t m_serialNumber; //!< The serialnumber of a device
	char m_productCode[24]; //!< The productcode of a device
	uint16_t m_hardwareVersion; //!< The hardware version of a device
	uint32_t m_productVariant;	//!< The product variant of a device
};

typedef struct XsDeviceId XsDeviceId;

#if defined(__cplusplus) && !defined(XSENS_NO_STL)
namespace std
{
	template<typename _CharT, typename _Traits>
	basic_ostream<_CharT, _Traits>& operator<<(basic_ostream<_CharT, _Traits>& o, XsDeviceId const& xd)
	{
		return (o << xd.toString());
	}
}

inline XsString& operator<<(XsString& o, XsDeviceId const& xd)
{
	o.append(xd.toString());
	return o;
}

#endif

#endif
