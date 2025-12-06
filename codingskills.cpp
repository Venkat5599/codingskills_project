#include <bits/stdc++.h>
using namespace std;

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

string currentUser;
string currentRole;

bool login() {
    string inUser, inPass;
    
    cout << "USERNAME: ";
    cin >> inUser;
    cout << "PASSWORD: ";
    cin >> inPass;

    ifstream fp(CRE_FILE);
    if (!fp.is_open()) {
        cout << "Credential file missing!" << endl;
        return false;
    }

    string u, p, r;
    while (fp >> u >> p >> r) {
        if (inUser == u && inPass == p) {
            currentUser = u;
            currentRole = r;
            fp.close();
            return true;
        }
    }

    fp.close();
    return false;
}

void addStudent() {
    int roll;
    string name;
    float mark;

    cout << "Roll: ";
    cin >> roll;
    cout << "Name: ";
    cin >> name;
    cout << "Mark: ";
    cin >> mark;

    ofstream fp(STUD_FILE, ios::app);
    if (!fp.is_open()) {
        cout << "Error: Cannot write to student file!" << endl;
        return;
    }
    fp << roll << " " << name << " " << fixed;
    fp.precision(2);
    fp << mark << endl;
    fp.close();

    cout << "Student added!" << endl;
}

void displayStudents() {
    ifstream fp(STUD_FILE);
    if (!fp.is_open()) {
        cout << "No student file!" << endl;
        return;
    }

    int roll;
    string name;
    float mark;

    cout << "Roll\tName\tMark" << endl;
    cout << "----\t----\t----" << endl;
    while (fp >> roll >> name >> mark) {
        cout << roll << "\t" << name << "\t" << fixed;
        cout.precision(2);
        cout << mark << endl;
    }

    fp.close();
}

void searchStudent() {
    int find;
    cout << "Enter roll to search: ";
    cin >> find;

    ifstream fp(STUD_FILE);
    if (!fp.is_open()) {
        cout << "No student file!" << endl;
        return;
    }

    int roll;
    string name;
    float mark;

    while (fp >> roll >> name >> mark) {
        if (roll == find) {
            cout << "Found: " << roll << " " << name << " " << fixed;
            cout.precision(2);
            cout << mark << endl;
            fp.close();
            return;
        }
    }
    fp.close();
    cout << "Student not found!" << endl;
}

void deleteStudent() {
    int delRoll;
    cout << "Enter roll to delete: ";
    cin >> delRoll;

    ifstream fp(STUD_FILE);
    if (!fp.is_open()) {
        cout << "No student file!" << endl;
        return;
    }

    ofstream temp("temp.txt");
    if (!temp.is_open()) {
        cout << "Error creating temp file!" << endl;
        fp.close();
        return;
    }

    int roll;
    string name;
    float mark;
    bool found = false;

    while (fp >> roll >> name >> mark) {
        if (roll != delRoll) {
            temp << roll << " " << name << " " << fixed;
            temp.precision(2);
            temp << mark << endl;
        } else {
            found = true;
        }
    }

    fp.close();
    temp.close();

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) cout << "Student deleted!" << endl;
    else cout << "Roll not found!" << endl;
}

void updateStudent() {
    int updateRoll;
    cout << "Enter roll to update: ";
    cin >> updateRoll;

    ifstream fp(STUD_FILE);
    if (!fp.is_open()) {
        cout << "No student file!" << endl;
        return;
    }

    ofstream temp("temp.txt");
    if (!temp.is_open()) {
        cout << "Error creating temp file!" << endl;
        fp.close();
        return;
    }

    int roll;
    string name;
    float mark;
    bool found = false;

    while (fp >> roll >> name >> mark) {
        if (roll == updateRoll) {
            found = true;
            string newName;
            float newMark;

            cout << "New Name: ";
            cin >> newName;
            cout << "New Mark: ";
            cin >> newMark;

            temp << roll << " " << newName << " " << fixed;
            temp.precision(2);
            temp << newMark << endl;
        } else {
            temp << roll << " " << name << " " << fixed;
            temp.precision(2);
            temp << mark << endl;
        }
    }

    fp.close();
    temp.close();

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) cout << "Student updated!" << endl;
    else cout << "Roll not found!" << endl;
}

void adminMenu() {
    int c;
    while (true) {
        cout << "\nADMIN MENU" << endl;
        cout << "1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Logout" << endl;
        cin >> c;
        switch(c) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            default: return;
        }
    }
}

void staffMenu() {
    int c;
    while (true) {
        cout << "\nSTAFF MENU" << endl;
        cout << "1.Add\n2.Display\n3.Search\n4.Update\n5.Logout" << endl;
        cin >> c;
        switch(c) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            default: return;
        }
    }
}

void guestMenu() {
    int c;
    while (true) {
        cout << "\nGUEST MENU" << endl;
        cout << "1.Display\n2.Search\n3.Logout" << endl;
        cin >> c;
        switch(c) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            default: return;
        }
    }
}

int main() {
    if (!login()) {
        cout << "Invalid login!" << endl;
        return 0;
    }

    cout << "Logged in as: " << currentRole << endl;

    if (currentRole == "ADMIN") adminMenu();
    else if (currentRole == "STAFF") staffMenu();
    else guestMenu();

    return 0;
}
