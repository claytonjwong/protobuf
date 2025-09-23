#include "helpers.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <optional>
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
        std::optional<demo::Envelope> optional_envelope = recvEnvelope(sock);
        if (!optional_envelope.has_value())
        {
            continue;
        }
        demo::Envelope envelope = optional_envelope.value();

        switch (envelope.payload_case()) {
            case demo::Envelope::kA:
                std::cout << "Got MsgA: " << envelope.a().text() << "\n";
                break;
            case demo::Envelope::kB:
                std::cout << "Got MsgB: " << envelope.b().number() << "\n";
                break;
            case demo::Envelope::kC:
                std::cout << "Got MsgC: " << envelope.c().value() << "\n";
                break;
        }
    }

    close(sock);
    google::protobuf::ShutdownProtobufLibrary();
}
