#pragma once

#include "messages.pb.h"
#include <arpa/inet.h>
#include <optional>
#include <sys/socket.h>

bool sendEnvelope(int sock, const sockaddr_in& addr, const demo::Envelope& env);
std::optional<demo::Envelope> recvEnvelope(int sock);