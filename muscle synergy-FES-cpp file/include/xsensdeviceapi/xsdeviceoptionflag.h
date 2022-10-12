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

#ifndef XSDEVICEOPTIONFLAG_H
#define XSDEVICEOPTIONFLAG_H

/*!	\addtogroup enums Global enumerations
@{
*/
/*! \brief Used to enable or disable some device options
	\sa XsDevice::setDeviceOptionFlags
	\note Not all devices support all options.
*/
enum XsDeviceOptionFlag
{
	XDOF_DisableAutoStore				= 0x00000001,	//!< When set to 1, automatic writing of configuration will be disabled.
	XDOF_DisableAutoMeasurement			= 0x00000002,	//!< When set to 1, the MT will stay in Config Mode upon start up.
	XDOF_EnableBeidou					= 0x00000004,	//!< When set to 1, enables Beidou, disables GLONASS (MTi-G).
	XDOF_DisableGps						= 0x00000008,	//!< When set to 1, disables GPS (MTi-G).
	XDOF_EnableAhs						= 0x00000010,	//!< When set to 1, the MTi will have Active Heading Stabilization (AHS) enabled.
	XDOF_Unused1						= 0x00000020,	//!< Unused flag.
	XDOF_EnableConfigurableBusId		= 0x00000040,	//!< When set to 1, allows to configure the BUS ID.
	XDOF_EnableInrunCompassCalibration	= 0x00000080,	//!< When set to 1, the MTi will have In-run Compass Calibration (ICC) enabled.
	XDOF_DisableSleepMode				= 0x00000100,	//!< When set to 1, an MTw will not enter sleep mode after a scan timeout. It will scan indefinitely.

	XDOF_None							= 0x00000000,	//!< When set to 1, disables all option flags.
	XDOF_All							= 0xFFFFFFFF	//!< When set to 1, enables all option flags.
};
/* @} */
typedef enum  XsDeviceOptionFlag XsDeviceOptionFlag;

#endif
