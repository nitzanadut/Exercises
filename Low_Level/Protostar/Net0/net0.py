from pwn import *

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

bash.sendline('nc localhost 2999')
data = bash.recvline()
num = int(data.split('\'')[1])
bash.sendline(p32(num))
print(bash.recvline())