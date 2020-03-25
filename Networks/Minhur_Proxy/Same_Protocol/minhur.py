import socket
import selectors
from threading import Thread


class Server_TCP:
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

        print('Running TCP...')
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
        print('TCP: {0} has logged in!'.format(addr))

        # Setting client blocking to False
        conn.setblocking(False)

        # Adding client to users and selector
        self.users[conn.fileno()] = conn, addr
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
            try:
                raw = data.split()
                ip, port, message = raw[0], raw[1], ' '.join(raw[2:])
                address = (ip, int(port))
                print('TCP: {0} -> {1}: {2}'.format(addr, address, message))

                for con, curr_addr in self.users.values():
                    if curr_addr == address:
                        con.send(message.encode())
                        conn.send('Message sent!'.encode())
                        break
                else:
                    print('TCP: Invalid address')
                    conn.sendall('Invalid address'.encode())
                
            except:
                print('TCP: Wrong message formatting')
                conn.send('Wrong message format'.encode())

        else:
            self.close_connection(conn)

class Server_UDP:
    "This class represents a TCP server"

    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

        self.server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server.bind((self.ip, self.port))

        # Setting the blocking to False
        self.server.setblocking(False)

        # Selector Init
        self.selector = selectors.DefaultSelector()
        self.selector.register(fileobj=self.server,
                               events=selectors.EVENT_READ,
                               data=self.recieve)

        self.users = dict()

    def run(self):
        "This function runs the selector server"
        
        print('Running UDP...')
        while True:
            events = self.selector.select()

            # Init event handler
            for key, mask in events:
                event_handler = key.data
                event_handler(key.fileobj, mask)

    def recieve(self, conn, mask):
        "A message from a client conn was recieved"

        data, addr = conn.recvfrom(1000)
        
        # Setting client blocking to False
        conn.setblocking(False)

        # Adding client to users and selector
        self.users[addr] = conn

        if data:
            try:
                raw = data.decode().split()
                ip, port, message = raw[0], raw[1], ' '.join(raw[2:])
                address = (ip, int(port))
                print('UDP: {0} -> {1}: {2}'.format(addr, address, message))

                for curr_addr, con in self.users.items():
                    if (curr_addr == address):
                        con.sendto(message.encode(), curr_addr)
                        conn.sendto('Message sent!'.encode(), addr)
                        break
                else:
                    print('UDP: Invalid address')
                    conn.sendto('Invalid address'.encode(), addr)
            except:
                print('UDP: {0} -> Wrong message format'.format(addr))
                self.server.sendto('Wrong message format'.encode(), addr)

def main():
    server_tcp = Server_TCP('', 1337)
    server_udp = Server_UDP('', 1337)
    tcp = Thread(target=server_tcp.run)
    udp = Thread(target=server_udp.run)
    tcp.start()
    udp.start()

if __name__ == '__main__':
    main()
