#include <iostream>
#include <string>
using namespace std;

class Management {
public:
    virtual void display() = 0;  // Pure virtual function, to be overridden by derived classesll
};

class Inventory : public Management {
public:
    string medicine_name[100];
    int quantity[100];
    int price[100];
    int expiry_year[100];
    int count;

    // Constructor
    Inventory() { 
        count = 0; 
    }

    // Add medicine to inventory
    void add_medicine(string mname, int quan, int pri, int exyear) {
        bool exists = false;
        for (int i = 0; i < count; i++) {
            if (medicine_name[i] == mname) {
                quantity[i] += quan;
                cout << "Medicine already available in stock. Increased the quantity." << endl;
                exists = true;
                break;
            }
        }
        if (!exists) {
            if (count < 100) {  
                medicine_name[count] = mname;
                quantity[count] = quan;
                price[count] = pri;
                expiry_year[count] = exyear;
                count++;
                cout << "New medicine added successfully." << endl;
            } else {
                cout << "Inventory full. Cannot add more medicines." << endl;
            }
        }
    }

    // Remove medicine from inventory
    void remove_medicine(string mname, int quan) {
        bool exists = false;
        for (int i = 0; i < count; i++) {
            if (medicine_name[i] == mname) {
                exists = true;
                if (quantity[i] >= quan) {
                    quantity[i] -= quan;
                    cout << "The given quantity has been removed from inventory." << endl;
                    if (quantity[i] == 0) {
                        for (int j = i; j < count - 1; j++) {
                            medicine_name[j] = medicine_name[j + 1];
                            quantity[j] = quantity[j + 1];
                            price[j] = price[j + 1];
                            expiry_year[j] = expiry_year[j + 1];
                        }
                        count--;
                        cout << "Medicine " << mname << " is completely removed from inventory." << endl;
                    }
                } else {
                    cout << "Entered quantity is greater than available quantity." << endl;
                }
                break;
            }
        }
        if (!exists) {
            cout << "Medicine not found in inventory." << endl;
        }
    }

    // Display all medicines in the inventory
    void display() override {
        if (count == 0) {
            cout << "No medicines available in inventory." << endl;
            return;
        }
        cout << "Medicines in stock:" << endl;
        for (int i = 0; i < count; i++) {
            cout << "--------------------------------" << endl;
            cout << "Name: " << medicine_name[i] << endl;
            cout << "Quantity: " << quantity[i] << endl;
            cout << "Price: " << price[i] << endl;
            cout << "Expiry Year: " << expiry_year[i] << endl;
            cout << "--------------------------------" << endl;
        }
    }
};

class Admin : public Management {
private:
    int patient_id[100];
    string patient_name[100];
    int age[100];
    string gender[100];
    string admitted_date[100];
    int count;

public:
    Admin() {
        count = 0;
    }

    void add_patient(int id, string name, int ag, string gend, string ad_date) {
        if (count < 100) {
            patient_id[count] = id;
            patient_name[count] = name;
            age[count] = ag;
            gender[count] = gend;
            admitted_date[count] = ad_date;
            count++;
            cout << "Added..!!" << endl;
        }
    }

    void update_patientdetails(int id) {
        bool exists = false;
        int option;
        for (int i = 0; i < count; i++) {
            if (patient_id[i] == id) {
                exists = true;
                cout << "1. Patient Name\n2. Patient Age\n3. Patient Gender\n4. Patient admitted date\nEnter option to update: ";
                cin >> option;
                switch (option) {
                case 1:
                    cout << "Enter name to update: ";
                    cin >> patient_name[i];
                    break;
                case 2:
                    cout << "Enter age to update: ";
                    cin >> age[i];
                    break;
                case 3:
                    cout << "Enter gender to update: ";
                    cin >> gender[i];
                    break;
                case 4:
                    cout << "Enter admitted date to update: ";
                    cin >> admitted_date[i];
                    break;
                default:
                    cout << "Invalid option entered";
                }
                cout << "Patient ID " << patient_id[i] << " is updated from data." << endl;
                break;
            }
        }
        if (!exists) {
            cout << "Patient not found." << endl;
        }
    }

    void display() override {
        if (count == 0) {
            cout << "No patient details available." << endl;
            return;
        }
        cout << "Patient details:" << endl;
        for (int i = 0; i < count; i++) {
            cout << "--------------------------------" << endl;
            cout << "Patient ID: " << patient_id[i] << endl;
            cout << "Patient Name: " << patient_name[i] << endl;
            cout << "Gender: " << gender[i] << endl;
            cout << "Age: " << age[i] << endl;
            cout << "Admitted Date: " << admitted_date[i] << endl;
            cout << "--------------------------------" << endl;
        }
    }
};

class Billing {
private:
    int patient_id[100];
    string patient_name[100];
    string treatment[100];
    int payment[100];
    int count = 0;

public:
    void add_billingInfo(int id, string name, string treat, int pay) {
        if (count < 100) {
            patient_id[count] = id;
            patient_name[count] = name;
            treatment[count] = treat;
            payment[count] = pay;
            count++;
            cout << "Added successfully to Billing Database...!!" << endl;
        }
    }

