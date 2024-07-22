# CPU Scheduling Algorithms Implementation

## Overview

This project implements several CPU scheduling algorithms, providing a comparative analysis of their performance:

- **First Come First Serve (FCFS):** Processes are executed in the order they arrive.
- **Round Robin (RR):** Processes are given a fixed time quantum, and if they don't finish within that time, they are
preempted and added to the back of the ready queue.
- **Non-Preemptive Shortest Job First (NSJF):** The process with the shortest burst time is executed first. Preemption
is not allowed.
- **Preemptive Shortest Job First (PSJF):** The process with the shortest remaining burst time is executed first.
Preemption is allowed.

The code uses C language and stores process data in a `TextData` structure.

## Tech Stack

- **Language:** C
- **Compiler:** GCC (or any other C compiler)

## Installation

1. **Clone the repository:**
```bash
git clone https://github.com/yourusername/your-repository.git
```

2. **Compile the code:**
```bash
gcc CPUSche.c -o CPUSche
```

## Running the Project

1. **Prepare the TaskSpec.txt file:**
- Create a file named `TaskSpec.txt`.
- Each line in this file represents a process with the following format: `process_name,arrival_time,burst_time`.
- For example:
```
P1,0,5
P2,2,3
P3,4,1
P4,6,2
```

2. **Run the executable:**
```bash
./CPUSche
```

## Configuration Settings

- **Time Quantum (RR):** The `timeQuantum` variable in the `main()` function determines the time quantum for the Round
Robin algorithm. You can adjust this value as needed.

## Testing

1. **Run the program:** Execute the `CPUSche` executable as described above.
2. **Check the Output.txt file:** The program generates an `Output.txt` file containing the results of each algorithm,
including:
- **Execution sequence:** The order in which processes are executed.
- **Waiting times:** The time each process spends waiting in the ready queue.
- **Average waiting time:** The average waiting time for all processes.

## Contributing

Contributions are welcome! Please follow these guidelines:

1. **Fork the repository.**
2. **Create a branch for your feature/fix.**
3. **Commit your changes.**
4. **Push to the branch.**
5. **Open a pull request.**

## Licensing

This project is licensed under the MIT License. See the LICENSE file for details.
