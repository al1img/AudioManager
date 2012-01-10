/**
* Copyright (C) 2011, BMW AG
*
* GeniviAudioMananger DbusPlugin
*
* \file CommandSender.h
*
* \date 20-Oct-2011 3:42:04 PM
* \author Christian Mueller (christian.ei.mueller@bmw.de)
*
* \section License
* GNU Lesser General Public License, version 2.1, with special exception (GENIVI clause)
* Copyright (C) 2011, BMW AG Christian Mueller  Christian.ei.mueller@bmw.de
*
* This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License, version 2.1, as published by the Free Software Foundation.
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License, version 2.1, for more details.
* You should have received a copy of the GNU Lesser General Public License, version 2.1, along with this program; if not, see <http://www.gnu.org/licenses/lgpl-2.1.html>.
* Note that the copyright holders assume that the GNU Lesser General Public License, version 2.1, may also be applicable to programs even in cases in which the program is not a library in the technical sense.
* Linking AudioManager statically or dynamically with other modules is making a combined work based on AudioManager. You may license such other modules under the GNU Lesser General Public License, version 2.1. If you do not want to license your linked modules under the GNU Lesser General Public License, version 2.1, you may use the program under the following exception.
* As a special exception, the copyright holders of AudioManager give you permission to combine AudioManager with software programs or libraries that are released under any license unless such a combination is not permitted by the license of such a software program or library. You may copy and distribute such a system following the terms of the GNU Lesser General Public License, version 2.1, including this special exception, for AudioManager and the licenses of the other code concerned.
* Note that people who make modified versions of AudioManager are not obligated to grant this special exception for their modified versions; it is their choice whether to do so. The GNU Lesser General Public License, version 2.1, gives permission to release a modified version without this exception; this exception also makes it possible to release a modified version which carries forward this exception.
*
* THIS CODE HAS BEEN GENERATED BY ENTERPRISE ARCHITECT GENIVI MODEL. PLEASE CHANGE ONLY IN ENTERPRISE ARCHITECT AND GENERATE AGAIN
*/


#ifndef DBUSCOMMANDSENDER_H_
#define DBUSCOMMANDSENDER_H_

#ifdef UNIT_TEST
#include  "../test/DbusCommandInterfaceBackdoor.h"
#endif

#include <command/CommandSendInterface.h>
#include <dbus/dbus.h>
#include <dbus/DBusWrapper.h>
#include <map>
#include "DBusMessageHandler.h"
#include "CommandReceiverShadow.h"

namespace am {

const char MY_NODE[]="CommandInterface";

/**
 * Dbus Implementation of CommandSendInterface
 */
class DbusCommandSender: public CommandSendInterface {
public:
	DbusCommandSender();
	virtual ~DbusCommandSender();
	am_Error_e startupInterface(CommandReceiveInterface* commandreceiveinterface) ;
	am_Error_e stopInterface() ;
	am_Error_e cbCommunicationReady() ;
	am_Error_e cbCommunicationRundown() ;
	void cbNumberOfMainConnectionsChanged() ;
	void cbNumberOfSinksChanged() ;
	void cbNumberOfSourcesChanged() ;
	void cbNumberOfSinkClassesChanged() ;
	void cbNumberOfSourceClassesChanged() ;
	void cbMainConnectionStateChanged(const am_mainConnectionID_t connectionID, const am_ConnectionState_e connectionState) ;
	void cbMainSinkSoundPropertyChanged(const am_sinkID_t sinkID, const am_MainSoundProperty_s SoundProperty) ;
	void cbMainSourceSoundPropertyChanged(const am_sourceID_t sourceID, const am_MainSoundProperty_s& SoundProperty) ;
	void cbSinkAvailabilityChanged(const am_sinkID_t sinkID, const am_Availability_s& availability) ;
	void cbSourceAvailabilityChanged(const am_sourceID_t sourceID, const am_Availability_s& availability) ;
	void cbVolumeChanged(const am_sinkID_t sinkID, const am_mainVolume_t volume) ;
	void cbSinkMuteStateChanged(const am_sinkID_t sinkID, const am_MuteState_e muteState) ;
	void cbSystemPropertyChanged(const am_SystemProperty_s& SystemProperty) ;
	void cbTimingInformationChanged(const am_timeSync_t time, const am_mainConnectionID_t mainConnectionID) ;
	uint16_t getInterfaceVersion() const;

#ifdef UNIT_TEST
    friend class DbusCommandInterfaceBackdoor;
#endif
private:
	DBusMessageHandler mDBUSMessageHandler;
	CommandReceiverShadow mCommandReceiverShadow;
	DBusWrapper* mDBusWrapper;
	CommandReceiveInterface* mCommandReceiveInterface;

	/**
	 * list of sinks, needed to send out only deltas
	 */
	std::vector<am_SinkType_s> mlistSinks;

	/**
	 * list of sources, needed to send out only deltas
	 */
	std::vector<am_SourceType_s> mlistSources;

	/**
	 * used as comparison function for am_SinkType_s
	 */
	struct sortBySinkID
	{
		bool operator()(const am_SinkType_s & a, const am_SinkType_s & b)
		{
			return (a.sinkID < b.sinkID);
		}
	};

	/**
	 * used as comparison function for am_SourceType_s
	 */
	struct sortBySourceID
	{
		bool operator()(const am_SourceType_s & a, const am_SourceType_s & b)
		{
			return (a.sourceID < b.sourceID);
		}
	};

};

}

#endif /* DBUSCOMMANDSENDER_H_ */
