#include "helpers.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "messages.pb.h"
#include <google/protobuf/message.h>
#include <google/protobuf/stubs/common.h>
#include <iostream>

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    // Create a Mail message containing multiple Envelopes
    demo::Mail mail;

    // Add Envelope with MsgA
    demo::Envelope* envelope1 = mail.add_envelopes();
    envelope1->mutable_a()->set_text("Hello from UDP client");

    // Add Envelope with MsgB
    demo::Envelope* envelope2 = mail.add_envelopes();
    envelope2->mutable_b()->set_number(123);

    // Add Envelope with MsgC
    demo::Envelope* envelope3 = mail.add_envelopes();
    envelope3->mutable_c()->set_value(9.81);

    // Send the Mail message containing all envelopes
    std::cout << "Sending Mail with " << mail.envelopes_size() << " envelopes\n";
    sendMail(sock, serverAddr, mail);

    close(sock);
    google::protobuf::ShutdownProtobufLibrary();
}
