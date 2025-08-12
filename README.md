# 🔗 Parallel & Distributed Computing – K Shortest Paths in a Graph

This project implements a **K Shortest Paths** algorithm in C for a directed weighted graph, reading input from a `.csv` dataset.  
It was developed as part of the **Parallel & Distributed Computing** course in Semester 6.

---

## 📌 Features
- Reads **graph data** (nodes, edges, weights) from a CSV file
- Dynamically maps **node names to integer indices**
- Implements **K shortest paths** algorithm using:
  - **Priority queue** (manual implementation)
  - **Adjacency matrix** representation
- Handles large datasets efficiently
- Displays multiple shortest path lengths between specified nodes

---

## ⚙️ How It Works
1. **Read CSV File**  
   - Parses node names and maps them to integer IDs  
   - Stores edges in an integer array
2. **Graph Initialization**  
   - Creates adjacency matrix with `INT_MAX` as default for no connection
3. **K Shortest Paths Calculation**  
   - Uses a priority queue to explore shortest paths iteratively  
   - Keeps track of multiple shortest paths for each node
4. **Output**  
   - Prints the `K` shortest path distances between given start and end nodes

---

## 🧠 Learning Outcomes
- Applied graph algorithms in C
- Implemented K shortest paths logic with priority queues
- Worked with CSV parsing in C
- Managed dynamic memory allocation for performance
- Learned optimization for parallel & distributed systems

## 📜 License
This project is for educational purposes only.
© 2024 Parallel & Distributed Computing – Semester 6
