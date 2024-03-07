#include <iostream>
#include <fstream>
using namespace std;

class hostel {
    int room_no;
    char name[30];
    char address[50];
    char phone[10];
public:
    // Function to display the main menu
    int main_menu();
    
    // Function to add a new customer record
    int add();
    
    // Function to display customer details based on room number
    int display();
    
    // Function to display all rooms and their occupants
    int rooms();
    
    // Function to edit customer record
    int edit();
    
    // Function to check if a room is already booked
    int check(int);
    
    // Function to modify customer record
    int modify(int);
    
    // Function to delete a customer record
    int delete_rec(int);
};

// Main menu function implementation
int hostel::main_menu() {
    int choice = 0;
    while (choice != 5) {
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\n\t\t\t1. Allot A Room";
        cout << "\n\t\t\t2. Display Student Record";
        cout << "\n\t\t\t3. Display Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            add();
            break;
        case 2:
            display();
            break;
        case 3:
            rooms();
            break;
        case 4:
            edit();
            break;
        case 5:
            break;
        default:
            cout << "\n\n\t\t\tWrong choice!!!";
            cout << "\n\t\t\tPress any key to continue!!";
            return 0;
        }
    }
    return 0;
}

// Function to add a new customer record
int hostel::add() {
    int r, flag;
    ofstream fout("Record.dat", ios::binary | ios::app); // Open file in append mode
    cout << "\n Enter Customer Details";
    cout << "\n **********************";
    cout << "\n\n Room no: ";
    cin >> r;
    flag = check(r);
    if (flag) {
        cout << "\n Sorry..!!! Room is already booked";
    }
    else {
        room_no = r;
        cout << "\n Name:\t ";
        cin >> name;
        cout << "\n Address:\t ";
        cin >> address;
        cout << "\n Phone No:\t ";
        cin >> phone;

        cout << endl;
        fout.write((char*)this, sizeof(*this));
        cout << "\n Room is booked!!!";
    }
    cout << "\n Press any key to continue!!";
    system("pause");
    fout.close();
    return 0;
}

// Function to display customer details based on room number
int hostel::display() {
    ifstream fin("Recor.dat", ios::binary | ios::in);
    int r;
    bool found = false; // Variable to track if the room is found
    cout << "\n Enter room no: ";
    cin >> r;
    
    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            found = true;
            cout << "\n Customer Details";
            cout << "\n ****************";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            break; // Exit loop once the record is found
        }
    }

    fin.close();
    
    if (!found) {
        cout << "\n Sorry Room no. not found or vacant!!";
    }
    cout << "\n\n Press any key to continue!!";
    system("pause");
    
    return 0;
}

// Function to display all rooms and their occupants
int hostel::rooms() {
    ifstream fin("Recor.dat", ios::binary | ios::in);
    cout << "\n\t\t\tList Of Rooms Allotted";
    cout << "\n\t\t\t*********************";
    cout << "\n\n Room No.\tName\t\tAddress\t\tPhoneNo.\n";
    
    bool found = false; // Flag to track if any records are found
    
    while (fin.read((char*)this, sizeof(*this))) {
        // Display details only if room is occupied
        if (room_no != 0) { // Assuming room numbers start from 1
            found = true;
            cout << "\n\n " << room_no << "\t\t" << name;
            cout << "\t\t" << address << "\t\t" << phone;
        }
    }
    
    // If no records were found, display a message
    if (!found) {
        cout << "\n\n No rooms are currently allocated.";
    }
    
    cout << "\n\n\n\t\t\tPress any key to continue!!";
    system("pause");
    fin.close();
    return 0;
}


// Function to edit customer record
int hostel::edit() {
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n *********";
    cout << "\n\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;
    cout << "\n Enter room no: ";
    cin >> r;
    
    switch (choice) {
    case 1:
        modify(r);
        break;
    case 2:
        delete_rec(r);
        break;
    default:
        cout << "\n Wrong Choice!!";
    }

    cout << "\n Press any key to continue!!!";
    system("pause");
    return 0;
}

// Function to check if a room is already booked
int hostel::check(int r) {
    int flag = 0;
    ifstream fin("Recor.dat", ios::in | ios::binary);
    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

// Function to modify customer record
int hostel::modify(int r) {
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n *****************";
            cout << "\n Name: ";
            cin >> name;
            cout << " Address: ";
            cin >> address;
            cout << " Phone no: ";
            cin >> phone;

            file.seekg(pos);
            file.write((char*)this, sizeof(*this));
            cout << "\n Record is modified!!";
            flag = 1;
            break;
        }
        pos = file.tellg();
    }
    if (flag == 0) {
        cout << "\n Sorry Room no. not found or vacant!!";
    }
    file.close();
    return 0;
}

// Function to delete a customer record
int hostel::delete_rec(int r) {
    int flag = 0;
    char ch;
    ifstream fin("Recor.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary);

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n\n Do you want to delete this record(y/n): ";
            cin >> ch;
            if (ch == 'n') {
                fout.write((char*)this, sizeof(*this));
            }
            flag = 1;
        } else {
            fout.write((char*)this, sizeof(*this));
        }
    }

    fin.close();
    fout.close();

    if (flag == 0) {
        cout << "\n Sorry room no. not found or vacant!!";
    } else {
        remove("Recor.dat");
        rename("temp.dat", "Recor.dat");
    }

    return 0;
}

int main() {
    hostel h;
    cout << "\n\t\t\t****************************";
    cout << "\n\t\t\t* HOSTEL MANAGEMENT PROJECT *";
    cout << "\n\t\t\t****************************";

    cout << "\n\n\n\n\n\t\t\t\tPress any key to continue!!";
    system("pause");
    h.main_menu();
    system("pause");
    return 0;
}
