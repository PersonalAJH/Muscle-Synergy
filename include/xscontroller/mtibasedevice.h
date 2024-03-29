/*	Copyright (c) 2003-2018 Xsens Technologies B.V. or subsidiaries worldwide.
	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1.	Redistributions of source code must retain the above copyright notice,
		this list of conditions and the following disclaimer.

	2.	Redistributions in binary form must reproduce the above copyright notice,
		this list of conditions and the following disclaimer in the documentation
		and/or other materials provided with the distribution.

	3.	Neither the names of the copyright holders nor the names of their contributors
		may be used to endorse or promote products derived from this software without
		specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
	THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
	OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR
	TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// half-public file, c++-source code only

#ifndef XSMTIBASEDEVICE_H
#define XSMTIBASEDEVICE_H

#include <xstypes/xsquaternion.h>
#include <xstypes/xssyncline.h>

#include "mtdevice.h"

class ExtendedScenario;
class MtHardwareParams;
class MtContainer;

/*!	\class MtiBaseDevice
	\brief The generic class for MTi devices
*/
class MtiBaseDevice : public MtDeviceEx
{
public:
	/*! \brief Construct a device as a master
		\param comm The communicator to use
		\returns The constructed master device
	*/
	static XsDevice* constructAsMaster(Communicator* comm)
	{
		return new MtiBaseDevice(comm);
	}

	explicit MtiBaseDevice(Communicator* comm);
	explicit MtiBaseDevice(MtContainer *master);
	virtual ~MtiBaseDevice();

	XsOutputConfigurationArray outputConfiguration() const;

	bool setOutputConfiguration(XsOutputConfigurationArray& o) override;

	int getBaseFrequency(XsDataIdentifier dataType = XDI_None) const;
	std::vector<int> supportedUpdateRates(XsDataIdentifier dataType = XDI_None) const override;
	static int calcFrequency(int baseFrequency, uint16_t skipFactor);

	bool setAlignmentRotationMatrix(XsAlignmentFrame frame, const XsMatrix& matrix) override;
	XsMatrix alignmentRotationMatrix(XsAlignmentFrame frame) const override;
	bool setAlignmentRotationQuaternion(XsAlignmentFrame frame, const XsQuaternion& quat) override;
	XsQuaternion alignmentRotationQuaternion(XsAlignmentFrame frame) const override;

	bool setHeadingOffset(double offset);

	XsSyncSettingArray syncSettings() const override;
	bool setSyncSettings(const XsSyncSettingArray &s) override;

	bool setNoRotation(uint16_t duration);

	bool setInitialPositionLLA(const XsVector& lla);
	XsTimeInfo utcTime() const;
	bool setUtcTime(const XsTimeInfo& time);

	XsErrorMode errorMode() const;
	bool setErrorMode(XsErrorMode errorMode);
	uint16_t rs485TransmissionDelay() const;
	bool setRs485TransmissionDelay(uint16_t delay);

	bool messageLooksSane(const XsMessage &msg) const override;

	bool startRepresentativeMotion() override;
	bool representativeMotionState() override;
	XsIccRepMotionResult stopRepresentativeMotion() override;
	bool storeIccResults() override;

	//! A struct for base frequency result
	struct BaseFrequencyResult
	{
		int m_frequency; //!< A frequency value
		bool m_divedable; //!< A divedable value
	};
protected:
	virtual int calculateUpdateRate(XsDataIdentifier dataType) const;

	virtual int calculateUpdateRateImp(XsDataIdentifier dataType, const XsOutputConfigurationArray& configurations) const;

	virtual const char* assemblyType() const;
	virtual XsString hardwareType() const;
	virtual XsSyncLine syncSettingsLine(const uint8_t* buff, XsSize offset) const;
	virtual uint8_t syncLine(const XsSyncSetting& setting) const;

	bool resetRemovesPort() const override;

	/*! \brief An internal function that gets the base frequency
		\param dataType The Data identifier to use
		\returns The base frequency result
	*/
	virtual BaseFrequencyResult getBaseFrequencyInternal(XsDataIdentifier dataType = XDI_None) const { (void) dataType; return BaseFrequencyResult(); };

	virtual bool hasIccSupport() const;
	virtual bool deviceUsesOnBoardFiltering();

	bool supportsLegacyOutput() const override { return !deviceId().isMtMark5(); }

	//! Boolean variable for enabling/disabling of the representative motion
	bool m_representativeMotion;

	//! Constant value for filter frequency
	static const int m_filterFrequency = 100;
};

#ifndef XDA_PRIVATE_BUILD
/*! \class MtiBaseDeviceEx
	\brief The internal base class for MTi devices
*/
struct MtiBaseDeviceEx : public MtiBaseDevice
{
	//! \copybrief MtiBaseDevice::MtiBaseDevice
	explicit MtiBaseDeviceEx(Communicator* comm, MtHardwareParams* hwParams = 0) : MtiBaseDevice(comm) { (void) hwParams; };

	//! \copybrief MtiBaseDevice::MtiBaseDevice
	explicit MtiBaseDeviceEx(MtContainer *master, MtHardwareParams* hwParams = 0) : MtiBaseDevice(master) { (void) hwParams; };
};
#else
#include "mtibasedeviceex.h"
#endif

#endif
