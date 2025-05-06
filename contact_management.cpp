#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Contact {
public:
    string name;
    string phone;
    string email;

    void input() {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter phone: ";
        getline(cin, phone);
        cout << "Enter email: ";
        getline(cin, email);
    }

    void display() const {
        cout << left << setw(20) << name << setw(15) << phone << setw(25) << email << endl;
    }

    string to_string() const {
        return name + "," + phone + "," + email + "\n";
    }
};

vector<Contact> load_contacts() {
    vector<Contact> contacts;
    ifstream file("contacts.txt");
    string line;
    while (getline(file, line)) {
        Contact c;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        c.name = line.substr(0, pos1);
        c.phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        c.email = line.substr(pos2 + 1);
        contacts.push_back(c);
    }
    file.close();
    return contacts;
}

void save_contacts(const vector<Contact>& contacts) {
    ofstream file("contacts.txt");
    for (const auto& c : contacts)
        file << c.to_string();
    file.close();
}

void display_contacts(const vector<Contact>& contacts) {
    cout << left << setw(20) << "Name" << setw(15) << "Phone" << setw(25) << "Email" << endl;
    cout << string(60, '-') << endl;
    for (const auto& c : contacts)
        c.display();
}

int main() {
    vector<Contact> contacts = load_contacts();
    int choice;
    do {
        cout << "\n1. Add Contact\n2. View Contacts\n3. Delete Contact\n4. Update Contact\n5. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            Contact c;
            c.input();
            contacts.push_back(c);
            save_contacts(contacts);
        } else if (choice == 2) {
            display_contacts(contacts);
        } else if (choice == 3) {
            string name;
            cout << "Enter name to delete: ";
            getline(cin, name);
            auto it = remove_if(contacts.begin(), contacts.end(), [&](Contact& c) { return c.name == name; });
            contacts.erase(it, contacts.end()); // Correctly erase the contacts
            save_contacts(contacts);
        } else if (choice == 4) {
            string name;
            cout << "Enter name to update: ";
            getline(cin, name);
            for (auto& c : contacts) {
                if (c.name == name) {
                    cout << "Enter new details:\n";
                    c.input();
                    break;
                }
            }
            save_contacts(contacts);
        }
    } while (choice != 5);
    return 0;
}