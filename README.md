📅 Week 1 – Core C Concepts & UDP Communication
🎯 Focus Areas

    Understand the OSI Model and its role in embedded system communications.

    Reinforce core C programming through practical use of data structures and control logic.

    Develop a UDP-based Chat Application in C using sockets and multithreading.

📘 Topics Covered
📡 Communication & Networking

    OSI Model (7 layers) with real-world protocol examples mapped to each layer.

    Comparison: RTOS vs Superloop architecture.

    Event-driven state machines for reactive system design.

    Basics of scheduling and threading in C.

💻 Core C Concepts

    Arrays, pointers, and the use of callback functions.

    Bitwise operations, masks, and byte packing/unpacking techniques.

🗂️ Data Structures (C Implementation)

    Static Queue: Enqueue, Dequeue, Overflow/Underflow.

    Singly Linked List: Insert, Delete, Traverse.

    Circular Buffer: Fixed-size buffer management with wrap-around.

🛠️ Deliverables
🧠 Documentation

    OSI Model summary with layer-wise protocol examples:

        Application: HTTP, FTP

        Transport: TCP, UDP

        Network: IP, ICMP

        Data Link: Ethernet, PPP

        Physical: RS-232, 802.11

✅ Code Submissions

    Data Structures in C

        Static Queue (Array-based)

        Singly Linked List (Dynamic memory allocation)

        Circular Buffer (Ring buffer logic)

    State Machine Module

        Event-driven control structure for handling system states.

    UDP Chat Application

        Server and Client using Berkeley sockets (C)

        Command-line interface for message input/output.

        Multithreaded server to support multiple client connections concurrently.
        gcc udp_chat.c -o chat -pthread

# Terminal 1 - Start Server
./chat udp_server

# Terminal 2 - Start Client (use 127.0.0.1 for localhost)
./chat udp_client 127.0.0.1

