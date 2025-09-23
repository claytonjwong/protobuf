#include "messages.pb.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <optional>
#include <vector>

bool sendEnvelope(int sock, const sockaddr_in& addr, const demo::Envelope& env) {
    std::string buffer;
    if (!env.SerializeToString(&buffer)) {
        return false;
    }

    ssize_t sent = sendto(sock, buffer.data(), buffer.size(), 0,
                          (const sockaddr*)&addr, sizeof(addr));
    return sent == static_cast<ssize_t>(buffer.size());
}

std::optional<demo::Envelope> recvEnvelope(int sock) {
    std::vector<char> buffer(2048); // large enough for your messages
    ssize_t n = recvfrom(sock, buffer.data(), buffer.size(), 0, nullptr, nullptr);
    if (n <= 0) {
        return std::nullopt;
    }

    demo::Envelope envelope;
    if (envelope.ParseFromArray(buffer.data(), n)) {
        return envelope;
    }
    return std::nullopt;
}
