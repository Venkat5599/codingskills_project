#include <bits/stdc++.h>
using namespace std;

struct Customer {
    int id;
    string name;
    int serviceTime;
    
    Customer(int id, string name, int serviceTime) 
        : id(id), name(name), serviceTime(serviceTime) {}
};

class BankQueueSimulation {
private:
    queue<Customer> serviceQueue;
    int customerCount;
    int totalWaitTime;
    int processedCustomers;
    
public:
    BankQueueSimulation() : customerCount(0), totalWaitTime(0), processedCustomers(0) {}
    
    void addCustomer(string name, int serviceTime) {
        customerCount++;
        Customer cust(customerCount, name, serviceTime);
        serviceQueue.push(cust);
        cout << "Customer " << name << " (ID: " << customerCount << ") joined queue. Queue size: " << serviceQueue.size() << endl;
    }
    
    void serveCustomer() {
        if (serviceQueue.empty()) {
            cout << "Queue is empty! No customers to serve." << endl;
            return;
        }
        
        Customer cust = serviceQueue.front();
        serviceQueue.pop();
        
        totalWaitTime += cust.serviceTime;
        processedCustomers++;
        
        cout << "\n>>> Serving Customer: " << cust.name << " (ID: " << cust.id << ")" << endl;
        cout << "    Service Time: " << cust.serviceTime << " minutes" << endl;
        cout << "    Remaining in queue: " << serviceQueue.size() << endl;
    }
    
    void displayQueue() {
        if (serviceQueue.empty()) {
            cout << "\nQueue is empty!" << endl;
            return;
        }
        
        cout << "\n Current Queue " << endl;
        queue<Customer> temp = serviceQueue;
        int position = 1;
        
        while (!temp.empty()) {
            Customer cust = temp.front();
            temp.pop();
            cout << "Position " << position << ": " << cust.name << " (Service Time: " 
                 << cust.serviceTime << " min)" << endl;
            position++;
        }
    }
    
    int getQueueSize() {
        return serviceQueue.size();
    }
    
    void displayStatistics() {
        cout << "\n SIMULATION STATISTICS " << endl;
        cout << "Total Customers Processed: " << processedCustomers << endl;
        cout << "Customers Still in Queue: " << serviceQueue.size() << endl;
        cout << "Total Service Time: " << totalWaitTime << " minutes" << endl;
        
        if (processedCustomers > 0) {
            cout << "Average Service Time: " << (float)totalWaitTime / processedCustomers << " minutes" << endl;
        }
    }
    
    void simulateRandomCustomers(int count) {
        cout << "\n--- Adding " << count << " Random Customers ---" << endl;
        string names[] = {"Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Henry"};
        
        for (int i = 0; i < count; i++) {
            string name = names[rand() % 8];
            int serviceTime = 2 + rand() % 10;
            addCustomer(name, serviceTime);
        }
    }
};

void displayMenu() {
    cout << "\n BANK QUEUE SIMULATION " << endl;
    cout << "1. Add Customer Manually" << endl;
    cout << "2. Add Random Customers" << endl;
    cout << "3. Serve Next Customer" << endl;
    cout << "4. Display Queue" << endl;
    cout << "5. Show Statistics" << endl;
    cout << "6. Process All Customers" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
    srand(time(0));
    BankQueueSimulation bank;
    int choice;
    
    cout << "\n Welcome to Bank Queue Simulation System \n" << endl;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                string name;
                int serviceTime;
                cout << "Enter customer name: ";
                getline(cin, name);
                cout << "Enter service time (minutes): ";
                cin >> serviceTime;
                bank.addCustomer(name, serviceTime);
                break;
            }
            
            case 2: {
                int count;
                cout << "How many random customers to add? ";
                cin >> count;
                bank.simulateRandomCustomers(count);
                break;
            }
            
            case 3: {
                bank.serveCustomer();
                break;
            }
            
            case 4: {
                bank.displayQueue();
                break;
            }
            
            case 5: {
                bank.displayStatistics();
                break;
            }
            
            case 6: {
                cout << "\n Processing All Customers " << endl;
                while (bank.getQueueSize() > 0) {
                    bank.serveCustomer();
                }
                cout << "All customers have been served!" << endl;
                bank.displayStatistics();
                break;
            }
            
            case 7: {
                cout << "\nThank you for using Bank Queue Simulation!" << endl;
                return 0;
            }
            
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}
