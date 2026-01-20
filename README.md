# Parking Garage Elimination Simulation

A C-based simulation that determines a winning student through a two-phase elimination process.  
This project demonstrates strong fundamentals in data structures, pointer manipulation, and algorithmic problem solving.

---

## Project Highlights
- Built using **C**
- Implements **circular singly linked lists** and **linked-list-based queues**
- Models a multi-group, multi-phase elimination algorithm
- Handles large inputs with strict output formatting
- Fully memory-safe (no leaks, Valgrind-tested)

---

## Technical Skills
- C Programming
- Data Structures (Queues, Circular Linked Lists)
- Pointer Manipulation
- Dynamic Memory Management
- Algorithm Design & Simulation
- Modular Function Design
- Edge Case Handling

---

## How It Works
### Phase 1 – Group Elimination
Each student group eliminates every k-th student in a circular sequence until a threshold size is reached.

### Phase 2 – Cross-Group Elimination
Students are eliminated across all groups by selecting the highest-numbered front student.  
Ties are broken by choosing the group with the lowest garage number.  
The process continues until one student remains.

---

## Constraints
- No sorting algorithms
- No file I/O (stdin/stdout only)
- Circular linked list implementation required
- Exact output matching required

---

## Build and Run
```bash
gcc main.c -Wno-unused-result
./a.out
```

---

## Outcome
Successfully simulates a complex elimination system while adhering to strict academic and technical constraints.  
This project showcases practical use of low-level data structures and disciplined memory management.
