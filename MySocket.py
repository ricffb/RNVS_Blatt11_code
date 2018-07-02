#!/usr/bin/python3 

import socket

IP_ADDR = '127.0.0.1'
PORT = 61680 
BUFFER_SIZE = 1024 
MESSAGE = "Python-Client listening to " +IP_ADDR+ "\n"

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM) 
s.connect((IP_ADDR,PORT)) 
s.send(MESSAGE.encode()) 

while True:
    data=s.recv(BUFFER_SIZE).decode().strip('\n')

    if data == "exit":
        break
    print('Received data: ', data)
s.close()