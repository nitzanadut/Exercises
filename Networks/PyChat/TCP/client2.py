import client

def main():
    client2 = client.Client('127.0.0.1', 1337)
    client2.run()


if __name__ == '__main__':
    main()