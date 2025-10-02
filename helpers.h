#pragma once

#include "messages.pb.h"
#include <arpa/inet.h>
#include <optional>
#include <sys/socket.h>

bool sendMail(int sock, const sockaddr_in& addr, const demo::Mail& mail);

std::optional<demo::Mail> recvMail(int sock);
