Don't run the programs in this directory because you probably do not have
permission to remove the slave_pid file, and if one was not there you would
create one that others could not remove. I left one here on purpose to reduce
confusion.

Assuming that the first test case has been copied, and the programs are in your
PATH, one way to try it out is:
    ex_master < test_signals_01 | ex_slave

Note that when lectura is heavily used, this runs a bit slow! The program does
not do much, but the slave and the master have to wait for each other sometimes.


