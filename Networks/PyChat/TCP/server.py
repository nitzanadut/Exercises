import socket
from multiprocessing import Process

def message_handler(conn, addr, clients):
        while 1:
                message = conn.recv(1024).decode()
                if not message: break
                print('{0}: {1}'.format(addr, message))
                
                for client in clients:
                    client.sendall(('({0}, {1})'.format(addr[0], addr[1]) + ' ' + message + '\n').encode())

class Server:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.ip, self.port))

    def run(self):
        self.server.listen(1)
        clients = []

        try:
            while True:
                conn, addr = self.server.accept()
                print(addr, 'has logged in!')
                clients.append(conn)

                p = Process(target=message_handler, args=(conn, addr, clients))
                p.start()
        finally:
            self.server.close()


def main():
    server = Server('0.0.0.0', 31337)
    server.run()


if __name__ == '__main__':
    main()