# SequentialAndMultiProcess


The subject of this project is to calculate the standard deviation of two separate files with sequential and multi-process program and compare the runtimes of sequential and multi-process program and see the effect of using multi-process program on the program’s runtime. 

In the sequential program, we put the numbers in the files into two arrays and calculated the summation of two files. After, we put all the numbers into one array and calculated the standard deviation of the numbers. Lastly, we printed the standard deviation and printed calculation time of the sequential program in milliseconds.

In the multi-process part, we used the shared memory interprocess communication. Firstly, with fork() system call we created two processes, one as the parent process and the other one as the child process. Process identifier for the child process is zero and process identifier for the parent process is nonzero. Within the child process we created a shared memory object called “Project1”. Via shared memory, child process sent the partial sum of file2.txt to the parent process. And parent process calculated the global average with these informations and sent the global average to child process through shared memory. With the global average, parent and child processes calculated the partial variance separately. Later, child process sent the partial variance to the parent process through shared memory. Lastly, parent process calculated the standard deviation of the numbers in two files with these data and printed the standard deviation and printed calculation time of the multi-process program in milliseconds.

Operating Systems: Ubuntu Linux

Programming Languages: C
