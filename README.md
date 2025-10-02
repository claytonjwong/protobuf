# Protobuf + Envelope

## Build Instructions
```
mkdir build
cd build
cmake .. && make
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