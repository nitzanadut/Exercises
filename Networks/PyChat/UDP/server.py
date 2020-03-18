import socket

class Server:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

        self.server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server.bind((self.ip, self.port))
    
    def run(self):
        try:
            while 1:
                message, addr = self.server.recvfrom(4096)
                if not message: break
                print('{0}: {1}'.format(addr, message.decode()))
                self.server.sendto(message, addr)
        finally:
            self.server.close()


def main():
    server = Server('0.0.0.0', 21337)
    server.run()


if __name__ == '__main__':
    main()