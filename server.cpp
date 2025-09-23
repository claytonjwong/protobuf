#include "helpers.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "messages.pb.h"
#include <google/protobuf/message.h>
#include <google/protobuf/stubs/common.h>

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(5555);

    bind(sock, (sockaddr*)&addr, sizeof(addr));

    std::cout << "UDP Server listening on port 5555...\n";

    while (true) {
        demo::Envelope env;
        sockaddr_in clientAddr{};
        if (!recvEnvelope(sock, env, clientAddr)) continue;

        switch (env.payload_case()) {
            case demo::Envelope::kA:
                std::cout << "Got MsgA: " << env.a().text() << "\n";
                break;
            case demo::Envelope::kB:
                std::cout << "Got MsgB: " << env.b().number() << "\n";
                break;
            case demo::Envelope::kC:
                std::cout << "Got MsgC: " << env.c().value() << "\n";
                break;
            default:
                std::cout << "Unknown message\n";
        }
    }

    close(sock);
    google::protobuf::ShutdownProtobufLibrary();
}
