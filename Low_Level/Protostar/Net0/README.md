**Net0**

In this challenge we needed to connect to network daemon and sent a random number as a 32bit unsigned int in little endian.
I used nc localhost 2999 and pwntools' p32 function