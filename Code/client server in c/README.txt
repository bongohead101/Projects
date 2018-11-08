use gcc to compile
it is optional to use arguments for the file name ports and hostname
i kept the actions output for the server so it will hopefully make it easier to grade

server: gcc server.c -o server
	./server <port> <filename/path>
client: gcc client.c -o client
	./client <hostname> <port>