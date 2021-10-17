**What is a red black tree?**

A red black tree is a self-balancing binary tree that provides scalable (logarithmic) performance for adding, removing, and finding an object.

**What is the purpose of a red black tree?**

A red black tree implements an associative array, which is similar to C++'s std::map, C#'s Dictionary, Java's java.util.Map, Python's [] dictionary, Lua's [] table, and JavaScript's {} Object.

**What are the goals of this project?**

An implementation that is easy to understand and modify.

**What are the specifications of this implementation?**

1. Every algorithm is iterative.
2. Each node is 32 bytes in size.
3. Each tree is static in size.
4. Nodes are stored in an array.
5. Nodes are referenced by index.
6. NIL is represented by zero.

**Why are the nodes stored in an array and reference by index?**

To allow the node array to be stored and shared in a memory-mapped file.
