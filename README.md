### Introdution
In order to Remote Execute Command via local internet. That is two code files, one is for server program, and another to client. You could execute server program to listen one port. And then connect with client provided server ip and port. ~~When you compile, listen server program on one port. Then use client program on the local network area with server ip and port.~~ 
#### Compile
gcc -o server server_ssl.c -pthread
gcc -o client client_ssl_.c -pthread

#### Usage
$./server 12345
#here 12345 port of this machine will be open
#open another shell, type in  
$./cient 127.0.0.1 12345
#127.0.0.1 is the ip address of server, and 12345 is the port that server provide. 
#Then the feedback returned on client is the result from the execution of serverfor the command you type in client.



