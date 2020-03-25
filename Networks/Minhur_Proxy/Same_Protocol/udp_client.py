import socket

SUPER_SECRET_KEY = 1337

def encrypt(text, key):
    return ''.join([chr(ord(c) ^ key) for c in text])

def decrypt(ciphertext, key):
    return ''.join([chr(ord(c) ^ key) for c in ciphertext])

class UDP_Client:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

        self.client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    def run(self):        
        try:
            while 1:
                message = input('> ')
                self.client.sendto(encrypt(message, SUPER_SECRET_KEY).encode(), (self.ip, self.port))
                response = self.client.recvfrom(4096)[0]
                print(response.decode())
        finally:
            self.client.close()

def main():
    client = UDP_Client('127.0.0.1', 1337)
    client.run()


if __name__ == '__main__':
    main()