    void isPaymentcomplete(int id) {
        bool exists = false;
        for (int i = 0; i < count; i++) {
            if (patient_id[i] == id) {
                exists = true;
                int bill = payment[i];
                if (bill != 0) {
                    cout << "The payment of patient ID " << id << " is successfully paid with amount of " << bill << endl;
                } else {
                    cout << "The payment of patient ID " << id << " is not paid." << endl;
                }
            }
        }
        if (!exists) {
            cout << "Patient not found in Billing database." << endl;
        }
    }

    void display_billingdetail() {
        if (count == 0) {
            cout << "No patient billing details available." << endl;
            return;
        }
        cout << "Billing details stored:" << endl;
        for (int i = 0; i < count; i++) {
            cout << "--------------------------------" << endl;
            cout << "Patient ID: " << patient_id[i] << endl;
            cout << "Patient Name: " << patient_name[i] << endl;
            cout << "Treatment: " << treatment[i] << endl;
            cout << "Payment: " << payment[i] << endl;
            cout << "--------------------------------" << endl;
        }
    }
};

int main() {
    int op;
    cout << "\n1. Inventory management" << endl;
    cout << "2. Hospital patient record management" << endl;
    cout << "3. Billing management" << endl;
    cout << "Enter one of the above options: ";
    cin >> op;

    if (op == 1) {
        Inventory I;
        int n, quan, pri, expiryyear;
        string mediname;
        int choice;

        do {
            cout << "\n1. Add Medicine" << endl;
            cout << "2. Remove Medicine" << endl;
            cout << "3. Display Medicines" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter proper choice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter number of medicines to be added: ";
                cin >> n;

                for (int i = 0; i < n; i++) {
                    cout << "Enter name of medicine: ";
                    cin >> mediname;

                    cout << "Enter quantity to be added: ";
                    cin >> quan;

                    cout << "Enter price of medicine: ";
                    cin >> pri;

                    cout << "Enter expiry year: ";
                    cin >> expiryyear;

                    I.add_medicine(mediname, quan, pri, expiryyear);
                }
            } else if (choice == 2) {
                cout << "Enter number of medicines to be removed: ";
                cin >> n;

                for (int i = 0; i < n; i++) {
                    cout << "Enter name of medicine: ";
                    cin >> mediname;

                    cout << "Enter quantity to be removed: ";
                    cin >> quan;

                    I.remove_medicine(mediname, quan);
                }
            } else if (choice == 3) {
                I.display();
            } else if (choice == 4) {
                cout << "Exiting program." << endl;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);

    } else if (op == 2) {
        Admin A;
        int choice, id, age;
        string name, gender, date;

        do {
            cout << "\n1. Add Patient Details" << endl;
            cout << "2. Update Patient Details" << endl;
            cout << "3. Display Patient Details" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter proper choice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter patient ID: ";
                cin >> id;

                cout << "Enter name of patient: ";
                cin >> name;

                cout << "Enter age of patient: ";
                cin >> age;

                cout << "Enter gender of patient: ";
                cin >> gender;

                cout << "Enter admitted date(in YYYY-MM-DD format): ";
                cin >> date;

                A.add_patient(id, name, age, gender, date);
            } else if (choice == 2) {
                cout << "Enter patient ID to update: ";
                cin >> id;

                A.update_patientdetails(id);
            } else if (choice == 3) {
                A.display();
            } else if (choice == 4) {
                cout << "Exiting program." << endl;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);

    } else if (op == 3) {
        Billing B;
        int choice, num, id, pay;
        string patient, treat, date;

        do {
            cout << "\n1. Add Patient Billing Details" << endl;
            cout << "2. Check Patient Payment Status" << endl;
            cout << "3. Display Patient Billing details" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter proper choice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter number of patient details to be added: ";
                cin >> num;

                for (int i = 0; i < num; i++) {
                    cout << "Enter patient ID: ";
                    cin >> id;

                    cout << "Enter name of patient: ";
                    cin >> patient;

                    while (true) {
                        cout << "Enter payment: ";
                        string payment_str;
                        cin >> payment_str;
                        try {
                            pay = stoi(payment_str);
                            break;
                        } catch (const invalid_argument& ia) {
                            cout << "Invalid input. Please enter a numeric value." << endl;
                        }
                    }

                    cout << "Enter treatment of patient: ";
                    cin >> treat;

                    cout << "Enter admitted date (YYYY-MM-DD): ";
                    cin >> date;

                    B.add_billingInfo(id, patient, treat, pay);
                }
            } else if (choice == 2) {
                cout << "Enter patient ID: ";
                cin >> id;
                B.isPaymentcomplete(id);
            } else if (choice == 3) {
                B.display_billingdetail();
            } else if (choice == 4) {
                cout << "Exiting program." << endl;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);
    } else {
        cout << "Invalid option entered.";
    }

    return 0;
}
