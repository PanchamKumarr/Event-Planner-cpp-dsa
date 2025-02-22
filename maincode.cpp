#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

struct Event {
    string name;
    int date;
    Event(string n, int d) : name(n), date(d) {}
};

struct Compare {
    bool operator()(Event a, Event b) {
        return a.date > b.date;
    }
};

class EventScheduler {
private:
    priority_queue<Event, vector<Event>, Compare> minHeap;
    unordered_map<string, vector<string>> adjList;
    unordered_map<string, int> inDegree;

    bool hasCycle(string event, unordered_set<string> &visited, unordered_set<string> &recStack) {
        if (!visited.count(event)) {
            visited.insert(event);
            recStack.insert(event);
            for (string neighbor : adjList[event]) {
                if (!visited.count(neighbor) && hasCycle(neighbor, visited, recStack))
                    return true;
                else if (recStack.count(neighbor))
                    return true;
            }
        }
        recStack.erase(event);
        return false;
    }

public:
    void addEvent(string name, int date) {
        minHeap.push(Event(name, date));
        if (inDegree.find(name) == inDegree.end()) {
            inDegree[name] = 0;
        }
        cout << "Event added: " << name << " on " << date << endl;
    }

    void addDependency(string from, string to) {
        adjList[from].push_back(to);
        inDegree[to]++;

        unordered_set<string> visited, recStack;
        for (auto &entry : adjList) {
            if (hasCycle(entry.first, visited, recStack)) {
                adjList[from].pop_back();
                inDegree[to]--;
                cout << "Error: This dependency creates a cycle!\n";
                return;
            }
        }

        cout << "Dependency added: " << to << " depends on " << from << endl;
    }

    void viewNextEvent() {
        if (!minHeap.empty()) {
            Event next = minHeap.top();
            cout << "Next Event: " << next.name << " on " << next.date << endl;
        } else {
            cout << "No upcoming events.\n";
        }
    }

    void removeEvent() {
        if (!minHeap.empty()) {
            Event removed = minHeap.top();
            minHeap.pop();
            cout << "Removed Event: " << removed.name << endl;
        } else {
            cout << "No events to remove.\n";
        }
    }

    void viewAllEvents() {
        priority_queue<Event, vector<Event>, Compare> tempHeap = minHeap;
        if (tempHeap.empty()) {
            cout << "No scheduled events.\n";
            return;
        }
        cout << "Scheduled Events:\n";
        while (!tempHeap.empty()) {
            Event e = tempHeap.top();
            tempHeap.pop();
            cout << e.name << " on " << e.date << endl;
        }
    }

    void checkEventOrder() {
        unordered_map<string, int> tempInDegree = inDegree;
        queue<string> q;
        vector<string> eventOrder;

        for (auto &event : tempInDegree) {
            if (event.second == 0) {
                q.push(event.first);
            }
        }

        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            eventOrder.push_back(curr);

            for (string neighbor : adjList[curr]) {
                tempInDegree[neighbor]--;
                if (tempInDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        if (eventOrder.size() == inDegree.size()) {
            cout << "Valid Event Order: ";
            for (string event : eventOrder) {
                cout << event << " -> ";
            }
            cout << "END\n";
        } else {
            cout << "Cycle detected! Some dependencies cannot be resolved.\n";
        }
    }
};

int main() {
    EventScheduler scheduler;
    int choice;
    string name, dep;
    int date;

    while (true) {
        cout << "\nEvent Scheduler:\n";
        cout << "1. Add Event\n2. Add Dependency\n3. View Next Event\n";
        cout << "4. Remove Event\n5. View All Events\n6. Check Event Order\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Event name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Event date (YYYYMMDD): ";
                cin >> date;
                scheduler.addEvent(name, date);
                break;
            case 2:
                cout << "Dependent event: ";
                cin.ignore();
                getline(cin, name);
                cout << "Prerequisite event: ";
                getline(cin, dep);
                scheduler.addDependency(dep, name);
                break;
            case 3:
                scheduler.viewNextEvent();
                break;
            case 4:
                scheduler.removeEvent();
                break;
            case 5:
                scheduler.viewAllEvents();
                break;
            case 6:
                scheduler.checkEventOrder();
                break;
            case 7:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
