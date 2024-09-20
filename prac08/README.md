# CAB403 - Practical 8 notes

## Materials
- Network Programming: [2024](https://beej.us/guide/bgnet/html/)

## Notes
### 1. TCP_Server_Solution.c:
- In one terminal, run the TCP server using `./tcp <port number>`.
- In another terminal (using natcat to act as the client), run `echo <message> | nc localhost <port number>` to send a message to the server.
- Or you can get the IP address of your local machine by using the command `hostname -I`.

### 2. TCP_Server_Solution.c:
- In one terminal, run the TCP server using `./udp <port number>`.
- In another terminal (using natcat to act as the client), run `nc -u localhost <port number>` and enter your message to send a message to the server.

### 3. 'reference' folder:
- The 'reference' folder contains example code for both Client and Server applications using TCP and UDP. In these examples, the Server receives a message from the Client and sends it back to the Client (hence the term 'Echo').

