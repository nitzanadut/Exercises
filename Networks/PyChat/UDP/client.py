import socket

class Client:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

        self.client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    def run(self):        
        try:
            while 1:
                message = input('> ')
                self.client.sendto(message.encode(), (self.ip, self.port))
                response = self.client.recvfrom(4096)[0]
                print(response.decode())
        finally:
            self.client.close()

def main():
    client = Client('127.0.0.1', 21337)
    client.run()


if __name__ == '__main__':
    main()