SemaphoreAssignment1
By:
1. Full Name: [Mahsheed Najeed]
   Class Account: [cssc1445@edoras.sdsu.edu]


2. Full Name: [Jasmine Mcduffie]
   Class Account: [teammate_edoras_username]


Testing Account:
Please use the following account to test the project:
[cssc1445@edoras.sdsu.edu]  


Project Description:
This project implements a multithreaded C program using semaphores to synchronize access to a shared file (QUOTE.txt). The program spawns 7 threads that come up at different times during run time, based on if they are even or odd. Each of the threads creates quotes to the file at, depending on the pause time, while using a semaphore to ensure that file access is thread-safe. There will be 2 different quotes printed on the quotes.txt file, and it will depend if the threat is even or odd. 


Build Instructions:
To compile the project using the provided Makefile:


1. Open a terminal or command prompt.
2. Navigate to the project directory:
   cd CLionProjects\SemaphorAssignment1
3. Run:
   make


Run Instructions:
After compilation, run the executable:
   SemaphorAssignment1.exe


To clean up the executable:
   make clean


Files Included:
- main.c               //Main file with C code
- Makefile             //Build configuration
- QUOTE.txt            //The output file with the threads and corresponding quotes