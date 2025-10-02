#include "helpers.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <optional>
#include <array>

bool sendMail(int sock, const sockaddr_in& addr, const demo::Mail& mail) {
    std::array<char, 4096> buffer; // larger buffer for Mail
    int size = mail.ByteSizeLong();
    if (size > buffer.size() || !mail.SerializeToArray(buffer.data(), buffer.size())) {
        return false;
    }

    ssize_t sent = sendto(sock, buffer.data(), size, 0,
                          (const sockaddr*)&addr, sizeof(addr));
    return sent == static_cast<ssize_t>(size);
}

std::optional<demo::Mail> recvMail(int sock) {
    std::array<char, 4096> buffer; // stack-allocated buffer
    ssize_t n = recvfrom(sock, buffer.data(), buffer.size(), 0, nullptr, nullptr);
    if (n <= 0) {
        return std::nullopt;
    }

    demo::Mail mail;
    if (mail.ParseFromArray(buffer.data(), n)) {
        return mail;
    }
    return std::nullopt;
}
