#include "stdafx.h"
#include "CXsensWraper.h"

std::ostream& operator << (std::ostream& out, XsPortInfo const & p)
{
	out << "Port: " << std::setw(2) << std::right << p.portNumber() << " (" << p.portName().toStdString() << ") @ "
		<< std::setw(7) << p.baudrate() << " Bd"
		<< ", " << "ID: " << p.deviceId().toString().toStdString()
		;
	return out;
}

std::ostream& operator << (std::ostream& out, XsDevice const & d)
{
	out << "ID: " << d.deviceId().toString().toStdString() << " (" << d.productCode().toStdString() << ")";
	return out;
}

int findClosestUpdateRate(const XsIntArray& supportedUpdateRates, const int desiredUpdateRate)
{
	if (supportedUpdateRates.empty())
	{
		return 0;
	}

	if (supportedUpdateRates.size() == 1)
	{
		return supportedUpdateRates[0];
	}

	int uRateDist = -1;
	int closestUpdateRate = -1;
	for (XsIntArray::const_iterator itUpRate = supportedUpdateRates.begin(); itUpRate != supportedUpdateRates.end(); ++itUpRate)
	{
		const int currDist = std::abs(*itUpRate - desiredUpdateRate);

		if ((uRateDist == -1) || (currDist < uRateDist))
		{
			uRateDist = currDist;
			closestUpdateRate = *itUpRate;
		}
	}
	return closestUpdateRate;
}

class WirelessMasterCallback : public XsCallback
{
public:
	typedef std::set<XsDevice*> XsDeviceSet;

	XsDeviceSet getWirelessMTWs() const
	{
		XsMutexLocker lock(m_mutex);
		return m_connectedMTWs;
	}

protected:
	virtual void onConnectivityChanged(XsDevice* dev, XsConnectivityState newState)
	{
		XsMutexLocker lock(m_mutex);
		switch (newState)
		{
		case XCS_Disconnected:		/*!< Device has disconnected, only limited informational functionality is available. */
			std::cout << "\nEVENT: MTW Disconnected -> " << *dev << std::endl;
			m_connectedMTWs.erase(dev);
			break;
		case XCS_Rejected:			/*!< Device has been rejected and is disconnected, only limited informational functionality is available. */
			std::cout << "\nEVENT: MTW Rejected -> " << *dev << std::endl;
			m_connectedMTWs.erase(dev);
			break;
		case XCS_PluggedIn:			/*!< Device is connected through a cable. */
			std::cout << "\nEVENT: MTW PluggedIn -> " << *dev << std::endl;
			m_connectedMTWs.erase(dev);
			break;
		case XCS_Wireless:			/*!< Device is connected wirelessly. */
			std::cout << "\nEVENT: MTW Connected -> " << *dev << std::endl;
			m_connectedMTWs.insert(dev);
			break;
		case XCS_File:				/*!< Device is reading from a file. */
			std::cout << "\nEVENT: MTW File -> " << *dev << std::endl;
			m_connectedMTWs.erase(dev);
			break;
		case XCS_Unknown:			/*!< Device is in an unknown state. */
			std::cout << "\nEVENT: MTW Unknown -> " << *dev << std::endl;
			m_connectedMTWs.erase(dev);
			break;
		default:
			std::cout << "\nEVENT: MTW Error -> " << *dev << std::endl;
			m_connectedMTWs.erase(dev);
			break;
		}
	}
private:
	mutable XsMutex m_mutex;
	XsDeviceSet m_connectedMTWs;
};

class MtwCallback : public XsCallback
{
public:
	MtwCallback(int mtwIndex, XsDevice* device)
		:m_mtwIndex(mtwIndex)
		, m_device(device)
	{}

	bool dataAvailable() const
	{
		XsMutexLocker lock(m_mutex);
		return !m_packetBuffer.empty();
	}

	XsDataPacket const * getOldestPacket() const
	{
		XsMutexLocker lock(m_mutex);
		XsDataPacket const * packet = &m_packetBuffer.front();
		return packet;
	}

	void deleteOldestPacket()
	{
		XsMutexLocker lock(m_mutex);
		m_packetBuffer.pop_front();
	}

	int getMtwIndex() const
	{
		return m_mtwIndex;
	}

	XsDevice const & device() const
	{
		assert(m_device != 0);
		return *m_device;
	}

protected:
	virtual void onLiveDataAvailable(XsDevice*, const XsDataPacket* packet)
	{
		XsMutexLocker lock(m_mutex);
		// NOTE: Processing of packets should not be done in this thread.

		m_packetBuffer.push_back(*packet);
		if (m_packetBuffer.size() > 300)
		{
			std::cout << std::endl;
			deleteOldestPacket();
		}
	}

private:
	mutable XsMutex m_mutex;
	std::list<XsDataPacket> m_packetBuffer;
	int m_mtwIndex;
	XsDevice* m_device;
};


