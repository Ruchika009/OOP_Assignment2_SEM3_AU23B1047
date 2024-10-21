#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
class Management {
public:
virtual void display() = 0; // Pure virtual function, to be overridden by derived classes
};
class Inventory : public Management {
public:
string medicine_name[100];
int quantity[100];
int price[100];
int expiry_year[100];
int count;
Inventory() {
count = 0;
}
void add_medicine(string mname, int quan, int pri, int exyear) {
try {
if (quan <= 0 || pri <= 0 || exyear <= 0) {
throw invalid_argument("Quantity, price, and expiry year must be positive.");
}
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
throw overflow_error("Inventory full. Cannot add more medicines.");
}
}
}
catch (const exception& e) {
cout << "Error: " << e.what() << endl;
}
}
void remove_medicine(string mname, int quan) {
try {
if (quan <= 0) {
throw invalid_argument("Quantity to remove must be positive.");
}
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
throw out_of_range("Entered quantity is greater than available quantity.");
}
break;
}
}
if (!exists) {
throw out_of_range("Medicine not found in inventory.");
}
}
catch (const exception& e) {
cout << "Error: " << e.what() << endl;
}
}
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
try {
if (id <= 0 || ag <= 0) {
throw invalid_argument("Patient ID and age must be positive.");
}
if (count >= 100) {
throw overflow_error("Cannot add more patients. Database is full.");
}
patient_id[count] = id;
patient_name[count] = name;
age[count] = ag;
gender[count] = gend;
admitted_date[count] = ad_date;
count++;
cout << "Added..!!" << endl;
}
catch (const exception& e) {
cout << "Error: " << e.what() << endl;
}
}
void update_patientdetails(int id) {
try {
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
throw invalid_argument("Invalid option entered.");
}
cout << "Patient ID " << patient_id[i] << " is updated from data." << endl;
break;
}
}
if (!exists) {
throw out_of_range("Patient not found.");
}
}
catch (const exception& e) {
cout << "Error: " << e.what() << endl;
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
class Billing : public Admin {
private:
int patient_id[100];
string patient_name[100];
string treatment[100];
int payment[100];
int count = 0;
public:
void add_billingInfo(int id, string name, string treat, int pay) {
try {
if (id <= 0 || pay < 0) {
throw invalid_argument("Patient ID must be positive and payment cannot be negative.");
}
if (count >= 100) {
throw overflow_error("Cannot add more billing details. Database is full.");
}
patient_id[count] = id;
patient_name[count] = name;
treatment[count] = treat;
payment[count] = pay;
count++;
cout << "Added successfully to Billing Database...!!" << endl;
}
catch (const exception& e) {
cout << "Error: " << e.what() << endl;
}
}
void isPaymentcomplete(int id) {
try {
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
throw out_of_range("Patient not found in Billing database.");
}
}
catch (const exception& e) {
cout << "Error: " << e.what() << endl;
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
class Insurance : public Admin, public Billing {
private:
int patient_id[100];
string patient_name[100];
string policy_holder[100];
string policy[100];
int count = 0;
public:
void add_Policy(int id, string patient, string holder, string pol) {
bool exists = false;
for (int i = 0; i < count; i++) {
if (patient_id[i] == id) {
exists = true;
cout << "Policy already exists for Patient ID: " << id << ". Updating policy..." << endl;
policy[i] = pol;
return;
}
}
if (!exists && count < 100) {
Billing::display_billingdetail();
patient_id[count] = id;
patient_name[count] = patient;
policy_holder[count] = holder;
count++;
cout << "Policy added successfully for Patient ID: " << id << endl;
} else if (count >= 100) {
cout << "Error: Maximum policy limit reached. Cannot add more policies." << endl;
}
}
void display_Policydetails() {
if (count == 0) {
cout << "No patient policy details available." << endl;
return;
}
cout << "Policy details stored:" << endl;
for (int i = 0; i < count; i++) {
cout << "--------------------------------" << endl;
cout << "Patient ID: " << patient_id[i] << endl;
cout << "Patient Name: " << patient_name[i] << endl;
cout << "Policy Holder: " << policy_holder[i] << endl;
cout << "Policy: " << policy[i] << endl;
//Billing::display_billingdetail();
cout << "--------------------------------" << endl;
}
}
void add_insurancedetail(int id, string name, string pol, string phold) {
try {
if (id <= 0) {
throw invalid_argument("Patient ID must be positive.");
}
if (count >= 100) {
throw overflow_error("Cannot add more insurance details. Database is full.");
}
patient_id[count] = id;
patient_name[count] = name;
policy[count] = pol;
policy_holder[count] = phold;
count++;
cout << "Insurance details successfully added..!!" << endl;
}
catch (const exception& e) {
cout << "Error: " << e.what() << endl;
}
}
void display_insurancedetail() {
if (count == 0) {
cout << "No insurance details available." << endl;
return;
}
cout << "Insurance details stored:" << endl;
for (int i = 0; i < count; i++) {
cout << "--------------------------------" << endl;
cout << "Patient ID: " << patient_id[i] << endl;
cout << "Patient Name: " << patient_name[i] << endl;
cout << "Policy: " << policy[i] << endl;
cout << "Policy Holder: " << policy_holder[i] << endl;
cout << "--------------------------------" << endl;
}
}
};
class R_and_D {
private:
string covid_symptoms[5] = {"cough", "cold", "fever", "muscle ache", "loss of taste or smell"};
int patient_id[100];
string symptom[100];
int count = 0;
public:
void add_patient_symptom(int id, string sy) {
patient_id[count] = id;
symptom[count] = sy;
count++;
}
void identify_symptom(int id) {
bool patient_found = false;
for (int i = 0; i < count; i++) {
if (patient_id[i] == id) {
patient_found = true;
bool is_covid_symptom = false;
for (int j = 0; j < 5; j++) {
if (symptom[i] == covid_symptoms[j]) {
is_covid_symptom = true;
break;
}
}
if (is_covid_symptom) {
cout << "Patient ID " << id << " has a COVID-related symptom." << endl;
} else {
cout << "Patient ID " << id << " does not have a COVID- related symptom." << endl;
}
break;
}
}
if (!patient_found) {
cout << "Patient ID not found." << endl;
}
}
};
int main() {
int main_option;
cout<<"********Welcome to Hospital Management System*********"<<endl;
do {
cout << "\n1. Inventory Management\n2. Patient Administration\n3. Billing Management\n4. Insurance Management\n5. R&D - Symptoms Management\n6. Exit\n";
cout << "Enter option to proceed: ";
cin >> main_option;
if (main_option == 1) {
Inventory I;
int choice, n, quan, pri, exyear;
string mediname;
do {
cout << "\n1. Add Medicine\n2. Remove Medicine\n3. Display Inventory\n4. Back to Main Menu\n";
cout << "Enter your choice: ";
cin >> choice;
if (choice == 1) {
cout << "Enter number of medicines to be added: ";
cin >> n;
for (int i = 0; i < n; i++) {
cout << "Enter name of medicine: ";
cin >> mediname;
cout << "Enter quantity: ";
cin >> quan;
cout << "Enter price: ";
cin >> pri;
// /cout << "Enter expiry year: ";
// /cin >> exyear;
while (true) {
cout << "Enter expiry year: ";
string expiryyear_str;
cin >> expiryyear_str;
try {
exyear = stoi(expiryyear_str);
if (exyear >= 2024 && exyear <= 2032) {
break;
} else {
cout << "Invalid expiry year. Please enter a year between 2024 and 2032." << endl;
}
} catch (const invalid_argument& ia) {
cout << "Invalid input. Please enter a numeric value."
<< endl;
}
}
I.add_medicine(mediname, quan, pri, exyear);
}
} else if (choice == 2) {
cout << "Enter name of medicine to remove: ";
cin >> mediname;
cout << "Enter quantity to remove: ";
cin >> quan;
I.remove_medicine(mediname, quan);
} else if (choice == 3) {
I.display();
} else if (choice != 4) {
cout << "Invalid choice. Please try again.\n";
}
} while (choice != 4);
} else if (main_option == 2) {
Admin A;
int choice, id, age;
string name, gender, date;
do {
cout << "\n1. Add Patient Details\n2. Update Patient Details\n3. Display Patient Details\n4. Back to Main Menu\n";
cout << "Enter your choice: ";
cin >> choice;
if (choice == 1) {
cout << "Enter patient ID: ";
cin >> id;
cout << "Enter patient name: ";
cin >> name;
cout << "Enter patient age: ";
cin >> age;
cout << "Enter gender: ";
cin >> gender;
cout << "Enter admitted date (YYYY-MM-DD): ";
cin >> date;
A.add_patient(id, name, age, gender, date);
} else if (choice == 2) {
cout << "Enter patient ID to update: ";
cin >> id;
A.update_patientdetails(id);
} else if (choice == 3) {
A.display();
} else if (choice != 4) {
cout << "Invalid choice. Please try again.\n";
}
} while (choice != 4);
} else if (main_option == 3) {
Billing B;
int choice, id, pay;
string patient, treat, date;
do {
cout << "\n1. Add Patient Billing Details\n2. Check Payment Status\
n3. Display Billing Details\n4. Back to Main Menu\n";
cout << "Enter your choice: ";
cin >> choice;
if (choice == 1) {
cout << "Enter patient ID: ";
cin >> id;
cout << "Enter patient name: ";
cin >> patient;
cout << "Enter payment: ";
cin >> pay;
cout << "Enter treatment: ";
cin >> treat;
B.add_billingInfo(id, patient, treat, pay);
} else if (choice == 2) {
cout << "Enter patient ID: ";
cin >> id;
B.isPaymentcomplete(id);
} else if (choice == 3) {
B.display_billingdetail();
} else if (choice != 4) {
cout << "Invalid choice. Please try again.\n";
}
} while (choice != 4);
} else if (main_option == 4) {
Insurance I;
int choice, id;
string patient, policy, holder;
do {
cout << "\n1. Add Patient Policy Details\n2. Display Policy Details\n3. Back to Main Menu\n";
cout << "Enter your choice: ";
cin >> choice;
if (choice == 1) {
cout << "Enter patient ID: ";
cin >> id;
cout << "Enter patient name: ";
cin >> patient;
cout << "Enter policy holder name: ";
cin >> holder;
cout << "Enter policy name: ";
cin >> policy;
I.add_Policy(id, patient, holder, policy);
} else if (choice == 2) {
I.display_Policydetails();
} else if (choice != 3) {
cout << "Invalid choice. Please try again.\n";
}
} while (choice != 3);
} else if (main_option == 5) {
R_and_D R;
int choice, id;
string sym;
do {
cout << "\n1. Add Patient Symptom Details\n2. Check patient with COVID symptoms\n3. Back to Main Menu\n";
cout << "Enter your choice: ";
cin >> choice;
if (choice == 1) {
cout << "Enter patient ID: ";
cin >> id;
cout << "Enter symptoms: ";
cin >> sym;
R.add_patient_symptom(id, sym);
} else if (choice == 2) {
cout << "Enter patient ID: ";
cin >> id;
R.identify_symptom(id);
} else if (choice != 3) {
cout << "Invalid choice. Please try again.\n";
}
} while (choice != 3);
} else if (main_option != 6) {
cout << "Invalid option. Please try again.\n";
}
} while (main_option != 6);
cout << "Exiting program.\n";
return 0;
}