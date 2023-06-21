# Inter-Process Communication

This repository contains three programs that demonstrate inter-process communication using different mechanisms: FIFOs, Unix Sockets, and Shared Memory. Each mechanism involves sending and receiving strings between two programs.

## Program Descriptions

- **`FIFO`**: This program implements inter-process communication using FIFOs (named pipes). It consists of two programs, `fifop1` and `fifop2`, which communicate with each other by sending and receiving strings.

- **`Socket`**: This program demonstrates inter-process communication using Unix Sockets. Similar to FIFO IPC, it also consists of two programs, `socketp1` and `socketp2`, that exchange strings between each other.

- **`Sharedmem`**: This program showcases inter-process communication using Shared Memory. It includes two programs, `sharedmemp1` and `sharedmemp2`, that share strings by utilizing shared memory segments.

## How to Run the Programs

To run the programs, follow these steps:

1. Clone the entire repository and navigate to the respective folders.

2. Compile the programs by running `make` in the corresponding directories:

   - For FIFO IPC:
     ```
     cd FIFO
     make
     ```

   - For Socket IPC:
     ```
     cd Socket
     make
     ```

   - For Shared Memory IPC:
     ```
     cd Sharedmem
     make
     ```

3. Open two separate terminals for each mechanism and navigate to the respective directories.

4. In one terminal, run the receiving program (P2). In the other terminal, run the sending program (P1). Execute the following commands in the respective terminals:

   - For FIFO IPC:
     ```
     Terminal 1:
     ./fifop1

     Terminal 2:
     ./fifop2
     ```

   - For Socket IPC:
     ```
     Terminal 1:
     ./socketp2

     Terminal 2:
     ./socketp1
     ```

   - For Shared Memory IPC:
     ```
     Terminal 1:
     ./sharedmemp2

     Terminal 2:
     ./sharedmemp1
     ```

   Make sure to start the receiving program (P2) before the sending program (P1) to establish proper communication.

5. Observe the inter-process communication results in the terminals.
