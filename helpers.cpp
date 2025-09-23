#include "messages.pb.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>

bool sendEnvelope(int sock, const sockaddr_in& addr, const demo::Envelope& env) {
    std::string buffer;
    if (!env.SerializeToString(&buffer)) return false;

    ssize_t sent = sendto(sock, buffer.data(), buffer.size(), 0,
                          (const sockaddr*)&addr, sizeof(addr));
    return sent == (ssize_t)buffer.size();
}

bool recvEnvelope(int sock, demo::Envelope& env, sockaddr_in& srcAddr) {
    std::vector<char> buffer(2048); // large enough for your messages
    socklen_t addrLen = sizeof(srcAddr);
    ssize_t n = recvfrom(sock, buffer.data(), buffer.size(), 0,
                         (sockaddr*)&srcAddr, &addrLen);
    if (n <= 0) return false;

    return env.ParseFromArray(buffer.data(), n);
}
