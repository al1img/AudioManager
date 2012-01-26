/**
 * Copyright (C) 2011, BMW AG
 *
 * GeniviAudioMananger AudioManagerDaemon
 *
 * \file databasetest.cpp
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

#include "routingTest.h"
#include "MockInterfaces.h"
#include "DatabaseHandler.h"
#include "ControlReceiver.h"
#include "ControlSender.h"
#include "DatabaseObserver.h"
#include "Router.h"
#include "../ControlInterfaceBackdoor.h"
#include "../CommandInterfaceBackdoor.h"
#include "../CommonFunctions.h"
#include <string.h>

using namespace am;
using namespace testing;

DLT_DECLARE_CONTEXT(DLT_CONTEXT)

routingTest::routingTest() :
        plistRoutingPluginDirs(), //
        plistCommandPluginDirs(), //
        pDatabaseHandler(std::string(":memory:")), //
        pControlSender(std::string("")), //
        pRouter(&pDatabaseHandler,&pControlSender), //
        pRoutingSender(plistRoutingPluginDirs), //
        pCommandSender(plistCommandPluginDirs), //
        pMockInterface(), //
        pMockControlInterface(), //
        pRoutingInterfaceBackdoor(), //
        pCommandInterfaceBackdoor(), //
        pControlInterfaceBackdoor(), //
        pControlReceiver(&pDatabaseHandler, &pRoutingSender, &pCommandSender, &pRouter), //
        pObserver(&pCommandSender, &pRoutingSender)
{
    pDatabaseHandler.registerObserver(&pObserver);
    pCommandInterfaceBackdoor.injectInterface(&pCommandSender, &pMockInterface);
    pControlInterfaceBackdoor.replaceController(&pControlSender, &pMockControlInterface);
}

routingTest::~routingTest()
{
}

void routingTest::SetUp()
{
    DLT_REGISTER_APP("Dtest", "AudioManagerDeamon");
    DLT_REGISTER_CONTEXT(DLT_CONTEXT, "Main", "Main Context");
    DLT_LOG(DLT_CONTEXT, DLT_LOG_INFO, DLT_STRING("Database Test started "));
}

void routingTest::TearDown()
{
    DLT_UNREGISTER_CONTEXT(DLT_CONTEXT);
}

ACTION(returnConnectionFormat)
{
    arg3=arg2;
}

//test that checks 3 domains, one sink one source but the connectionformat of third domains do not fit.
TEST_F(routingTest,simpleRoute3DomainsNoConnection)
{
    EXPECT_CALL(pMockInterface,cbNumberOfSourcesChanged()).Times(3);
    EXPECT_CALL(pMockInterface,cbNumberOfSinksChanged()).Times(3);
    EXPECT_CALL(pMockControlInterface,getConnectionFormatChoice(_,_,_,_)).WillRepeatedly(DoAll(returnConnectionFormat(),Return(E_OK)));

    //initialize 2 domains
    am_Domain_s domain1, domain2, domain3;
    am_domainID_t domainID1, domainID2, domainID3;

    domain1.domainID = 0;
    domain1.name = "domain1";
    domain1.busname = "domain1bus";
    domain1.state = DS_CONTROLLED;
    domain2.domainID = 0;
    domain2.name = "domain2";
    domain2.busname = "domain2bus";
    domain2.state = DS_CONTROLLED;
    domain3.domainID = 0;
    domain3.name = "domain3";
    domain3.busname = "domain3bus";
    domain3.state = DS_CONTROLLED;

    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain1,domainID1));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain2,domainID2));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain3,domainID3));

    am_Source_s source, gwSource, gwSource1;
    am_sourceID_t sourceID, gwSourceID, gwSourceID1;

    source.domainID = domainID1;
    source.name = "source1";
    source.sourceState = SS_ON;
    source.sourceID = 0;
    source.sourceClassID = 5;
    source.listConnectionFormats.push_back(CF_MONO);

    gwSource.domainID = domainID2;
    gwSource.name = "gwsource1";
    gwSource.sourceState = SS_ON;
    gwSource.sourceID = 0;
    gwSource.sourceClassID = 5;
    gwSource.listConnectionFormats.push_back(CF_ANALOG);

    gwSource1.domainID = domainID3;
    gwSource1.name = "gwsource2";
    gwSource1.sourceState = SS_ON;
    gwSource1.sourceID = 0;
    gwSource1.sourceClassID = 5;
    gwSource1.listConnectionFormats.push_back(CF_MONO);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(source,sourceID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(gwSource,gwSourceID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(gwSource1,gwSourceID1));

    am_Sink_s sink, gwSink, gwSink1;
    am_sinkID_t sinkID, gwSinkID, gwSinkID1;

    sink.domainID = domainID3;
    sink.name = "sink1";
    sink.sinkID = 0;
    sink.sinkClassID = 5;
    sink.muteState = MS_MUTED;
    sink.listConnectionFormats.push_back(CF_STEREO);

    gwSink.domainID = domainID1;
    gwSink.name = "gwSink";
    gwSink.sinkID = 0;
    gwSink.sinkClassID = 5;
    gwSink.muteState = MS_MUTED;
    gwSink.listConnectionFormats.push_back(CF_MONO);

    gwSink1.domainID = domainID2;
    gwSink1.name = "gwSink1";
    gwSink1.sinkID = 0;
    gwSink1.sinkClassID = 5;
    gwSink1.muteState = MS_MUTED;
    gwSink1.listConnectionFormats.push_back(CF_ANALOG);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(sink,sinkID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(gwSink,gwSinkID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(gwSink1,gwSinkID1));

    am_Gateway_s gateway, gateway1;
    am_gatewayID_t gatewayID, gatewayID1;

    gateway.controlDomainID = domainID1;
    gateway.gatewayID = 0;
    gateway.sinkID = gwSinkID;
    gateway.sourceID = gwSourceID;
    gateway.domainSourceID = domainID2;
    gateway.domainSinkID = domainID1;
    gateway.listSinkFormats = gwSink.listConnectionFormats;
    gateway.listSourceFormats = gwSource.listConnectionFormats;
    gateway.convertionMatrix.push_back(true);
    gateway.name = "gateway";

    gateway1.controlDomainID = domainID2;
    gateway1.gatewayID = 0;
    gateway1.sinkID = gwSinkID1;
    gateway1.sourceID = gwSourceID1;
    gateway1.domainSourceID = domainID3;
    gateway1.domainSinkID = domainID2;
    gateway1.listSinkFormats = gwSink1.listConnectionFormats;
    gateway1.listSourceFormats = gwSource1.listConnectionFormats;
    gateway1.convertionMatrix.push_back(true);
    gateway1.name = "gateway";

    ASSERT_EQ(E_OK, pDatabaseHandler.enterGatewayDB(gateway,gatewayID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterGatewayDB(gateway1,gatewayID1));

    std::vector<am_Route_s> listRoutes;
    std::vector<am_RoutingElement_s> listRoutingElements;
    am_RoutingElement_s hopp1;
    am_RoutingElement_s hopp2;
    am_RoutingElement_s hopp3;

    hopp1.sourceID = sourceID;
    hopp1.sinkID = gwSinkID;
    hopp1.domainID = domainID1;
    hopp1.connectionFormat = source.listConnectionFormats[0];

    hopp2.sourceID = gwSourceID;
    hopp2.sinkID = gwSinkID1;
    hopp2.domainID = domainID2;
    hopp2.connectionFormat = gwSink1.listConnectionFormats[0];

    hopp3.sourceID = gwSourceID1;
    hopp3.sinkID = sinkID;
    hopp3.domainID = domainID3;
    hopp3.connectionFormat = sink.listConnectionFormats[0];

    listRoutingElements.push_back(hopp1);
    listRoutingElements.push_back(hopp2);
    listRoutingElements.push_back(hopp3);

    am_Route_s compareRoute;
    compareRoute.route = listRoutingElements;
    compareRoute.sinkID = sinkID;
    compareRoute.sourceID = sourceID;

    ASSERT_EQ(E_OK, pRouter.getRoute(false,sourceID,sinkID,listRoutes));
    ASSERT_EQ(0, listRoutes.size());
}
//test that checks just 2 domains, one sink one source with only one connection format each
TEST_F(routingTest,simpleRoute2Domains)
{
    EXPECT_CALL(pMockInterface,cbNumberOfSourcesChanged()).Times(2);
    EXPECT_CALL(pMockInterface,cbNumberOfSinksChanged()).Times(2);
    EXPECT_CALL(pMockControlInterface,getConnectionFormatChoice(_,_,_,_)).WillRepeatedly(DoAll(returnConnectionFormat(),Return(E_OK)));

    //initialize 2 domains
    am_Domain_s domain1, domain2;
    am_domainID_t domainID1, domainID2;

    domain1.domainID = 0;
    domain1.name = "domain1";
    domain1.busname = "domain1bus";
    domain1.state = DS_CONTROLLED;
    domain2.domainID = 0;
    domain2.name = "domain2";
    domain2.busname = "domain2bus";
    domain2.state = DS_CONTROLLED;

    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain1,domainID1));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain2,domainID2));

    am_Source_s source, gwSource;
    am_sourceID_t sourceID, gwSourceID;

    source.domainID = domainID1;
    source.name = "source1";
    source.sourceState = SS_ON;
    source.sourceID = 0;
    source.sourceClassID = 5;
    source.listConnectionFormats.push_back(CF_ANALOG);

    gwSource.domainID = domainID2;
    gwSource.name = "gwsource1";
    gwSource.sourceState = SS_ON;
    gwSource.sourceID = 0;
    gwSource.sourceClassID = 5;
    gwSource.listConnectionFormats.push_back(CF_MONO);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(source,sourceID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(gwSource,gwSourceID));

    am_Sink_s sink, gwSink;
    am_sinkID_t sinkID, gwSinkID;

    sink.domainID = domainID2;
    sink.name = "sink1";
    sink.sinkID = 0;
    sink.sinkClassID = 5;
    sink.muteState = MS_MUTED;
    sink.listConnectionFormats.push_back(CF_MONO);

    gwSink.domainID = domainID1;
    gwSink.name = "gwSink";
    gwSink.sinkID = 0;
    gwSink.sinkClassID = 5;
    gwSink.muteState = MS_MUTED;
    gwSink.listConnectionFormats.push_back(CF_ANALOG);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(sink,sinkID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(gwSink,gwSinkID));

    am_Gateway_s gateway;
    am_gatewayID_t gatewayID;

    gateway.controlDomainID = domainID1;
    gateway.gatewayID = 0;
    gateway.sinkID = gwSinkID;
    gateway.sourceID = gwSourceID;
    gateway.domainSourceID = domainID2;
    gateway.domainSinkID = domainID1;
    gateway.listSinkFormats = gwSink.listConnectionFormats;
    gateway.listSourceFormats = gwSource.listConnectionFormats;
    gateway.convertionMatrix.push_back(true);
    gateway.name = "gateway";

    ASSERT_EQ(E_OK, pDatabaseHandler.enterGatewayDB(gateway,gatewayID));

    std::vector<am_Route_s> listRoutes;
    std::vector<am_RoutingElement_s> listRoutingElements;
    am_RoutingElement_s hopp1;
    am_RoutingElement_s hopp2;

    hopp1.sinkID = gwSinkID;
    hopp1.sourceID = sourceID;
    hopp1.domainID = domainID1;
    hopp1.connectionFormat = source.listConnectionFormats[0];

    hopp2.sinkID = sinkID;
    hopp2.sourceID = gwSourceID;
    hopp2.domainID = domainID2;
    hopp2.connectionFormat = sink.listConnectionFormats[0];

    listRoutingElements.push_back(hopp1);
    listRoutingElements.push_back(hopp2);

    am_Route_s compareRoute;
    compareRoute.route = listRoutingElements;
    compareRoute.sinkID = sinkID;
    compareRoute.sourceID = sourceID;

    ASSERT_EQ(E_OK, pRouter.getRoute(false,sourceID,sinkID,listRoutes));
    ASSERT_EQ(1, listRoutes.size());
    ASSERT_TRUE(pCF.compareRoute(compareRoute,listRoutes[0]));

}

//test that checks just 2 domains, one sink one source but the connectionformat of source
TEST_F(routingTest,simpleRoute2DomainsNoMatchConnectionFormats)
{
    EXPECT_CALL(pMockInterface,cbNumberOfSourcesChanged()).Times(2);
    EXPECT_CALL(pMockInterface,cbNumberOfSinksChanged()).Times(2);
    EXPECT_CALL(pMockControlInterface,getConnectionFormatChoice(_,_,_,_)).WillRepeatedly(DoAll(returnConnectionFormat(),Return(E_OK)));

    //initialize 2 domains
    am_Domain_s domain1, domain2;
    am_domainID_t domainID1, domainID2;

    domain1.domainID = 0;
    domain1.name = "domain1";
    domain1.busname = "domain1bus";
    domain1.state = DS_CONTROLLED;
    domain2.domainID = 0;
    domain2.name = "domain2";
    domain2.busname = "domain2bus";
    domain2.state = DS_CONTROLLED;

    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain1,domainID1));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain2,domainID2));

    am_Source_s source, gwSource;
    am_sourceID_t sourceID, gwSourceID;

    source.domainID = domainID1;
    source.name = "source1";
    source.sourceState = SS_ON;
    source.sourceID = 0;
    source.sourceClassID = 5;
    source.listConnectionFormats.push_back(CF_STEREO);

    gwSource.domainID = domainID2;
    gwSource.name = "gwsource1";
    gwSource.sourceState = SS_ON;
    gwSource.sourceID = 0;
    gwSource.sourceClassID = 5;
    gwSource.listConnectionFormats.push_back(CF_MONO);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(source,sourceID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(gwSource,gwSourceID));

    am_Sink_s sink, gwSink;
    am_sinkID_t sinkID, gwSinkID;

    sink.domainID = domainID2;
    sink.name = "sink1";
    sink.sinkID = 0;
    sink.sinkClassID = 5;
    sink.muteState = MS_MUTED;
    sink.listConnectionFormats.push_back(CF_MONO);

    gwSink.domainID = domainID1;
    gwSink.name = "gwSink";
    gwSink.sinkID = 0;
    gwSink.sinkClassID = 5;
    gwSink.muteState = MS_MUTED;
    gwSink.listConnectionFormats.push_back(CF_ANALOG);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(sink,sinkID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(gwSink,gwSinkID));

    am_Gateway_s gateway;
    am_gatewayID_t gatewayID;

    gateway.controlDomainID = domainID1;
    gateway.gatewayID = 0;
    gateway.sinkID = gwSinkID;
    gateway.sourceID = gwSourceID;
    gateway.domainSourceID = domainID2;
    gateway.domainSinkID = domainID1;
    gateway.listSinkFormats = gwSink.listConnectionFormats;
    gateway.listSourceFormats = gwSource.listConnectionFormats;
    gateway.convertionMatrix.push_back(true);
    gateway.name = "gateway";

    ASSERT_EQ(E_OK, pDatabaseHandler.enterGatewayDB(gateway,gatewayID));

    std::vector<am_Route_s> listRoutes;
    std::vector<am_RoutingElement_s> listRoutingElements;
    am_RoutingElement_s hopp1;
    am_RoutingElement_s hopp2;

    hopp1.sinkID = gwSinkID;
    hopp1.sourceID = sourceID;
    hopp1.domainID = domainID1;
    hopp1.connectionFormat = source.listConnectionFormats[0];

    hopp2.sinkID = sinkID;
    hopp2.sourceID = gwSourceID;
    hopp2.domainID = domainID2;
    hopp2.connectionFormat = sink.listConnectionFormats[0];

    listRoutingElements.push_back(hopp1);
    listRoutingElements.push_back(hopp2);

    am_Route_s compareRoute;
    compareRoute.route = listRoutingElements;
    compareRoute.sinkID = sinkID;
    compareRoute.sourceID = sourceID;

    ASSERT_EQ(E_OK, pRouter.getRoute(false,sourceID,sinkID,listRoutes));
    ASSERT_EQ(0, listRoutes.size());
}

//test that checks 3 domains, one sink one source.
TEST_F(routingTest,simpleRoute3Domains)
{
    EXPECT_CALL(pMockInterface,cbNumberOfSourcesChanged()).Times(3);
    EXPECT_CALL(pMockInterface,cbNumberOfSinksChanged()).Times(3);
    EXPECT_CALL(pMockControlInterface,getConnectionFormatChoice(_,_,_,_)).WillRepeatedly(DoAll(returnConnectionFormat(),Return(E_OK)));

    //initialize 2 domains
    am_Domain_s domain1, domain2, domain3;
    am_domainID_t domainID1, domainID2, domainID3;

    domain1.domainID = 0;
    domain1.name = "domain1";
    domain1.busname = "domain1bus";
    domain1.state = DS_CONTROLLED;
    domain2.domainID = 0;
    domain2.name = "domain2";
    domain2.busname = "domain2bus";
    domain2.state = DS_CONTROLLED;
    domain3.domainID = 0;
    domain3.name = "domain3";
    domain3.busname = "domain3bus";
    domain3.state = DS_CONTROLLED;

    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain1,domainID1));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain2,domainID2));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterDomainDB(domain3,domainID3));

    am_Source_s source, gwSource, gwSource1;
    am_sourceID_t sourceID, gwSourceID, gwSourceID1;

    source.domainID = domainID1;
    source.name = "source1";
    source.sourceState = SS_ON;
    source.sourceID = 0;
    source.sourceClassID = 5;
    source.listConnectionFormats.push_back(CF_MONO);

    gwSource.domainID = domainID2;
    gwSource.name = "gwsource1";
    gwSource.sourceState = SS_ON;
    gwSource.sourceID = 0;
    gwSource.sourceClassID = 5;
    gwSource.listConnectionFormats.push_back(CF_ANALOG);

    gwSource1.domainID = domainID3;
    gwSource1.name = "gwsource2";
    gwSource1.sourceState = SS_ON;
    gwSource1.sourceID = 0;
    gwSource1.sourceClassID = 5;
    gwSource1.listConnectionFormats.push_back(CF_MONO);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(source,sourceID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(gwSource,gwSourceID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSourceDB(gwSource1,gwSourceID1));

    am_Sink_s sink, gwSink, gwSink1;
    am_sinkID_t sinkID, gwSinkID, gwSinkID1;

    sink.domainID = domainID3;
    sink.name = "sink1";
    sink.sinkID = 0;
    sink.sinkClassID = 5;
    sink.muteState = MS_MUTED;
    sink.listConnectionFormats.push_back(CF_MONO);

    gwSink.domainID = domainID1;
    gwSink.name = "gwSink";
    gwSink.sinkID = 0;
    gwSink.sinkClassID = 5;
    gwSink.muteState = MS_MUTED;
    gwSink.listConnectionFormats.push_back(CF_MONO);

    gwSink1.domainID = domainID2;
    gwSink1.name = "gwSink1";
    gwSink1.sinkID = 0;
    gwSink1.sinkClassID = 5;
    gwSink1.muteState = MS_MUTED;
    gwSink1.listConnectionFormats.push_back(CF_ANALOG);

    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(sink,sinkID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(gwSink,gwSinkID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterSinkDB(gwSink1,gwSinkID1));

    am_Gateway_s gateway, gateway1;
    am_gatewayID_t gatewayID, gatewayID1;

    gateway.controlDomainID = domainID1;
    gateway.gatewayID = 0;
    gateway.sinkID = gwSinkID;
    gateway.sourceID = gwSourceID;
    gateway.domainSourceID = domainID2;
    gateway.domainSinkID = domainID1;
    gateway.listSinkFormats = gwSink.listConnectionFormats;
    gateway.listSourceFormats = gwSource.listConnectionFormats;
    gateway.convertionMatrix.push_back(true);
    gateway.name = "gateway";

    gateway1.controlDomainID = domainID2;
    gateway1.gatewayID = 0;
    gateway1.sinkID = gwSinkID1;
    gateway1.sourceID = gwSourceID1;
    gateway1.domainSourceID = domainID3;
    gateway1.domainSinkID = domainID2;
    gateway1.listSinkFormats = gwSink1.listConnectionFormats;
    gateway1.listSourceFormats = gwSource1.listConnectionFormats;
    gateway1.convertionMatrix.push_back(true);
    gateway1.name = "gateway";

    ASSERT_EQ(E_OK, pDatabaseHandler.enterGatewayDB(gateway,gatewayID));
    ASSERT_EQ(E_OK, pDatabaseHandler.enterGatewayDB(gateway1,gatewayID1));

    std::vector<am_Route_s> listRoutes;
    std::vector<am_RoutingElement_s> listRoutingElements;
    am_RoutingElement_s hopp1;
    am_RoutingElement_s hopp2;
    am_RoutingElement_s hopp3;

    hopp1.sourceID = sourceID;
    hopp1.sinkID = gwSinkID;
    hopp1.domainID = domainID1;
    hopp1.connectionFormat = source.listConnectionFormats[0];

    hopp2.sourceID = gwSourceID;
    hopp2.sinkID = gwSinkID1;
    hopp2.domainID = domainID2;
    hopp2.connectionFormat = gwSink1.listConnectionFormats[0];

    hopp3.sourceID = gwSourceID1;
    hopp3.sinkID = sinkID;
    hopp3.domainID = domainID3;
    hopp3.connectionFormat = sink.listConnectionFormats[0];

    listRoutingElements.push_back(hopp1);
    listRoutingElements.push_back(hopp2);
    listRoutingElements.push_back(hopp3);

    am_Route_s compareRoute;
    compareRoute.route = listRoutingElements;
    compareRoute.sinkID = sinkID;
    compareRoute.sourceID = sourceID;

    ASSERT_EQ(E_OK, pRouter.getRoute(false,sourceID,sinkID,listRoutes));
    ASSERT_EQ(1, listRoutes.size());
    ASSERT_TRUE(pCF.compareRoute(compareRoute,listRoutes[0]));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

