// Include necessary libraries
#include <iostream>
#include <fstream>
#include <string>
#include "ns3/internet-module.h"
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/tcp-header.h"
#include "ns3/udp-header.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/error-model.h"
#include "ns3/enum.h"
#include "ns3/event-id.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/traffic-control-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3; // groups all ns-3-related declarations in a scope outside the global namespace
using namespace std;

// Some global objects
Ptr<PacketSink> cbr[5]; // 5 CBR traffic agents
Ptr<PacketSink> tcpSink; // Main traffic
long debugger = 0;
AsciiTraceHelper ascii; // handles ascii trace files by providing a common base class

// Some global variables
bool first_drop = true; // used to check first drop or not
int total_packets_dropped = 0; // keep track of total dropped packets
bool first_transfer = true; // used to check if the byte transferred is the first one or not
int total_bytes_transferred = 0; // keep track of total tranferred bytes

// Define component for logging to monitor or debug the progress of simulation programs
NS_LOG_COMPONENT_DEFINE ("Assign4_Gr4");

// Function to record congestion window values (storing old congestion and new congestion window values); can be used to find the slow start, congestion avoidance
static void CongWindChange(Ptr<OutputStreamWrapper> stream, uint32_t oldCwnd, uint32_t newCwnd){
    debugger++;
    *stream->GetStream() << Simulator::Now().GetSeconds() << ", " << oldCwnd << ", " << newCwnd << ",\n";
    debugger++;
    // cout << debugger << "\n";
}

// Function to record packet drops, total_packets_dropped is incremented each time the packet is dropped
static void PktDrop(Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p){
    debugger++;
    total_packets_dropped++;
    // first_drop variable is used to check if the packet drop is first or not
    if(first_drop){
        first_drop = 0;
        *stream->GetStream() << "0, 0,\n";
        debugger++;
    }
    else{
        *stream->GetStream() << Simulator::Now().GetSeconds() << ", " << total_packets_dropped << ",\n";
        debugger++;
    }
    // cout << debugger << "\n";
}

// Function to find the total cumulative transfered bytes; total_bytes_transferred is incremented each time the byte is transfered
static void TotalBytes(Ptr<OutputStreamWrapper> stream){
    debugger++;
    // Add bytes from N0
    total_bytes_transferred += tcpSink->GetTotalRx();
    // Also add that from CBR traffic agents
    for(int i = 0; i < 5; i++){
        debugger++;
        total_bytes_transferred += cbr[i]->GetTotalRx();
    }
    debugger++;
    // first_transfer variable is used to check if the byte transfer is first or not
    if(first_transfer){
    	first_transfer = 0;
    }
    else{
    	*stream->GetStream() << Simulator::Now().GetSeconds() << ", " << total_bytes_transferred << ",\n";
        debugger++;
    }
    Simulator::Schedule(Seconds(0.001), &TotalBytes, stream);
    debugger++;
    // cout << debugger << "\n";
}

