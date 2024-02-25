#ifndef PROCESS_H
#define PROCESS_H

#include <pcap.h>
#include <unordered_map>
#include <netinet/ip.h>

struct ip_stats {
    int send_packets;
    int receive_packets;
    int send_bytes;
    int receive_bytes;

    ip_stats() : send_packets(0), receive_packets(0), send_bytes(0), receive_bytes(0) {}
};

struct ip_header {
    u_int8_t  ip_vhl;
    u_int8_t  ip_tos;
    u_int16_t ip_len;
    u_int16_t ip_id;
    u_int16_t ip_off;
    u_int8_t  ip_ttl;
    u_int8_t  ip_p;
    u_int16_t ip_sum;
    struct    in_addr ip_src, ip_dst;
};

void process_packets(pcap_t *handle);

#endif // PROCESS_H

