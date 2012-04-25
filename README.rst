A shared library that puts your program into an infinite loop when it segfaults
=============================

``Problem:`` A bad program causes segfault.  You want to poke around
but don't want to or can't recompile the source.

``This tool:`` This shared library will install a SIGSEGV handler and
go into infinite loop when segmentation fault occur.

``TODO:``

* Add other signals so we can "pause" a running program, or perhaps
  a running thread; using pthread_kill() to broadcast the signal to
  the targeted thread.

* Intercept the process and thread creation so the user can selectively
  "pause" process or thread as she wants.

Compile
-------
To compile, you simply run make: ::

$ make

Example
----
To run with your program that will cause segfault,
simple add the memd.so to ``LD_PRELOAD``: ::

 $ LD_PRELOAD=./memd.so ./pi 5

If the program crashes, it will print out the process id and
thread id like below sreenshot: ::

 $ LD_PRELOAD=./memd.so ./pi 5
 Installing SIGSEGV handler...
 long double size = 16 bytes
 thread thr_an started
 thread thr_bn started
 thread thr_tn started
 thread thr_pn started
 Pi = 2.9142135623730933185939612206638571478833910077810287475585937500
 Segmentation fault occurred at address 0
 Process id 9024 thread id 0x8c14b700