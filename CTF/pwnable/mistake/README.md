**mistake (1 Point)**


At first glance this line seemed weird, like a parentheses was missing.

```diff
if(fd=open("/home/mistake/password",O_RDONLY,0400) < 0){
```

When checking about operator priority I realized this line will be evaluated like this:

```diff
if(fd=(open("/home/mistake/password",O_RDONLY,0400) < 0))
```

Meaning, fd will equal zero, and not a file pointer!
We get the password from stdin, that's why there's a delay after the "do not bruteforce..." prompt that's longer than 20 seconds, the program is waiting for user input!

Then, the password is xor'ed with 1.

A = 0x41 = 0b1000001

A ^ 1 = 0b1000000 = @


```diff
$ ./mistake
do not bruteforce...
AAAA
input password : AAAA
Wrong Password

$ ./mistake
do not bruteforce...
AAAAAAAAAA
input password : @@@@@@@@@@
Password OK
Mommy, the operator priority always confuses me :(

```