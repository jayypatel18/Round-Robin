This code implements a simulation of the Round Robin scheduling algorithm, which is a pre-emptive process scheduling algorithm. Here are the unique features of our code:

1. Classes for Process Management:
   - Your code defines two classes: `PCB` (Process Control Block) and `ReadyQueue`. These classes help in organizing and managing processes.

2. Round Robin Scheduling:
   - The `RoundRobin` class implements the Round Robin scheduling algorithm. It manages the execution of processes in a time-sliced manner, where each process gets a fixed time quantum of 3 seconds before being pre-empted.

3. Dispatcher Function:
   - The `dispatcher()` function is the heart of the scheduling algorithm. It handles the execution, pre-emption, and re-queuing of processes based on their remaining execution time.

4. Output:
   - The program calculates and displays statistics like average waiting time and average turn around time after all processes have been executed.

5. User Interaction:
   - The program prompts the user to input the number of processes and their details (process ID and execution time) before simulating the scheduling.
6. Novelty:
   - We have implemented this algorithm with the use of nothing but linked list to add process and manipulate it in the PCB.
