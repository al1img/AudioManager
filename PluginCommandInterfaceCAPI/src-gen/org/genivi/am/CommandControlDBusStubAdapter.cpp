/*
* This file was generated by the CommonAPI Generators.
*
* This file was generated by the CommonAPI Generators.
*
* This file was generated by the CommonAPI Generators.
*
* Copyright (C) 2012, BMW AG
*
* This file is part of GENIVI Project AudioManager.
*
* Contributions are licensed to the GENIVI Alliance under one or more
* Contribution License Agreements.
*
* \copyright
* This Source Code Form is subject to the terms of the
* Mozilla Public License, v. 2.0. If a  copy of the MPL was not distributed with
* this file, You can obtain one at http://mozilla.org/MPL/2.0/.
*
*
* \author Aleksandar Donchev, aleksander.donchev@partner.bmw.de BMW 2013
* \author Christian Linke christian.linke@bmw.de BMW 2013
*
* For further information see http://www.genivi.org/.
*/
#include "CommandControlDBusStubAdapter.h"
#include <org/genivi/am/CommandControl.h>

namespace org {
namespace genivi {
namespace am {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createCommandControlDBusStubAdapter(
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<CommandControlDBusStubAdapter>(commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerCommandControlDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(CommandControl::getInterfaceId(),
                                                               &createCommandControlDBusStubAdapter);
}

CommandControlDBusStubAdapter::CommandControlDBusStubAdapter(
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        CommandControlDBusStubAdapterHelper(commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, dbusConnection, std::dynamic_pointer_cast<CommandControlStub>(stub)) {
}

const char* CommandControlDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
    return
        "<signal name=\"newMainConnection\">\n"
            "<arg name=\"mainConnection\" type=\"(qqqni)\" />\n"
        "</signal>\n"
        "<signal name=\"removedMainConnection\">\n"
            "<arg name=\"mainConnection\" type=\"q\" />\n"
        "</signal>\n"
        "<signal name=\"newSink\">\n"
            "<arg name=\"sink\" type=\"(qs(iq)niq)\" />\n"
        "</signal>\n"
        "<signal name=\"removedSink\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
        "</signal>\n"
        "<signal name=\"newSource\">\n"
            "<arg name=\"source\" type=\"(qs(iq)q)\" />\n"
        "</signal>\n"
        "<signal name=\"removedSource\">\n"
            "<arg name=\"source\" type=\"q\" />\n"
        "</signal>\n"
        "<signal name=\"numberOfSinkClassesChanged\">\n"
        "</signal>\n"
        "<signal name=\"numberOfSourceClassesChanged\">\n"
        "</signal>\n"
        "<signal name=\"mainConnectionStateChanged\">\n"
            "<arg name=\"connectionID\" type=\"q\" />\n"
            "<arg name=\"connectionState\" type=\"i\" />\n"
        "</signal>\n"
        "<signal name=\"mainSinkSoundPropertyChanged\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
            "<arg name=\"soundProperty\" type=\"(qn)\" />\n"
        "</signal>\n"
        "<signal name=\"mainSourceSoundPropertyChanged\">\n"
            "<arg name=\"sourceID\" type=\"q\" />\n"
            "<arg name=\"soundProperty\" type=\"(qn)\" />\n"
        "</signal>\n"
        "<signal name=\"sinkAvailabilityChanged\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
            "<arg name=\"availability\" type=\"(iq)\" />\n"
        "</signal>\n"
        "<signal name=\"sourceAvailabilityChanged\">\n"
            "<arg name=\"sourceID\" type=\"q\" />\n"
            "<arg name=\"availability\" type=\"(iq)\" />\n"
        "</signal>\n"
        "<signal name=\"volumeChanged\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
            "<arg name=\"volume\" type=\"n\" />\n"
        "</signal>\n"
        "<signal name=\"sinkMuteStateChanged\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
            "<arg name=\"muteState\" type=\"i\" />\n"
        "</signal>\n"
        "<signal name=\"systemPropertyChanged\">\n"
            "<arg name=\"systemProperty\" type=\"(qn)\" />\n"
        "</signal>\n"
        "<signal name=\"timingInformationChanged\">\n"
            "<arg name=\"mainConnectionID\" type=\"q\" />\n"
            "<arg name=\"time\" type=\"n\" />\n"
        "</signal>\n"
        "<signal name=\"sinkUpdated\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
            "<arg name=\"sinkClassID\" type=\"q\" />\n"
            "<arg name=\"listMainSoundProperties\" type=\"a(qn)\" />\n"
        "</signal>\n"
        "<signal name=\"sourceUpdated\">\n"
            "<arg name=\"sourceID\" type=\"q\" />\n"
            "<arg name=\"sourceClassID\" type=\"q\" />\n"
            "<arg name=\"listMainSoundProperties\" type=\"a(qn)\" />\n"
        "</signal>\n"
        "<signal name=\"sinkNotification\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
            "<arg name=\"notification\" type=\"(qn)\" />\n"
        "</signal>\n"
        "<signal name=\"sourceNotification\">\n"
            "<arg name=\"sourceID\" type=\"q\" />\n"
            "<arg name=\"notification\" type=\"(qn)\" />\n"
        "</signal>\n"
        "<signal name=\"mainSinkNotificationConfigurationChanged\">\n"
            "<arg name=\"sinkID\" type=\"q\" />\n"
            "<arg name=\"mainNotificationConfiguration\" type=\"(qin)\" />\n"
        "</signal>\n"
        "<signal name=\"mainSourceNotificationConfigurationChanged\">\n"
            "<arg name=\"sourceID\" type=\"q\" />\n"
            "<arg name=\"mainNotificationConfiguration\" type=\"(qin)\" />\n"
        "</signal>\n"
        "<method name=\"connect\">\n"
            "<arg name=\"sourceID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"mainConnectionID\" type=\"q\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"disconnect\">\n"
            "<arg name=\"mainConnectionID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"setVolume\">\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"volume\" type=\"n\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"volumeStep\">\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"volumeStep\" type=\"n\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"setSinkMuteState\">\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"muteState\" type=\"i\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"setMainSinkSoundProperty\">\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"soundProperty\" type=\"(qn)\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"setMainSourceSoundProperty\">\n"
            "<arg name=\"sourceID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"soundProperty\" type=\"(qn)\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"setSystemProperty\">\n"
            "<arg name=\"property\" type=\"(qn)\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListMainConnections\">\n"
            "<arg name=\"listConnections\" type=\"a(qqqni)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListMainSinks\">\n"
            "<arg name=\"listMainSinks\" type=\"a(qs(iq)niq)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListMainSources\">\n"
            "<arg name=\"listMainSources\" type=\"a(qs(iq)q)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListMainSinkSoundProperties\">\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"listSoundProperties\" type=\"a(qn)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListMainSourceSoundProperties\">\n"
            "<arg name=\"sourceID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"listSourceProperties\" type=\"a(qn)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListSourceClasses\">\n"
            "<arg name=\"listSourceClasses\" type=\"a(qsa(qn))\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListSinkClasses\">\n"
            "<arg name=\"listSinkClasses\" type=\"a(qsa(qn))\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListSystemProperties\">\n"
            "<arg name=\"listSystemProperties\" type=\"a(qn)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getTimingInformation\">\n"
            "<arg name=\"mainConnectionID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"delay\" type=\"n\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListMainSinkNotificationConfigurations\">\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"listMainNotificationConfigurations\" type=\"a(qin)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"getListMainSourceNotificationConfigurations\">\n"
            "<arg name=\"sourceID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"listMainNotificationConfigurations\" type=\"a(qin)\" direction=\"out\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"setMainSinkNotificationConfiguration\">\n"
            "<arg name=\"sinkID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"mainNotificationConfiguration\" type=\"(qin)\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
        "<method name=\"setMainSourceNotificationConfiguration\">\n"
            "<arg name=\"sourceID\" type=\"q\" direction=\"in\" />\n"
            "<arg name=\"mainNotificationConfiguration\" type=\"(qin)\" direction=\"in\" />\n"
            "<arg name=\"error\" type=\"i\" direction=\"out\" />\n"
        "</method>\n"
    ;
}



static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sourceID_t, am_sinkID_t>,
    std::tuple<am_mainConnectionID_t, am_Error_e>
    > connectStubDispatcher(&CommandControlStub::connect, "qi");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_mainConnectionID_t>,
    std::tuple<am_Error_e>
    > disconnectStubDispatcher(&CommandControlStub::disconnect, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sinkID_t, am_mainVolume_t>,
    std::tuple<am_Error_e>
    > setVolumeStubDispatcher(&CommandControlStub::setVolume, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sinkID_t, int16_t>,
    std::tuple<am_Error_e>
    > volumeStepStubDispatcher(&CommandControlStub::volumeStep, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sinkID_t, am_MuteState_e>,
    std::tuple<am_Error_e>
    > setSinkMuteStateStubDispatcher(&CommandControlStub::setSinkMuteState, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sinkID_t, am_MainSoundProperty_s>,
    std::tuple<am_Error_e>
    > setMainSinkSoundPropertyStubDispatcher(&CommandControlStub::setMainSinkSoundProperty, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sourceID_t, am_MainSoundProperty_s>,
    std::tuple<am_Error_e>
    > setMainSourceSoundPropertyStubDispatcher(&CommandControlStub::setMainSourceSoundProperty, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_SystemProperty_s>,
    std::tuple<am_Error_e>
    > setSystemPropertyStubDispatcher(&CommandControlStub::setSystemProperty, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<>,
    std::tuple<am_MainConnection_L, am_Error_e>
    > getListMainConnectionsStubDispatcher(&CommandControlStub::getListMainConnections, "a(qqqni)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<>,
    std::tuple<am_SinkType_L, am_Error_e>
    > getListMainSinksStubDispatcher(&CommandControlStub::getListMainSinks, "a(qs(iq)niq)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<>,
    std::tuple<am_SourceType_L, am_Error_e>
    > getListMainSourcesStubDispatcher(&CommandControlStub::getListMainSources, "a(qs(iq)q)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sinkID_t>,
    std::tuple<am_MainSoundProperty_L, am_Error_e>
    > getListMainSinkSoundPropertiesStubDispatcher(&CommandControlStub::getListMainSinkSoundProperties, "a(qn)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sourceID_t>,
    std::tuple<am_MainSoundProperty_L, am_Error_e>
    > getListMainSourceSoundPropertiesStubDispatcher(&CommandControlStub::getListMainSourceSoundProperties, "a(qn)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<>,
    std::tuple<am_SourceClass_L, am_Error_e>
    > getListSourceClassesStubDispatcher(&CommandControlStub::getListSourceClasses, "a(qsa(qn))i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<>,
    std::tuple<am_SinkClass_L, am_Error_e>
    > getListSinkClassesStubDispatcher(&CommandControlStub::getListSinkClasses, "a(qsa(qn))i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<>,
    std::tuple<am_SystemProperty_L, am_Error_e>
    > getListSystemPropertiesStubDispatcher(&CommandControlStub::getListSystemProperties, "a(qn)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_mainConnectionID_t>,
    std::tuple<am_timeSync_t, am_Error_e>
    > getTimingInformationStubDispatcher(&CommandControlStub::getTimingInformation, "ni");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sinkID_t>,
    std::tuple<am_NotificationConfiguration_L, am_Error_e>
    > getListMainSinkNotificationConfigurationsStubDispatcher(&CommandControlStub::getListMainSinkNotificationConfigurations, "a(qin)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sourceID_t>,
    std::tuple<am_NotificationConfiguration_L, am_Error_e>
    > getListMainSourceNotificationConfigurationsStubDispatcher(&CommandControlStub::getListMainSourceNotificationConfigurations, "a(qin)i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sinkID_t, am_NotificationConfiguration_s>,
    std::tuple<am_Error_e>
    > setMainSinkNotificationConfigurationStubDispatcher(&CommandControlStub::setMainSinkNotificationConfiguration, "i");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    CommandControlStub,
    std::tuple<am_sourceID_t, am_NotificationConfiguration_s>,
    std::tuple<am_Error_e>
    > setMainSourceNotificationConfigurationStubDispatcher(&CommandControlStub::setMainSourceNotificationConfiguration, "i");


void CommandControlDBusStubAdapter::fireNewMainConnectionEvent(const am_MainConnectionType_s& mainConnection) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_MainConnectionType_s>>
            ::sendSignal(
                *this,
                "newMainConnection",
                "(qqqni)",
                mainConnection
        );
}
void CommandControlDBusStubAdapter::fireRemovedMainConnectionEvent(const am_mainConnectionID_t& mainConnection) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_mainConnectionID_t>>
            ::sendSignal(
                *this,
                "removedMainConnection",
                "q",
                mainConnection
        );
}
void CommandControlDBusStubAdapter::fireNewSinkEvent(const am_SinkType_s& sink) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_SinkType_s>>
            ::sendSignal(
                *this,
                "newSink",
                "(qs(iq)niq)",
                sink
        );
}
void CommandControlDBusStubAdapter::fireRemovedSinkEvent(const am_sinkID_t& sinkID) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t>>
            ::sendSignal(
                *this,
                "removedSink",
                "q",
                sinkID
        );
}
void CommandControlDBusStubAdapter::fireNewSourceEvent(const am_SourceType_s& source) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_SourceType_s>>
            ::sendSignal(
                *this,
                "newSource",
                "(qs(iq)q)",
                source
        );
}
void CommandControlDBusStubAdapter::fireRemovedSourceEvent(const am_sourceID_t& source) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sourceID_t>>
            ::sendSignal(
                *this,
                "removedSource",
                "q",
                source
        );
}
void CommandControlDBusStubAdapter::fireNumberOfSinkClassesChangedEvent() {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<>>
            ::sendSignal(
                *this,
                "numberOfSinkClassesChanged",
                ""
        );
}
void CommandControlDBusStubAdapter::fireNumberOfSourceClassesChangedEvent() {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<>>
            ::sendSignal(
                *this,
                "numberOfSourceClassesChanged",
                ""
        );
}
void CommandControlDBusStubAdapter::fireMainConnectionStateChangedEvent(const am_mainConnectionID_t& connectionID, const am_ConnectionState_e& connectionState) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_mainConnectionID_t, am_ConnectionState_e>>
            ::sendSignal(
                *this,
                "mainConnectionStateChanged",
                "qi",
                connectionID, connectionState
        );
}
void CommandControlDBusStubAdapter::fireMainSinkSoundPropertyChangedEvent(const am_sinkID_t& sinkID, const am_MainSoundProperty_s& soundProperty) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t, am_MainSoundProperty_s>>
            ::sendSignal(
                *this,
                "mainSinkSoundPropertyChanged",
                "q(qn)",
                sinkID, soundProperty
        );
}
void CommandControlDBusStubAdapter::fireMainSourceSoundPropertyChangedEvent(const am_sourceID_t& sourceID, const am_MainSoundProperty_s& soundProperty) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sourceID_t, am_MainSoundProperty_s>>
            ::sendSignal(
                *this,
                "mainSourceSoundPropertyChanged",
                "q(qn)",
                sourceID, soundProperty
        );
}
void CommandControlDBusStubAdapter::fireSinkAvailabilityChangedEvent(const am_sinkID_t& sinkID, const am_Availability_s& availability) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t, am_Availability_s>>
            ::sendSignal(
                *this,
                "sinkAvailabilityChanged",
                "q(iq)",
                sinkID, availability
        );
}
void CommandControlDBusStubAdapter::fireSourceAvailabilityChangedEvent(const am_sourceID_t& sourceID, const am_Availability_s& availability) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sourceID_t, am_Availability_s>>
            ::sendSignal(
                *this,
                "sourceAvailabilityChanged",
                "q(iq)",
                sourceID, availability
        );
}
void CommandControlDBusStubAdapter::fireVolumeChangedEvent(const am_sinkID_t& sinkID, const am_mainVolume_t& volume) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t, am_mainVolume_t>>
            ::sendSignal(
                *this,
                "volumeChanged",
                "qn",
                sinkID, volume
        );
}
void CommandControlDBusStubAdapter::fireSinkMuteStateChangedEvent(const am_sinkID_t& sinkID, const am_MuteState_e& muteState) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t, am_MuteState_e>>
            ::sendSignal(
                *this,
                "sinkMuteStateChanged",
                "qi",
                sinkID, muteState
        );
}
void CommandControlDBusStubAdapter::fireSystemPropertyChangedEvent(const am_SystemProperty_s& systemProperty) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_SystemProperty_s>>
            ::sendSignal(
                *this,
                "systemPropertyChanged",
                "(qn)",
                systemProperty
        );
}
void CommandControlDBusStubAdapter::fireTimingInformationChangedEvent(const am_mainConnectionID_t& mainConnectionID, const am_timeSync_t& time) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_mainConnectionID_t, am_timeSync_t>>
            ::sendSignal(
                *this,
                "timingInformationChanged",
                "qn",
                mainConnectionID, time
        );
}
void CommandControlDBusStubAdapter::fireSinkUpdatedEvent(const am_sinkID_t& sinkID, const am_sinkClass_t& sinkClassID, const am_MainSoundProperty_L& listMainSoundProperties) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t, am_sinkClass_t, am_MainSoundProperty_L>>
            ::sendSignal(
                *this,
                "sinkUpdated",
                "qqa(qn)",
                sinkID, sinkClassID, listMainSoundProperties
        );
}
void CommandControlDBusStubAdapter::fireSourceUpdatedEvent(const am_sourceID_t& sourceID, const am_sourceClass_t& sourceClassID, const am_MainSoundProperty_L& listMainSoundProperties) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sourceID_t, am_sourceClass_t, am_MainSoundProperty_L>>
            ::sendSignal(
                *this,
                "sourceUpdated",
                "qqa(qn)",
                sourceID, sourceClassID, listMainSoundProperties
        );
}
void CommandControlDBusStubAdapter::fireSinkNotificationEvent(const am_sinkID_t& sinkID, const am_NotificationPayload_s& notification) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t, am_NotificationPayload_s>>
            ::sendSignal(
                *this,
                "sinkNotification",
                "q(qn)",
                sinkID, notification
        );
}
void CommandControlDBusStubAdapter::fireSourceNotificationEvent(const am_sourceID_t& sourceID, const am_NotificationPayload_s& notification) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sourceID_t, am_NotificationPayload_s>>
            ::sendSignal(
                *this,
                "sourceNotification",
                "q(qn)",
                sourceID, notification
        );
}
void CommandControlDBusStubAdapter::fireMainSinkNotificationConfigurationChangedEvent(const am_sinkID_t& sinkID, const am_NotificationConfiguration_s& mainNotificationConfiguration) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sinkID_t, am_NotificationConfiguration_s>>
            ::sendSignal(
                *this,
                "mainSinkNotificationConfigurationChanged",
                "q(qin)",
                sinkID, mainNotificationConfiguration
        );
}
void CommandControlDBusStubAdapter::fireMainSourceNotificationConfigurationChangedEvent(const am_sourceID_t& sourceID, const am_NotificationConfiguration_s& mainNotificationConfiguration) {
    CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<am_sourceID_t, am_NotificationConfiguration_s>>
            ::sendSignal(
                *this,
                "mainSourceNotificationConfigurationChanged",
                "q(qin)",
                sourceID, mainNotificationConfiguration
        );
}

} // namespace am
} // namespace genivi
} // namespace org

