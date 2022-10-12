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

#ifndef SIMPLEPROTOCOLMANAGER_H
#define SIMPLEPROTOCOLMANAGER_H

#include "iprotocolmanager.h"
#include "protocolhandler.h"

/*! \brief A very basic protocol manager
	\details This protocol manager supports only the xbus protocol
*/
class SimpleProtocolManager : public IProtocolManager
{
public:
	/*! \copydoc IProtocolManager::findMessage
	*/
	MessageLocation findMessage(XsMessage& rcv, const XsByteArray& raw) override
	{
		return m_protocolHandler.findMessage(rcv, raw);
	}

	/*! \copydoc IProtocolManager::validateMessage
	*/
	bool validateMessage(XsMessage const& msg) const override
	{
		return msg.isChecksumOk();
	}
private:
	ProtocolHandler m_protocolHandler; //!< Standard protocol handler; used for finding messages.
};

#endif
