import socket

class Client:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def run(self):        
        self.client.connect((self.ip, self.port))

        try:
            while 1:
                message = input('> ')
                self.client.sendall(message.encode())
                response = self.client.recv(1024)
                print(response.decode(), end='')
        finally:
            self.client.close()

def main():
    client = Client('127.0.0.1', 31337)
    client.run()


if __name__ == '__main__':
    main()