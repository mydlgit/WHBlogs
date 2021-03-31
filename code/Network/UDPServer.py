from socket import socket, AF_INET, SOCK_DGRAM
import time

serverPort=12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverAddress = ("127.0.0.1", serverPort)
serverSocket.bind(serverAddress)
print('The server is ready to recive')

start = time.time()
while(1):
    message, clientAddress = serverSocket.recvfrom(2048)
    modifieMsg = message.upper()
    serverSocket.sendto(modifieMsg, clientAddress)
    break

serverSocket.close()
print('server closed')