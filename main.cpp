#include <iostream>
#include <pcap.h>
#include "process.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "사용하는 pcap 파일: " << argv[0] << " <pcap_file>\n";
        return 1;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(argv[1], errbuf);
    if (handle == NULL) {
        std::cerr << "파일을 여는중 오류 발생" << argv[1] << ": " << errbuf << "\n";
        return 1;
    }

    process_packets(handle);

    pcap_close(handle);

    return 0;
}