template<>
const org::genivi::am::CommandControlDBusStubAdapterHelper::StubDispatcherTable org::genivi::am::CommandControlDBusStubAdapterHelper::stubDispatcherTable_ = {
    { { "connect", "qq" }, &org::genivi::am::connectStubDispatcher },
    { { "disconnect", "q" }, &org::genivi::am::disconnectStubDispatcher },
    { { "setVolume", "qn" }, &org::genivi::am::setVolumeStubDispatcher },
    { { "volumeStep", "qn" }, &org::genivi::am::volumeStepStubDispatcher },
    { { "setSinkMuteState", "qi" }, &org::genivi::am::setSinkMuteStateStubDispatcher },
    { { "setMainSinkSoundProperty", "q(qn)" }, &org::genivi::am::setMainSinkSoundPropertyStubDispatcher },
    { { "setMainSourceSoundProperty", "q(qn)" }, &org::genivi::am::setMainSourceSoundPropertyStubDispatcher },
    { { "setSystemProperty", "(qn)" }, &org::genivi::am::setSystemPropertyStubDispatcher },
    { { "getListMainConnections", "" }, &org::genivi::am::getListMainConnectionsStubDispatcher },
    { { "getListMainSinks", "" }, &org::genivi::am::getListMainSinksStubDispatcher },
    { { "getListMainSources", "" }, &org::genivi::am::getListMainSourcesStubDispatcher },
    { { "getListMainSinkSoundProperties", "q" }, &org::genivi::am::getListMainSinkSoundPropertiesStubDispatcher },
    { { "getListMainSourceSoundProperties", "q" }, &org::genivi::am::getListMainSourceSoundPropertiesStubDispatcher },
    { { "getListSourceClasses", "" }, &org::genivi::am::getListSourceClassesStubDispatcher },
    { { "getListSinkClasses", "" }, &org::genivi::am::getListSinkClassesStubDispatcher },
    { { "getListSystemProperties", "" }, &org::genivi::am::getListSystemPropertiesStubDispatcher },
    { { "getTimingInformation", "q" }, &org::genivi::am::getTimingInformationStubDispatcher },
    { { "getListMainSinkNotificationConfigurations", "q" }, &org::genivi::am::getListMainSinkNotificationConfigurationsStubDispatcher },
    { { "getListMainSourceNotificationConfigurations", "q" }, &org::genivi::am::getListMainSourceNotificationConfigurationsStubDispatcher },
    { { "setMainSinkNotificationConfiguration", "q(qin)" }, &org::genivi::am::setMainSinkNotificationConfigurationStubDispatcher },
    { { "setMainSourceNotificationConfiguration", "q(qin)" }, &org::genivi::am::setMainSourceNotificationConfigurationStubDispatcher }
};