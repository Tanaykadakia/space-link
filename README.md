# SPACE-LINK Mission Control

SPACE-LINK is a program that pretends to be the control room for a group of satellites. You run it in the terminal and use it through a simple text menu. It does three jobs: it keeps a list of satellites, handles emergency alerts, and finds the best route for sending messages between space locations like Earth, the Moon and Mars.

It was built as a data structures project. Each job is powered by a different data structure, so the space theme is a way of showing how each one solves a real problem.

## Features

| Module | Data structure | What it does |
|---|---|---|
| Satellite Registry | Linked list | Add, display, search and delete satellites by ID |
| Emergency Signals | Priority queue (sorted array) | Stores alerts by severity (1-5) and always processes the most severe first |
| Communication Network | Graph + BFS | Finds the route with the fewest links between two nodes |

## Getting started

You need a C compiler such as GCC.

```
gcc space_network.c -o space_network
./space_network
```

On Windows PowerShell, run it with `.\space_network`.

## Usage

```
====================================
       SPACE-LINK MISSION CONTROL
====================================
1. Satellite Registry (Linked List)
2. Emergency Signals (Priority Queue)
3. Communication Network (Graph + BFS)
4. Exit
```

Type a number to open a module. Each module has its own menu with an option to return to the main menu.

### Example: finding a route

```
Enter starting satellite (e.g. EARTH): EARTH
Enter destination (e.g. MARS): MARS

Route with the fewest links:
EARTH -> SAT2 -> MARS
Total communication links: 2
```

Available nodes: `EARTH`, `SAT1`, `SAT2`, `MOON`, `MARS`, `SAT3` (uppercase only).

## How it works

- **Linked list:** each satellite points to the next one. New satellites are added at the end, and all memory is freed on exit.
- **Priority queue:** alerts are kept sorted by severity, so the most urgent one is always first. Alerts with the same severity are handled in the order they arrived. Capacity is 50.
- **BFS (breadth-first search):** explores the network one step at a time, so the first route it finds to the destination has the fewest links.

## Limitations

- Names and messages cannot contain spaces.
- Data is not saved when the program closes.
- Non-numeric input at a menu prompt is not handled.

## Author

Tanay Kadakia
