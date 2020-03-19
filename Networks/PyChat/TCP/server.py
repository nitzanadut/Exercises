import socket
import selectors

class Server:
    "This class represents a TCP server"

    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.ip, self.port))

        # Setting the blocking to False
        self.server.setblocking(False)

        # Selector Init
        self.selector = selectors.DefaultSelector()
        self.selector.register(fileobj=self.server,
                               events=selectors.EVENT_READ,
                               data=self.accept)

        self.users = dict()

    def run(self):
        "This function runs the selector server"

        self.server.listen(1)

        while True:
            events = self.selector.select()

            # Init event handler
            for key, mask in events:
                event_handler = key.data
                event_handler(key.fileobj, mask)

    def accept(self, sock, mask):
        "Accepting a new client"

        conn, addr = self.server.accept()
        print('{0} has logged in!'.format(addr))

        # Setting client blocking to False
        conn.setblocking(False)

        # Adding client to users and selector
        self.users[conn.fileno()] = conn
        self.selector.register(fileobj=conn, events=selectors.EVENT_READ,
                               data=self.recieve)

    def close_connection(self, conn):
        "Closing a client's connection"

        print('{0} has logged out'.format(conn.getsockname()))
        del self.users[conn.fileno()]
        self.selector.unregister(conn)
        conn.close()

    def recieve(self, conn, mask):
        "A message from a client conn was recieved"

        data = conn.recv(1000).decode()
        addr = conn.getsockname()
        if data:
            print('{0} {1}'.format(addr, data))

            for con in self.users.values():
                message = '{0} {1}'.format(addr, data)
                con.send(message.encode())
        else:
            self.close_connection(conn)

def main():
    server = Server('', 1337)
    server.run()

if __name__ == '__main__':
    main()