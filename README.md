# Protobuf + Envelope

## Build Instructions
```
➜  protobuf git:(main) ./build.sh
-- The CXX compiler identification is GNU 11.4.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Protobuf: /usr/lib/x86_64-linux-gnu/libprotobuf.so (found version "3.12.4")
-- Configuring done
-- Generating done
-- Build files have been written to: /home/clayton/sandbox/protobuf/build
[ 12%] Running cpp protocol buffer compiler on /home/clayton/sandbox/protobuf/messages.proto
[ 25%] Building CXX object CMakeFiles/proto_helpers.dir/messages.pb.cc.o
[ 37%] Building CXX object CMakeFiles/proto_helpers.dir/helpers.cpp.o
[ 50%] Linking CXX static library libproto_helpers.a
[ 50%] Built target proto_helpers
[ 62%] Building CXX object CMakeFiles/server.dir/server.cpp.o
[ 75%] Linking CXX executable server
[ 75%] Built target server
[ 87%] Building CXX object CMakeFiles/client.dir/client.cpp.o
[100%] Linking CXX executable client
[100%] Built target client
```

## Run Server
```
➜  protobuf git:(main) ✗ ./run_server.sh &
[1] 534717
UDP Server listening on port 5555...
```

## Run Client
```
➜  protobuf git:(main) ✗ ./run_client.sh
Sending Mail with 3 envelopes
Received Mail with 3 envelopes
Processing envelope 1:
  MsgA: Hello from UDP client
Processing envelope 2:
  MsgB: 123
Processing envelope 3:
  MsgC: 9.81
```