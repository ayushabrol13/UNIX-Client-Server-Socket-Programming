# UNIX-Client-Server-Socket-Programming

I have implemented a simple client-server model where a client program can chat with a dummy math server.

I learnt about the concepts of Socket Programming and made two Client Server Models.

## Server1.c File

- This is the server file which is used to create a server and listen to the client.
- This is a single process server that can only handle one client at a time.
- This server is used to handle the client and send the data to the client.
- Open a Terminal in the directory where the Server1.c file is present.
- Type the following command to compile the Server1.c file.

        gcc Server1.c -o Server1

- Type the following command to run the Server1.c file.

        ./Server1 5555

  where 5555 is the Port Number that the server is listening to.

## Server2.c File

- This is the server file which is used to create a server and listen to the client.
- This is a multi process server that can handle multiple clients at a time but without the use of multi-threading.
- This server is used to handle the client and send the data to the client.
- Open a Terminal in the directory where the Server2.c file is present.
- Type the following command to compile the Server2.c file.

        gcc Server2.c -o Server2

- Type the following command to run the Server2.c file.

        ./Server2 5555

  where 5555 is the Port Number that the server is listening to.
  NOTE - For the running of the Server2.c file, we need multiple terminals opened as different clients.

## Client.c File

- This file contains the client side code.
- Open another Terminal in the directory where this file is present other than the Terminal in which a Server is running.
- Compile the file using the command

        gcc Client.c -o Client

- Run the file using the command

        ./Client 127.0.01 5555

- NOTE - Only run the Client.c File when a particular server is already running.
- Where ./Client is the argv[0], 127.0.0.1 is the IP address of the server and 5555 is the port number of the server.
- 127.0.0.1 is passed as argv[1] and 5555 is passed as argv[2].

## Overall Analysis

- We analysed the Server1.c file and the Server2.c file and compared the difference between them.

- The Server1.c file is a single process server that can only handle one client at a time and returns "line busy" when any other client tries to connect.

- The Server2.c file is a multi process server that can handle multiple clients at a time.

- In the Server2.c we executed multiple fork() calls to create multiple processes without going towards multi-threading.

## Sample Run

### The Client

The Client code is first compiled. The server runs on port 5555 in another terminal. The client program is then
given the IP (localhost 127.0.0.1 in this case) and port (5555) as command line inputs. Sample runs of the
client goes as follows.

        $ gcc Client.c -o Client
        $ ./Client 127.0.0.1 5555

Connected to server

Please enter the message to the server: 2 + 4

Server replied: 6

Please enter the message to the server: 3 \* 3

Server replied: 9

...

...

### The Server

The sample run of the server is as follows.

        $ gcc Server1.c -o Server1
        $ ./Server1 5555

Connected with client socket number 4

Client socket 4 sent message: 2 + 4

Sending reply: 6

Client socket 4 sent message: 3 \* 3

Sending reply: 9

...

...
