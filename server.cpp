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
        // Try to receive a Mail message
        std::optional<demo::Mail> optional_mail = recvMail(sock);
        if (!optional_mail.has_value()) {
            continue;
        }
        demo::Mail mail = optional_mail.value();
        std::cout << "Received Mail with " << mail.envelopes_size() << " envelopes\n";

        // Process each envelope in the mail
        for (int i = 0; i < mail.envelopes_size(); i++) {
            const demo::Envelope& envelope = mail.envelopes(i);
            std::cout << "Processing envelope " << i + 1 << ":\n";

            switch (envelope.payload_case()) {
                case demo::Envelope::kA:
                    std::cout << "  MsgA: " << envelope.a().text() << "\n";
                    break;
                case demo::Envelope::kB:
                    std::cout << "  MsgB: " << envelope.b().number() << "\n";
                    break;
                case demo::Envelope::kC:
                    std::cout << "  MsgC: " << envelope.c().value() << "\n";
                    break;
                default:
                    std::cout << "  Unknown message type\n";
                    break;
            }
        }
    }

    close(sock);
    google::protobuf::ShutdownProtobufLibrary();
}
