# **Event Scheduler**  

## **Key Algo's**

-**Min Heap (Priority Queue)** → To keep track of the next upcoming event.
-**Graph (Adjacency List)** → To store dependencies between events.
-**Topological Sorting** → To ensure dependent events occur in the correct order
-A simple **Event Scheduler** that allows users to add, remove, and manage events while handling dependencies between them. The scheduler also checks for cycles in event dependencies and determines a valid execution order.  

## **Features**  
- **Add Events** with a specific date.  
- **View Next Event** scheduled chronologically.  
- **View All Events** sorted by date.  
- **Remove Events** from the schedule.  
- **Add Dependencies** between events.  
- **Cycle Detection** to prevent invalid dependencies.  
- **Check Event Order** using topological sorting.  

## **How It Works**  
- Events are stored in a **Min Heap (priority queue)** to ensure the earliest event is always retrieved first.  
- Dependencies between events are stored as a **Directed Graph (Adjacency List)**.  
- **Cycle detection (DFS)** ensures that dependencies do not create circular dependencies.  
- **Topological Sorting (Kahn’s Algorithm)** determines a valid order of events based on dependencies.  

## **Installation & Compilation**  
Make sure you have **g++ (GCC)** installed.  

### **Compile the program**  
```sh
g++ event_scheduler.cpp -o event_scheduler

Event Scheduler  
1. Add an event  
2. Add a dependency  
3. View next event  
4. Remove event  
5. View all events  
6. Check event order  
7. Exit  
What would you like to do?

Project Structure
📁 Event-Planner-cpp-dsa  
│── 📄 maincode.cpp   # Main source code  
│── 📄 README.md             # Project documentation  

Future Improvements
Save and load events from a file for persistence.
GUI-based interface for easier interaction.
More detailed event metadata (e.g., location, duration).