CXsensWraper::CXsensWraper() {
	initialCheck = false;
	totalDevice  = 0;
	for (int j = 0; j < MAXDEVICE; j++) {
		deviceAry[j] = "00000000";
		angleData_0[j] = Vec3f(0, 0, 0);
	}
}


CXsensWraper::~CXsensWraper() {}

void CXsensWraper::setDeviceID(char *_deviceID, int idx)
{
	deviceAry[idx] = _deviceID;
	totalDevice = totalDevice + 1;
}


WirelessMasterCallback wirelessMasterCallback;
std::vector<MtwCallback*> mtwCallbacks;
std::vector<XsEuler> eulerData;
std::vector<XsVector> gyroData;
std::vector<XsVector> accelData;
std::vector<XsVector> angularData;

void CXsensWraper::setXsens()
{
	const int desiredUpdateRate = 100;   // Use 75 Hz update rate for MTWs
	const int desiredRadioChannel = 19;   // Use radio channel 19 for wireless master.

	XsControl* control = XsControl::construct();
	if (control == 0)
	{
		std::cout << "Failed to construct XsControl instance." << std::endl;
	}
	XsPortInfoArray detectedDevices = XsScanner::scanPorts();
	XsPortInfoArray::const_iterator wirelessMasterPort = detectedDevices.begin();
	while (wirelessMasterPort != detectedDevices.end() && !wirelessMasterPort->deviceId().isWirelessMaster())
	{
		++wirelessMasterPort;
	}
	if (wirelessMasterPort == detectedDevices.end())
	{
		throw std::runtime_error("No wireless masters found");
	}
	if (!control->openPort(wirelessMasterPort->portName().toStdString(), wirelessMasterPort->baudrate()))
	{
		std::ostringstream error;
		error << "Failed to open port " << *wirelessMasterPort;
		throw std::runtime_error(error.str());
	}
	XsDevicePtr wirelessMasterDevice = control->device(wirelessMasterPort->deviceId());
	if (!wirelessMasterDevice->gotoConfig())
	{
		std::ostringstream error;
		error << "Failed to goto config mode: " << *wirelessMasterDevice;
		throw std::runtime_error(error.str());
	}
	wirelessMasterDevice->addCallbackHandler(&wirelessMasterCallback);
	const XsIntArray supportedUpdateRates = wirelessMasterDevice->supportedUpdateRates();
	for (XsIntArray::const_iterator itUpRate = supportedUpdateRates.begin(); itUpRate != supportedUpdateRates.end(); ++itUpRate)
	{
		//std::cout << *itUpRate << " ";
	}
	const int newUpdateRate = findClosestUpdateRate(supportedUpdateRates, desiredUpdateRate);
	if (!wirelessMasterDevice->setUpdateRate(newUpdateRate))
	{
		std::ostringstream error;
		error << "Failed to set update rate: " << *wirelessMasterDevice;
		throw std::runtime_error(error.str());
	}
	if (wirelessMasterDevice->isRadioEnabled())
	{
		if (!wirelessMasterDevice->disableRadio())
		{
			std::ostringstream error;
			error << "Failed to disable radio channel: " << *wirelessMasterDevice;
			throw std::runtime_error(error.str());
		}
	}
	if (!wirelessMasterDevice->enableRadio(desiredRadioChannel))
	{
		std::ostringstream error;
		error << "Failed to set radio channel: " << *wirelessMasterDevice;
		throw std::runtime_error(error.str());
	}

	bool waitForConnections = true;
	size_t connectedMTWCount = wirelessMasterCallback.getWirelessMTWs().size();
	do
	{
		XsTime::msleep(100);

		while (true)
		{
			size_t nextCount = wirelessMasterCallback.getWirelessMTWs().size();
			if (nextCount != connectedMTWCount)
			{
				std::cout << "  - Number of connected MTWs: " << nextCount << std::endl;
				connectedMTWCount = nextCount;
				if (nextCount >= totalDevice) {
					waitForConnections = !waitForConnections;
				}
			}
			else
			{
				break;
			}
			std::cout << "" << std::endl;
			std::cout << "MTW Connecting... (" << nextCount << "/" << totalDevice << ")" << std::endl;
		}

	} while (waitForConnections);   // Å½»öµÈ device ÇÒ´ç
	std::cout << "\nMTW All Devices Connected" << std::endl;

	if (!wirelessMasterDevice->gotoMeasurement())
	{
		std::ostringstream error;
		error << "Failed to goto measurement mode: " << *wirelessMasterDevice;
		throw std::runtime_error(error.str());
	}
	XsDeviceIdArray allDeviceIds = control->deviceIds();
	XsDeviceIdArray mtwDeviceIds;

	for (XsDeviceIdArray::const_iterator i = allDeviceIds.begin(); i != allDeviceIds.end(); ++i)
	{
		if (i->isMtw())
		{
			mtwDeviceIds.push_back(*i);
		}
	}
	XsDevicePtrArray mtwDevices;
	for (XsDeviceIdArray::const_iterator i = mtwDeviceIds.begin(); i != mtwDeviceIds.end(); ++i)
	{
		XsDevicePtr mtwDevice = control->device(*i);
		if (mtwDevice != 0)
		{
			mtwDevices.push_back(mtwDevice);
		}
		else
		{
			throw std::runtime_error("Failed to create an MTW XsDevice instance");
		}
	}
	mtwCallbacks.resize(mtwDevices.size());
	for (int i = 0; i < (int)mtwDevices.size(); ++i)
	{
		mtwCallbacks[i] = new MtwCallback(i, mtwDevices[i]);
		mtwDevices[i]->addCallbackHandler(mtwCallbacks[i]);
	}
	eulerData.resize(mtwCallbacks.size());
	gyroData.resize(mtwCallbacks.size());
	accelData.resize(mtwCallbacks.size());
	angularData.resize(mtwCallbacks.size());
	std::cout << "MTW Checking DeviceID...";

	for (int i = 0; i < (int)mtwCallbacks.size(); i++)
	{
		std::cout << "\n mtwCallbacks ID : " << mtwCallbacks[i]->device().deviceId().toString().toStdString();

		for (int j = 0; j < totalDevice; j++)
		{
			std::cout << "\n  - now checking..." << deviceAry[j];
			if (mtwCallbacks[i]->device().deviceId().toString().toStdString().compare(deviceAry[j]) == 0)
			{
				deviceNum[j] = i;
				std::cout << " -> Device" << j << " Checked!";
			}
		}
	}

	std::cout << "\n\nMTW Setting Complete\n-----------------------------------------------------" << std::endl;
	std::cout << " [Q] = Initial Setting\n [W] = Start Recording\n [E] = Stop Recording\n [R] = Start Simulation\n [T] = Stop Simulation" << std::endl;

}

