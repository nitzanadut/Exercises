from pwn import *
import struct

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

bash.sendline('nc localhost 2998')
wanted = bash.recv().split('$ ')[1]
print('[*] wanted: {0}'.format(wanted))

bash.sendline(str(struct.unpack('<i', wanted)[0]))
print(bash.recvline())