// Trace congestion window length
// Function to call CongWindChange function with appropriate stream to write the value in
static void TraceCongWind(Ptr<OutputStreamWrapper> stream){
    debugger++;
    //Trace changes to the congestion window
    Config::ConnectWithoutContext("/NodeList/0/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeBoundCallback(&CongWindChange, stream));
    debugger++;
    // cout << debugger << "\n";
}

int main(int argc, char *argv[]){
    // Use for command line arguments
    CommandLine cmd;
    // Tcp algo to be used, TcpNewReno by deafult
    string tcp_algo = "TcpNewReno";
    // Max Bytes to be transferred, 0 => unlimited
    uint32_t maxBytes = 0;
    // Start and end times for the 5 CBR traffic agents
    double start[5] = {0.2, 0.4, 0.6, 0.8, 1.0};
    double end[5]   = {1.8, 1.8, 1.2, 1.4, 1.6};

    // Use ./ns3 run "source_code.cc --tcp_algo=tcp_type" for running with specific tcp algorithm where tcp_type is entered by user
    cmd.AddValue("tcp_algo", "TcpNewReno, TcpWestwood, TcpVegas, TcpHybla, TcpScalable", tcp_algo);
    // Parse the input
    cmd.Parse(argc, argv);
    debugger++;
    // cout << debugger << "\n";

    // Selecting the TCP type based on user input
    if(tcp_algo == "TcpNewReno"){
        Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpNewReno::GetTypeId()));
        debugger++;
    }
    else if(tcp_algo == "TcpVegas"){
        Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpVegas::GetTypeId()));
        debugger++;
    }
    else if(tcp_algo == "TcpWestwood"){
        Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpWestwood::GetTypeId()));
        debugger++;
    }
    else if(tcp_algo == "TcpHybla"){
        Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpHybla::GetTypeId()));
        debugger++;
    }
    else if(tcp_algo == "TcpScalable"){
        Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpScalable::GetTypeId()));
        debugger++;
    }
    // Else invalid type, exit the program
    else {
        NS_LOG_DEBUG("Not Valid TCP Type");
        exit(1);
    }
    // cout << debugger << "\n";

    // 3 file names for data storage
    string file1 = tcp_algo + "_bytes_rcvd.txt";
    string file2 = tcp_algo + "_dropped_packets.txt";
    string file3 = tcp_algo + "_cong_wind.txt";
    
    // Creating file streams for data storage
    Ptr<OutputStreamWrapper> bytes_rcvd = ascii.CreateFileStream(file1);
    debugger++;
    Ptr<OutputStreamWrapper> dropped_packets = ascii.CreateFileStream(file2);
    debugger++;
    Ptr<OutputStreamWrapper> cong_wind = ascii.CreateFileStream(file3);
    debugger++;
    // cout << debugger << "\n";

    // Network topology:
    //
    //       N0 ----------- N1
    //            1 Mbps
    //            10 ms

    // Explicitly create the point-to-point link required by the topology with given data rate 1Mbps and delay 10ms.
    NS_LOG_INFO("Creating channels");
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    debugger++;
    pointToPoint.SetChannelAttribute("Delay", StringValue("10ms"));
    debugger++;
    // Bandwidth delay = 1Mbps * 10ms = 10^4 bits = 1250 Bytes; we have to set max queue size of 1250 Bytes
    pointToPoint.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("1p"));
    debugger++;
    // cout << debugger << "\n";

    // Explicitly create the nodes required by the topology.
    NS_LOG_INFO("Creating nodes");
    NodeContainer nodes;
    nodes.Create(2);
    NS_LOG_INFO("Created nodes successfully");
    debugger++;
    // cout << debugger << "\n";

    // Attaching nodes to the network device container
    NetDeviceContainer devices;
    devices = pointToPoint.Install(nodes);
    NS_LOG_INFO("Installed nodes successfully");
    debugger++;
    // cout << debugger << "\n";

    // Install the internet stack on the nodes
    InternetStackHelper internet;
    internet.Install(nodes);
    NS_LOG_INFO("Installed internet successfully");
    debugger++;
    // cout << debugger << "\n";

    // Create error model
    Ptr<RateErrorModel> em = CreateObject<RateErrorModel>();
    em->SetAttribute("ErrorRate", DoubleValue(0.00001));
    debugger++;
    devices.Get(1)->SetAttribute("ReceiveErrorModel", PointerValue(em));
    debugger++;
    // cout << debugger << "\n";

    // We've got the "hardware" in place. Now we need to add IP addresses.
    NS_LOG_INFO ("Assign IP Addresses.");
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    debugger++;
    Ipv4InterfaceContainer ipv4Container = ipv4.Assign(devices);
    debugger++;
    // cout << debugger << "\n";

    // Create a BulkSendApplication and install it on node 0
    NS_LOG_INFO("Creating Applications");
    uint16_t port = 12100;
    BulkSendHelper source("ns3::TcpSocketFactory",InetSocketAddress(ipv4Container.GetAddress(1), port));
    debugger++;
    // cout << debugger << "\n";

    // Set the amount of data to send in bytes.
    source.SetAttribute("MaxBytes", UintegerValue(maxBytes));
    ApplicationContainer sourceApps = source.Install(nodes.Get(0));
    debugger++;
    sourceApps.Start(Seconds(0.0));
    sourceApps.Stop(Seconds(1.80));
    NS_LOG_INFO("Application installed successfully on N0");
    debugger++;
    // cout << debugger << "\n";

    // Create a PacketSinkApplication and install it on node 1
    PacketSinkHelper sink ("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer sinkApps = sink.Install(nodes.Get(1));
    debugger++;
    sinkApps.Start(Seconds(0.0));
    sinkApps.Stop(Seconds(1.80));
    NS_LOG_INFO("Application installed successfully on N1");
    debugger++;
    // cout << debugger << "\n";

    // Get a pointer to application with type-cast
    tcpSink = DynamicCast<PacketSink>(sinkApps.Get(0));
    debugger++;
    // cout << debugger << "\n";

    // Creating a port
    uint16_t cbrPort = 12000;

    // Add 5 CBR traffic agents
    for(int i = 0; i <= 4; i++){
        // Install applications: five CBR streams each saturating the channel
        ApplicationContainer cbrApps, cbrSinkApps;

        // cbrPort+i is used to get the different port numbers
        OnOffHelper onOffHelper("ns3::UdpSocketFactory", InetSocketAddress(ipv4Container.GetAddress(1), cbrPort+i));
        debugger++;
        onOffHelper.SetAttribute("PacketSize", UintegerValue(1024));
        debugger++;
        onOffHelper.SetAttribute("OnTime",  StringValue("ns3::ConstantRandomVariable[Constant=1]"));
        debugger++;
        onOffHelper.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
        debugger++;
        onOffHelper.SetAttribute("DataRate", StringValue("300Kbps"));
        debugger++;
        onOffHelper.SetAttribute("StartTime", TimeValue(Seconds(start[i])));
        debugger++;
        onOffHelper.SetAttribute("StopTime", TimeValue(Seconds(end[i])));
        debugger++;
        cbrApps.Add(onOffHelper.Install(nodes.Get(0)));
        NS_LOG_INFO("CBR installed successfully");
        // cout << debugger << "\n";

        // Packet sinks for each CBR agent
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), cbrPort+i));
        debugger++;
        cbrSinkApps = sink.Install(nodes.Get(1));
        debugger++;
        cbrSinkApps.Start(Seconds(0.0));
        cbrSinkApps.Stop(Seconds(1.8));
        NS_LOG_INFO("CBR-sink installed successfully");
        debugger++;
        // cout << debugger << "\n";

        // Get a pointer to application with type-cast
        cbr[i] = DynamicCast<PacketSink>(cbrSinkApps.Get(0));
        debugger++;
        // cout << debugger << "\n";
    }

    // Keeping track of dropped packets using the PktDrop function
    devices.Get(1)->TraceConnectWithoutContext("PhyRxDrop", MakeBoundCallback(&PktDrop, dropped_packets));
    debugger++;
    // cout << debugger << "\n";

    // Running the simulation
    NS_LOG_INFO("Run Simulation");
    Simulator::Schedule(Seconds(0.00001), &TotalBytes, bytes_rcvd);
    debugger++;
    Simulator::Schedule(Seconds(0.00001), &TraceCongWind, cong_wind);
    debugger++;
    // cout << debugger << "\n";

    // Using Flow monitor for displaying various stats
    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();
    debugger++;
    // cout << debugger << "\n";

    // Set stop time and start the simulation
    Simulator::Stop(Seconds(1.80));
    NS_LOG_INFO("Simulation running...");
    Simulator::Run();
    debugger++;
    // cout << debugger << "\n";

    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowHelper.GetClassifier());
    debugger++;
    map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats();
    FlowMonitor::FlowStats tmp = stats[1];
    debugger++;
    // cout << debugger << "\n";

    string file4 = tcp_algo + "_stat.txt";
    cout << "\nUsing " << tcp_algo <<  " TCP congestion control algorithm.\n";
    cout << "Flow monitor statistics are written in file " << file4 << ".\n";
    // cout << debugger << "\n";

    // Writing the flow monitor statistics to the file named 'p' (same name as that of tcp type used)
    fstream fp;
    fp.open(file4.c_str(), ios::out);
    debugger++;
    fp << "\nUsing " << tcp_algo <<  " TCP congestion control algorithm. Flow monitor statistics:\n\n";
    fp << "Transfered Packets: " << tmp.txPackets << "\n";
    fp << "Transfered Bytes: " << tmp.txBytes << "\n";
    fp << "Offered Load: " << tmp.txBytes * 8.0 / (tmp.timeLastTxPacket.GetSeconds() - tmp.timeFirstTxPacket.GetSeconds()) / (1000 * 1000) << " Mbps" << "\n";
    debugger++;
    fp << "Received Packets: " << tmp.rxPackets << "\n";
    fp << "Received Bytes: " << tmp.rxBytes<< "\n";
    fp << "Throughput: " << tmp.rxBytes * 8.0 / (tmp.timeLastRxPacket.GetSeconds() - tmp.timeFirstRxPacket.GetSeconds()) / (1000 * 1000) << " Mbps" << "\n";
    debugger++;
    fp.close();
    // cout << debugger << "\n";
    
    // Output flowMonitor to XML 
    string file5 = tcp_algo + "_stats.flowmon";
    cout << "Complete flow monitor can be seen in XML file " << file5 << ".\n";
    flowMonitor->SerializeToXmlFile(file5, true, true);
    debugger++;
    // cout << debugger << "\n";

    // Destroy the setup and return
    Simulator::Destroy();
    NS_LOG_INFO("Simulation completed");
    return 0;
}
