from socket import socket, AF_INET, SOCK_STREAM

serverPort=12000
serverName='127.0.0.1'

serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind((serverName, serverPort))
serverSocket.listen(1)  #设置请求队列大小为1

print('Ther server is ready to receive')

while(1):
    connectionSocket, addr = serverSocket.accept()
    print('client addr info:', addr)
    msg = connectionSocket.recv(2048)
    modifiedMsg = msg.upper()
    connectionSocket.send(modifiedMsg)
    connectionSocket.close()
    print('connection socket is closed')
    # break

serverSocket.close()
print('server socket is closed')