# Protobuf + Envelope

## Build Instructions
```
mkdir build
cd build
cmake .. && make
```

## Run Server
```
build git:(main) ✗ ./server
UDP Server listening on port 5555...
Got MsgA: Hello from UDP client
Got MsgB: 123
Got MsgC: 9.81
```

## Run Client
```
build git:(main) ✗ ./client
```