# Inter-Process Communication

This repository contains three programs that demonstrate inter-process communication using different mechanisms: FIFOs, Unix Sockets, and Shared Memory. Each mechanism involves sending and receiving strings between two programs.

## Program Descriptions

- **`fifo`**: This program implements inter-process communication using FIFOs (named pipes). It consists of two programs, `p1_fifo` and `p2_fifo`, which communicate with each other by sending and receiving strings.

- **`socket`**: This program demonstrates inter-process communication using Unix Sockets. Similar to FIFO IPC, it also consists of two programs, `p1_socket` and `p2_socket`, that exchange strings between each other.

- **`sharedmem`**: This program showcases inter-process communication using Shared Memory. It includes two programs, `p1_shared_memory` and `p2_shared_memory`, that share strings by utilizing shared memory segments.

## How to Run the Programs

To run the programs, follow these steps:

1. Clone the entire repository and navigate to the respective folders.

2. Compile the programs by running `make` in the corresponding directories:

   - For FIFO IPC:
     ```
     cd fifo
     make
     ```

   - For Socket IPC:
     ```
     cd socket
     make
     ```

   - For Shared Memory IPC:
     ```
     cd sharedmem
     make
     ```

3. Open two separate terminals for each mechanism and navigate to the respective directories.

4. In one terminal, run the receiving program (P2). In the other terminal, run the sending program (P1). Execute the following commands in the respective terminals:

   - For FIFO IPC:
     ```
     Terminal 1:
     ./p2_fifo

     Terminal 2:
     ./p1_fifo
     ```

   - For Socket IPC:
     ```
     Terminal 1:
     ./p2_socket

     Terminal 2:
     ./p1_socket
     ```

   - For Shared Memory IPC:
     ```
     Terminal 1:
     ./p2_shared_memory

     Terminal 2:
     ./p1_shared_memory
     ```

   Make sure to start the receiving program (P2) before the sending program (P1) to establish proper communication.

5. Observe the inter-process communication results in the terminals.
