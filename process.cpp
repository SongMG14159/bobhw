#include <iostream>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <pcap.h>
#include <cstring>
#include <unordered_map>
#include "process.h"

void process_packet(const u_char *packet, int len, std::unordered_map<std::string, ip_stats> &ip_counters) {
    struct ip_header *ip_hdr;
    ip_hdr = (struct ip_header *)(packet + sizeof(struct ether_header));

    char Source_ip[INET_ADDRSTRLEN];
    char Destination_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ip_hdr->ip_src), Source_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip_hdr->ip_dst), Destination_ip, INET_ADDRSTRLEN);

    ip_counters[Source_ip].send_packets++;
    ip_counters[Source_ip].send_bytes += len;

    ip_counters[Destination_ip].receive_packets++;
    ip_counters[Destination_ip].receive_bytes += len;

    std::cout << "송신IP: " << Source_ip << std::endl;
    std::cout << "수신IP: " << Destination_ip << std::endl;
    std::cout << "사용된 protocal: " << (ip_hdr->ip_p == IPPROTO_TCP ? "TCP" : (ip_hdr->ip_p == IPPROTO_UDP ? "UDP" : "Other")) << std::endl;
    std::cout << "송수신된 패킷 바이트: " << len << std::endl;
    std::cout << std::endl;
}

void process_packets(pcap_t *handle) {
    std::unordered_map<std::string, ip_stats> ip_counters;

    struct pcap_pkthdr header;
    const u_char *packet;

    while ((packet = pcap_next(handle, &header)) != NULL) {
        process_packet(packet, header.len, ip_counters);
    }

    // 각IP 별로 송수신 패킷 정리
    for (const auto &entry : ip_counters) {
        std::cout << "--------------------------" << std::endl;
        std::cout << "IP: " << entry.first << std::endl;
        std::cout << "송신 패킷 갯수: " << entry.second.send_packets << std::endl;
        std::cout << "수신 패킷 갯수: " << entry.second.receive_packets << std::endl;
        std::cout << "송신 패킷 바이트: " << entry.second.send_bytes << std::endl;
        std::cout << "수신 패킷 바이트: " << entry.second.receive_bytes << std::endl << std::endl;
    }
}

