/**
 * Copyright (C) 2011, BMW AG
 *
 * GeniviAudioMananger DbusPlugin
 *
 * \file CommandSender.cpp
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

#include <command/CommandReceiveInterface.h>
#include <dbus/DBusWrapper.h>
#include "DBusCommandSender.h"
#include "DBusMessageHandler.h"
#include <dlt/dlt.h>
#include <algorithm>
#include <string>
#include <vector>
#include <assert.h>
#include <set>

using namespace am;

DLT_DECLARE_CONTEXT(DLT_CONTEXT)

/**
 * factory for plugin loading
 */
extern "C" CommandSendInterface* PluginCommandInterfaceDbusFactory()
{
    return (new DbusCommandSender());
}

/**
 * destroy instance of commandSendInterface
 */
extern "C" void destroyRoutingPluginInterfaceDbus(CommandSendInterface* commandSendInterface)
{
    delete commandSendInterface;
}

DbusCommandSender::DbusCommandSender() :
        mDBUSMessageHandler(), //
        mCommandReceiverShadow(), //
        mDBusWrapper(NULL), //
        mCommandReceiveInterface(NULL)
{
    DLT_REGISTER_CONTEXT(DLT_CONTEXT, "DBP", "DBus Plugin");
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("DbusCommandSender constructed"));
}

DbusCommandSender::~DbusCommandSender()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("DbusCommandSender destructed"));
    DLT_UNREGISTER_CONTEXT(DLT_CONTEXT);
}

am_Error_e DbusCommandSender::startupInterface(CommandReceiveInterface* commandreceiveinterface)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("startupInterface called"));

    mCommandReceiveInterface = commandreceiveinterface;
    mCommandReceiverShadow.setCommandReceiver(mCommandReceiveInterface);
    mCommandReceiveInterface->getDBusConnectionWrapper(mDBusWrapper);
    assert(mDBusWrapper!=NULL);
    return (E_OK);
}

am_Error_e DbusCommandSender::stopInterface()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("stopInterface called"));
    /**
     * todo: finish DbusCommandSender::stopInterface(), what needs to be done?
     */
    return (E_OK);
}

am_Error_e DbusCommandSender::cbCommunicationReady()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbCommunicationReady called"));
    /**
     * todo: implement DbusCommandSender::cbCommunicationReady()
     */
    return E_NOT_USED;
}

am_Error_e DbusCommandSender::cbCommunicationRundown()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbCommunicationRundown called"));
    /**
     * todo: implement DbusCommandSender::cbCommunicationRundown()
     */
    return E_NOT_USED;
}

void DbusCommandSender::cbNumberOfMainConnectionsChanged()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbNumberOfMainConnectionsChanged called"));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("NumberOfMainConnectionsChanged"));
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbNumberOfSinksChanged()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbNumberOfSinksChanged called"));

    std::vector<am_SinkType_s> newListSinks;
    std::vector<am_SinkType_s> diffList;
    mCommandReceiveInterface->getListMainSinks(newListSinks);
    std::sort(newListSinks.begin(), newListSinks.end(), sortBySinkID());
    std::set_symmetric_difference(newListSinks.begin(), newListSinks.end(), mlistSinks.begin(), mlistSinks.end(), std::back_inserter(diffList), sortBySinkID());
    assert(diffList.size()==1);
    if (newListSinks.size() > mlistSinks.size())
    {
        mDBUSMessageHandler.initSignal(std::string(MY_NODE), "SinkAdded");
        mDBUSMessageHandler.append(diffList[0]);

        DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("send signal SinkAdded"));
    }
    else
    {
        mDBUSMessageHandler.initSignal(std::string(MY_NODE), "SinkRemoved");
        mDBUSMessageHandler.append(diffList.begin()->sinkID);

        DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("send signal SinkRemoved"));
    }

    mDBUSMessageHandler.sendMessage();
    mlistSinks = newListSinks;
}

void DbusCommandSender::cbNumberOfSourcesChanged()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbNumberOfSourcesChanged called"));

    std::vector<am_SourceType_s> newlistSources;
    std::vector<am_SourceType_s> diffList;
    mCommandReceiveInterface->getListMainSources(newlistSources);
    std::sort(newlistSources.begin(), newlistSources.end(), sortBySourceID());
    std::set_symmetric_difference(newlistSources.begin(), newlistSources.end(), mlistSources.begin(), mlistSources.end(), std::back_inserter(diffList), sortBySourceID());
    assert(diffList.size()==1);
    if (newlistSources.size() > mlistSources.size())
    {
        mDBUSMessageHandler.initSignal(std::string(MY_NODE), "SourceAdded");
        mDBUSMessageHandler.append(diffList[0]);

        DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("send signal SourceAdded"));
    }
    else
    {
        mDBUSMessageHandler.initSignal(std::string(MY_NODE), "SourceRemoved");
        mDBUSMessageHandler.append((dbus_uint16_t) diffList.begin()->sourceID);

        DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("send signal SourceRemoved"));
    }

    mDBUSMessageHandler.sendMessage();
    mlistSources = newlistSources;
}

