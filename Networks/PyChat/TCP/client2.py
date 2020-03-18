import client

def main():
    client2 = client.Client('127.0.0.1', 31337)
    client2.run()


if __name__ == '__main__':
    main()