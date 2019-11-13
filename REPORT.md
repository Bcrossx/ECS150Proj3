#User-level thread library
##Implementation

###Category: Semaphore API

#####Semaphore up/down
The semaphore up/down functions proved to be the most tricky for us as far
as the semaphore phase went. The idea seemed to be straightforwards but
we initially had some incorrect implementation where we were checking the
count and not the length of our blocked threads queue. Also after going
through the slides again I realized in sem_down we needed a while loop
and not just an if statement to keep checking and enqueuing the thread ID's.

#####Corner case
After thinking about this corner case we thought about having a two queue
implementation. Which would've been one queue for blocked threads and the
other for unblocked threads. But thought our implementation should be able
to take care of this case as is.

####Testing
The testers gave us many issues which took an absurd amount of time to debug.
The main issues came from small mistakes such as in sem_down not using the
while loop and sem_up not using the length of the blocked_queue. Though for
some reason we still have issues with the sem_buffer test case where we
suspect a thread is stuck on blocked and for some reason is not being
unblocked. Other than that our semaphore implementation seems to work great.

###Category: TPS API
It took us a long time to figure out where to even begin with the TPS API.
For some reason this part really confused us both, eventually we decided we
would need two structs for the page and TPS because thinking ahead we thought
we may need a way to ensure mutual exclusivity for the data.

#####tps_read/write
It seems our biggest frustrations with this phase was these functions. They
seemed straightforward enough but we had a tough time figuring out how to
apply the different functions to achieve the goal of each function
respectively.

####Testing
Sadly our code was so filled with little bugs that were beyond our
comprehension so we did not get to do much testing for this phase. We
tried to debug as much as possible and have a strong intuition that the fault
of our code is in the read/write functions. We tried for many hours to run
through gdb and find out what data we were getting and why we aren't getting
right outcome but sadly we fell short.

##Outside Sources
######Linux man pages
