#pragma once

#include "messages.pb.h"
#include <arpa/inet.h>
#include <sys/socket.h>

bool sendEnvelope(int sock, const sockaddr_in& addr, const demo::Envelope& env);
bool recvEnvelope(int sock, demo::Envelope& env, sockaddr_in& srcAddr);