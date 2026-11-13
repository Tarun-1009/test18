# Operating System Lab - Simple & Compact C Solutions
**MNNIT Allahabad - Operating Systems Lab**

All code has been rewritten to be **minimal, simple, and concise** (25–40 lines each), making it easy to understand, write in lab notebooks, and run in practical exams.

---

## Files Overview

### 📁 Assignment 2: File System Calls
* [q1_file_operations.c](file:///d:/Downloads/osassignments/Assignment2/q1_file_operations.c) (~45 lines): Create, write, read, link, unlink, copy, and reverse read.
* [q2_read_15_chars.c](file:///d:/Downloads/osassignments/Assignment2/q2_read_15_chars.c) (~20 lines): Read up to 15 characters from `stdin` using `read(0, ...)` and display.
* [q3_copy_20_chars.c](file:///d:/Downloads/osassignments/Assignment2/q3_copy_20_chars.c) (~30 lines): Read 20 chars of `F1.txt` and append to `F2.txt`.
* [q4_merge_txt_files.c](file:///d:/Downloads/osassignments/Assignment2/q4_merge_txt_files.c) (~25 lines): Read all `.txt` files in directory and merge into `merged.txt`.
* [q5_print_last_5.c](file:///d:/Downloads/osassignments/Assignment2/q5_print_last_5.c) (~25 lines): Print last 5 characters using `lseek(fd, -5, SEEK_END)`.
* [q6_extract_range.c](file:///d:/Downloads/osassignments/Assignment2/q6_extract_range.c) (~25 lines): Seek to 15th char and copy 6 characters to `F2.txt`.

### 📁 Assignment 3: Process Management (`fork`)
* [q1_child_exit_status.c](file:///d:/Downloads/osassignments/Assignment3/q1_child_exit_status.c) (~20 lines): Child exits, parent calls `wait(&status)` and prints decimal & hex exit code.
* [q2_fork_variable.c](file:///d:/Downloads/osassignments/Assignment3/q2_fork_variable.c) (~20 lines): Demonstrates variable copy and memory isolation between parent and child.
* [q3_fork_file_sharing.c](file:///d:/Downloads/osassignments/Assignment3/q3_fork_file_sharing.c) (~20 lines): Demonstrates shared file descriptor offset across `fork()`.
* [q4_collatz.c](file:///d:/Downloads/osassignments/Assignment3/q4_collatz.c) (~20 lines): Child calculates Collatz sequence for argument; parent waits.

### 📁 Assignment 4: Pipes & Named Pipes (FIFOs)
* [q1_pipe_factorial.c](file:///d:/Downloads/osassignments/Assignment4/q1_pipe_factorial.c) (~25 lines): Parent sends number via pipe; child calculates factorial.
* [q2_two_way_pipe.c](file:///d:/Downloads/osassignments/Assignment4/q2_two_way_pipe.c) (~35 lines): Two pipes: parent sends string, child toggles case and returns it.
* [q3_named_pipe_vowels.c](file:///d:/Downloads/osassignments/Assignment4/q3_named_pipe_vowels.c) (~35 lines): Parent writes sentence to named pipe (`/tmp/my_fifo`); child counts vowels.
* [my_npipe_reader.c](file:///d:/Downloads/osassignments/Assignment4/my_npipe_reader.c) & [my_npipe_writer.c](file:///d:/Downloads/osassignments/Assignment4/my_npipe_writer.c): Inter-process communication via `/tmp/mypipe` until `'exit'`.

### 📁 Assignment 5: CPU Scheduling Algorithms
* [q1a_fcfs.c](file:///d:/Downloads/osassignments/Assignment5/q1a_fcfs.c) (~25 lines): First-Come First-Served algorithm.
* [q1b_sjf.c](file:///d:/Downloads/osassignments/Assignment5/q1b_sjf.c) (~35 lines): Shortest Job First (Non-preemptive).
* [q1c_round_robin.c](file:///d:/Downloads/osassignments/Assignment5/q1c_round_robin.c) (~35 lines): Round Robin (Time quantum = 2 ms).
* [q1d_priority.c](file:///d:/Downloads/osassignments/Assignment5/q1d_priority.c) (~35 lines): Priority scheduling ($P2 > P3 > P1 > P4$).
* [q1_scheduling.c](file:///d:/Downloads/osassignments/Assignment5/q1_scheduling.c) (~30 lines): Quick all-in-one runner for Q1.
* [q2_srtf.c](file:///d:/Downloads/osassignments/Assignment5/q2_srtf.c) (~35 lines): Shortest Remaining Time First (Preemptive SJF).
* [q3_mlq.c](file:///d:/Downloads/osassignments/Assignment5/q3_mlq.c) (~25 lines): Multi-Level Queue (System processes run before User processes).
* [q4_mlfq.c](file:///d:/Downloads/osassignments/Assignment5/q4_mlfq.c) (~50 lines): Multilevel Feedback Queue with timeline and results.

### 📁 Assignment 6: Multithreading (`pthread`)
* [q1_stats_threads.c](file:///d:/Downloads/osassignments/Assignment6/q1_stats_threads.c) (~35 lines): 3 threads for Average, Minimum, and Maximum.
* [q2_matrix_threads.c](file:///d:/Downloads/osassignments/Assignment6/q2_matrix_threads.c) (~35 lines): 2 parallel threads compute $(A+B)$ and $(A-B)$; main computes product.
* [q3_prefix_product.c](file:///d:/Downloads/osassignments/Assignment6/q3_prefix_product.c) (~35 lines): $N$ threads compute prefix products.
* [q4_fibonacci_thread.c](file:///d:/Downloads/osassignments/Assignment6/q4_fibonacci_thread.c) (~25 lines): Worker thread generates Fibonacci sequence.
* [q5_bank_system.c](file:///d:/Downloads/osassignments/Assignment6/q5_bank_system.c) (~40 lines): Mutex-synchronized banking simulation.

### 📁 Assignment 8: Shared Memory & Synchronization
* [q1_race_shared_memory.c](file:///d:/Downloads/osassignments/Assignment8/q1_race_shared_memory.c) (~35 lines): Shared memory (`shmget`/`shmat`) race condition demonstration.
* [q2a_bounded_buffer_semaphore.c](file:///d:/Downloads/osassignments/Assignment8/q2a_bounded_buffer_semaphore.c) (~45 lines): Bounded-buffer using semaphores.
* [q2b_bounded_buffer_monitor.c](file:///d:/Downloads/osassignments/Assignment8/q2b_bounded_buffer_monitor.c) (~45 lines): Bounded-buffer using monitor (`mutex` + condition variables).

---

## How to Compile & Run (Linux / WSL)

```bash
# Basic single file compilation:
gcc Assignment5/q1a_fcfs.c -o fcfs
./fcfs

# Multithreaded compilation (requires -pthread):
gcc -pthread Assignment6/q1_stats_threads.c -o stats
./stats 90 81 78 95 79 72 85
```
