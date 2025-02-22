#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    string model;
    double rentalPricePerDay;
    string requiredLicense;

    Vehicle(string model, double price, string license) : model(model), rentalPricePerDay(price), requiredLicense(license) {}
};

class User {
public:
    string userID, name, contactNumber, licenseType;
    int age;
    
    User(string userID, string name, int age, string contact, string license) 
        : userID(userID), name(name), age(age), contactNumber(contact), licenseType(license) {}

    void updateDetails(string newName, int newAge, string newContact, string newLicense) {
        name = newName;
        age = newAge;
        contactNumber = newContact;
        licenseType = newLicense;
    }
};

class RentalSystem {
private:
    Vehicle* vehicles[100]; 
    int vehicleCount;

public:
    RentalSystem() : vehicleCount(0) {}

    void addVehicle(string model, double price, string license) {
        if (vehicleCount < 100) {
            vehicles[vehicleCount++] = new Vehicle(model, price, license);
        }
    }

    void showVehicles() {
        cout << "Available Vehicles:\n";
        for (int i = 0; i < vehicleCount; i++) {
            cout << i + 1 << ". Model: " << vehicles[i]->model << ", Price: $" << vehicles[i]->rentalPricePerDay 
                 << ", Required License: " << vehicles[i]->requiredLicense << "\n";
        }
    }

    void rentVehicle(User& user, int choice) {
        if (choice < 1 || choice > vehicleCount) {
            cout << "Invalid selection.\n";
            return;
        }

        Vehicle* selectedVehicle = vehicles[choice - 1];
        if (user.licenseType == selectedVehicle->requiredLicense || user.licenseType == "Full") {
            cout << "Rental successful! You rented: " << selectedVehicle->model << " for $" << selectedVehicle->rentalPricePerDay << "/day\n";
        } else {
            cout << "You are not eligible to rent this vehicle.\n";
        }
    }

    ~RentalSystem() {
        for (int i = 0; i < vehicleCount; i++) {
            delete vehicles[i];
        }
    }
};

int main() {
    RentalSystem system;
    system.addVehicle("Toyota Corolla", 30, "Full");
    system.addVehicle("Honda Civic", 28, "Intermediate");
    system.addVehicle("Suzuki Swift", 25, "Learner");
    
    User user("U001", "John Doe", 25, "1234567890", "Intermediate");
    
    cout << "Welcome, " << user.name << "!" << endl;
    system.showVehicles();

    // cout << "Enter the vehicle number to rent: ";
    // int choice;
    // cin >> choice;
    // Hardcoded
    system.rentVehicle(user, 2);
    
    return 0;
    
}