void CXsensWraper::runXsens()
{
	bool newDataAvailable = false;
	for (size_t i = 0; i < mtwCallbacks.size(); ++i)
	{
		if (mtwCallbacks[i]->dataAvailable())
		{
			newDataAvailable = true;
			XsDataPacket const * packet = mtwCallbacks[i]->getOldestPacket();
			XsVector xsvector;
			eulerData[i] = packet->orientationEuler();
			gyroData[i] = packet->calibratedGyroscopeData();
			accelData[i] = packet->freeAcceleration();
			angularData[i] = xsvector.angularVelocityFromQuaternion(packet->orientationQuaternion(), 1 / 100);
			mtwCallbacks[i]->deleteOldestPacket();

		}
	}

	if (newDataAvailable)
	{	
		if (initialCheck) {
			std::cout << "! Initial Value Setting" << std::endl;
			for (int j = 0; j < totalDevice; j++) {
				angleData_0[j][0] = eulerData[deviceNum[j]].roll();
				angleData_0[j][1] = eulerData[deviceNum[j]].pitch();
				angleData_0[j][2] = eulerData[deviceNum[j]].yaw();
			}
			//std::cout << " - Yaw Values : " << initialYaw[0] << ", " << initialYaw[1] << ", " << initialYaw[2] << std::endl;
			initialCheck = !initialCheck;
		}
		for (int j = 0; j < totalDevice; j++)
		{
			angleData[j] = Vec3f(eulerData[deviceNum[j]].roll()-angleData_0[j][0], eulerData[deviceNum[j]].pitch()- angleData_0[j][1], eulerData[deviceNum[j]].yaw() - angleData_0[j][2]);
			jh_angleData[j] = Vec3f(eulerData[deviceNum[j]].roll(), eulerData[deviceNum[j]].pitch(), eulerData[deviceNum[j]].yaw());
			avelData[j]  = Vec3f(gyroData[deviceNum[j]][0], gyroData[deviceNum[j]][1], gyroData[deviceNum[j]][2]);
			accData[j]   = Vec3f(accelData[deviceNum[j]][0], accelData[deviceNum[j]][1], accelData[deviceNum[j]][2]);
			angVelData[j] = Vec3f(angularData[deviceNum[j]][0], angularData[deviceNum[j]][1], angularData[deviceNum[j]][2]);
		}
	}
}



Vec3f CXsensWraper::getAngle(int idx)
{
	return angleData[idx];
}

Vec3f CXsensWraper::getjhAngle(int idx)
{
	return jh_angleData[idx];

}

Vec3f CXsensWraper::getGyro(int idx)
{
	return avelData[idx];
}

Vec3f CXsensWraper::getAcc(int idx)
{
	return accData[idx];
}

Vec3f CXsensWraper::getAng(int idx)
{
	return angVelData[idx];
}

void CXsensWraper::setInitialYaw()
{
	if (!initialCheck) {
		initialCheck = !initialCheck;
	}
}
