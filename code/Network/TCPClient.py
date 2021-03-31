from socket import socket, AF_INET, SOCK_STREAM
serverName = "127.0.0.1"
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

msg = input("Input lowercase msg:")
clientSocket.send(msg.encode())

modifiedMsg= clientSocket.recv(2048)
print("From server  ", modifiedMsg.decode())
clientSocket.close
