from socket import socket, AF_INET, SOCK_DGRAM

serverName='127.0.0.1'
serverPort=12000
clientSocket = socket(AF_INET, SOCK_DGRAM)
message=input('Input lowercase sentence:')
clientSocket.sendto(message.encode(), (serverName, serverPort))
modifieMessage, serverAddress = clientSocket.recvfrom(2048)
print(modifieMessage)
clientSocket.close()