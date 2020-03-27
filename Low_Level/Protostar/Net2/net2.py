from pwn import *
from subprocess import Popen, PIPE
import shlex

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

bash.sendline('nc localhost 2997')
data = bash.recv().split(':~$ ')[1]
print('[*] Data: ' + data)

# Unpacking
numbers = [int(unpack(''.join(data[i * 4:(i + 1) * 4]))) for i in range(4)]
print('[*] Unpacked Numbers: ' + ' '.join([str(i) for i in numbers]))

# Calling the c file to sum up the numbers
cmd = "./sum {0}".format(' '.join([str(i) for i in numbers]))
p = subprocess.Popen(shlex.split(cmd), stdout=PIPE)
sum_ = p.communicate()[0]

print('[*] Sum: {0}'.format(sum_))
    
bash.sendline(p32(int(sum_)))
print(bash.recvline())