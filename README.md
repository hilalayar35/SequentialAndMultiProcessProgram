# SequentialAndMultiProcessProgram


The subject of this project is to calculate the standard deviation of two separate files with sequential and multi-process program and compare the runtimes of sequential and multi-process program and see the effect of using multi-process program on the program’s runtime. 

Runtime of the multi-process program is generally half of the runtime of sequential program. Multi-process program is twice as fast as the sequential program. We chose the shared memory interprocess communication model because it is faster but implementation of shared memory model is not easy. Two processes shared a memory area of 4096 bytes. In addition, the multi-process program is more efficient than a sequential program because it divides the calculation into processes and therefore reduces the workload on the CPU.

Operating Systems: Ubuntu Linux

Programming Languages: C