void DbusCommandSender::cbNumberOfSinkClassesChanged()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbNumberOfSinkClassesChanged called"));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("NumberOfSinkClassesChanged"));
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbNumberOfSourceClassesChanged()
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbNumberOfSourceClassesChanged called"));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("NumberOfSourceClassesChanged"));
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbMainConnectionStateChanged(const am_mainConnectionID_t connectionID, const am_ConnectionState_e connectionState)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbMainConnectionStateChanged called, connectionID"), DLT_INT16(connectionID), DLT_STRING("connectionState"), DLT_INT16(connectionState));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("MainConnectionStateChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) connectionID);
    mDBUSMessageHandler.append((dbus_int16_t) connectionState);
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbMainSinkSoundPropertyChanged(const am_sinkID_t sinkID, const am_MainSoundProperty_s SoundProperty)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbMainSinkSoundPropertyChanged called, sinkID"), DLT_INT16(sinkID), DLT_STRING("SoundProperty.type"), DLT_INT16(SoundProperty.type), DLT_STRING("SoundProperty.value"), DLT_INT16(SoundProperty.value));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("MainSinkSoundPropertyChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) sinkID);
    mDBUSMessageHandler.append(SoundProperty);
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbMainSourceSoundPropertyChanged(const am_sourceID_t sourceID, const am_MainSoundProperty_s & SoundProperty)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbMainSourceSoundPropertyChanged called, sourceID"), DLT_INT16(sourceID), DLT_STRING("SoundProperty.type"), DLT_INT16(SoundProperty.type), DLT_STRING("SoundProperty.value"), DLT_INT16(SoundProperty.value));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("MainSourceSoundPropertyChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) sourceID);
    mDBUSMessageHandler.append(SoundProperty);
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbSinkAvailabilityChanged(const am_sinkID_t sinkID, const am_Availability_s & availability)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbSinkAvailabilityChanged called, sinkID"), DLT_INT16(sinkID), DLT_STRING("availability.availability"), DLT_INT16(availability.availability), DLT_STRING("SoundProperty.reason"), DLT_INT16(availability.availabilityReason));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("SinkAvailabilityChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) sinkID);
    mDBUSMessageHandler.append(availability);
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbSourceAvailabilityChanged(const am_sourceID_t sourceID, const am_Availability_s & availability)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbSourceAvailabilityChanged called, sourceID"), DLT_INT16(sourceID), DLT_STRING("availability.availability"), DLT_INT16(availability.availability), DLT_STRING("SoundProperty.reason"), DLT_INT16(availability.availabilityReason));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("SourceAvailabilityChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) sourceID);
    mDBUSMessageHandler.append(availability);
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbVolumeChanged(const am_sinkID_t sinkID, const am_mainVolume_t volume)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbVolumeChanged called, sinkID"), DLT_INT16(sinkID), DLT_STRING("volume"), DLT_INT16(volume));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("VolumeChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) sinkID);
    mDBUSMessageHandler.append((dbus_int16_t) volume);
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbSinkMuteStateChanged(const am_sinkID_t sinkID, const am_MuteState_e muteState)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbSinkMuteStateChanged called, sinkID"), DLT_INT16(sinkID), DLT_STRING("muteState"), DLT_INT16(muteState));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("SinkMuteStateChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) sinkID);
    mDBUSMessageHandler.append((dbus_int16_t) muteState);
    mDBUSMessageHandler.sendMessage();
}

void DbusCommandSender::cbSystemPropertyChanged(const am_SystemProperty_s & SystemProperty)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbSystemPropertyChanged called, SystemProperty.type"), DLT_INT16(SystemProperty.type), DLT_STRING("SystemProperty.value"), DLT_INT16(SystemProperty.value));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("SystemPropertyChanged"));
    mDBUSMessageHandler.append(SystemProperty);
    mDBUSMessageHandler.sendMessage();
}

void am::DbusCommandSender::cbTimingInformationChanged(const am_mainConnectionID_t mainConnectionID, const am_timeSync_t time)
{
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("cbTimingInformationChanged called, mainConnectionID"), DLT_INT16(mainConnectionID), DLT_STRING("time"), DLT_INT16(time));

    mDBUSMessageHandler.initSignal(std::string(MY_NODE), std::string("TimingInformationChanged"));
    mDBUSMessageHandler.append((dbus_uint16_t) mainConnectionID);
    mDBUSMessageHandler.append((dbus_int16_t) time);
    mDBUSMessageHandler.sendMessage();
}

uint16_t DbusCommandSender::getInterfaceVersion() const
{
    return (CommandSendVersion);
}

