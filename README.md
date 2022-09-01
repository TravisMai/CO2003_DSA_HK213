# DSA-HK213-Cache-implementMy assignment 2 in dsa semester 202

Student Outcomes
After completing this assignment, students will be able to

explain how a cache works
apply AVL tree to search in a simple cache
Introduction
In a real computer machine, the speed of the main memory is very low in comparison with the speed of its processor. To improve the performance, a fast cache memory is used to reduce the processor’s time waiting when accessing instructions and data in main memory. The cache stores copies of the data from the main memory so that future requests for that data can be served faster.

How it works
When the processor firstly references a memory slot in the main memory, the content of the memory slot together with its address are put into the cache. Subsequently, when the processor references the memory slot again, the desired contents are read directly from the fast cache instead of the slow main memory.

Cache replacement Policies
As the size of a cache is limited, when the cache is full and a new data is inserted into the cache for future requests, an existing data in the cache must be selected by the cache replacement policy and it is removed to have place for the new data. There are many cache replacement policies, some of which are listed as below:

FIFO (First In First Out): the oldest data is selected
LIFO (Last In First Out): the newest data is selected
LRU (Least Recently Used): the least recently used data is selected
MSU (Most Recently Used): the most recently used data is selected
LFU (Least Frequently Used): the least frequently used data is selected
RR (Random Replacement): a random data is selected
