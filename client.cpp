#include "helpers.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "messages.pb.h"
#include <google/protobuf/message.h>
#include <google/protobuf/stubs/common.h>

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    demo::Envelope env;

    env.mutable_a()->set_text("Hello from UDP client");
    sendEnvelope(sock, serverAddr, env);

    env.Clear();
    env.mutable_b()->set_number(123);
    sendEnvelope(sock, serverAddr, env);

    env.Clear();
    env.mutable_c()->set_value(9.81);
    sendEnvelope(sock, serverAddr, env);

    close(sock);
    google::protobuf::ShutdownProtobufLibrary();
}
