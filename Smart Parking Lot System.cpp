#include <iostream>
#include <fstream>
using namespace std;
class Vehicle {
protected:
    string licensePlate;
    string vehicleType;
    int entryTime;
public:
    Vehicle(string plate, string type, int entry):licensePlate(plate),vehicleType(type),entryTime(entry){}
    virtual double calculateFee(int exitTime) = 0;
    string getLicensePlate() const { return licensePlate; }
    string getVehicleType() const { return vehicleType; }
    int getEntryTime() const { return entryTime; }
    virtual ~Vehicle() {}
};
class Bike : public Vehicle {
public:
    Bike(string plate, int entry) : Vehicle(plate, "Bike", entry) {}

    double calculateFee(int exitTime) override {
        int duration = exitTime - entryTime;
        if (duration <= 0) duration = 1;
        return duration * 50.0;
    }
};
class Car : public Vehicle {
public:
    Car(string plate, int entry) : Vehicle(plate, "Car", entry) {}

    double calculateFee(int exitTime) override {
        int duration = exitTime - entryTime;
        if (duration <= 0) duration = 1;
        return duration * 100.0;
    }
};
class Truck : public Vehicle {
public:
    Truck(string plate, int entry) : Vehicle(plate, "Truck", entry) {}

    double calculateFee(int exitTime) override {
        int duration = exitTime - entryTime;
        if (duration <= 0) duration = 1;
        return duration * 200.0;
    }
};
class ParkingSlot {
private:
    int slotID;
    string slotSize;
    bool isOccupied;
    Vehicle* parkedVehicle; 

public:
    ParkingSlot() {
        slotID = 0;
        slotSize = "Medium";
        isOccupied = false;
        parkedVehicle = nullptr;
    }
    
    void setupSlot(int id, string size) {
        slotID = id;
        slotSize = size;
        isOccupied = false;
        parkedVehicle = nullptr;
    }
    
    int getSlotID() const { return slotID; }
    string getSlotSize() const { return slotSize; }
    bool getIsOccupied() const { return isOccupied; }
    Vehicle* getParkedVehicle()const { return parkedVehicle; }

    void occupySlot(Vehicle* v) {
        parkedVehicle = v;
        isOccupied = true;
    }

    void vacateSlot() {
        parkedVehicle = nullptr;
        isOccupied = false;
    }
};
class ParkingPlaza {
private:
    ParkingSlot slots[5]; 
public:
    ParkingPlaza() {
        slots[0].setupSlot(1, "Small");
        slots[1].setupSlot(2, "Medium");
        slots[2].setupSlot(3, "Medium");
        slots[3].setupSlot(4, "Medium");
        slots[4].setupSlot(5, "Large");
    }

    void displayDashboard() const {
        cout << "\n\t\t\t\t\t PARKING LOT REAL-TIME DASHBOARD\n";
        for (int i = 0; i < 5; i++) {
            cout << "[Slot " << slots[i].getSlotID() << " (" << slots[i].getSlotSize() << "): ";
            if (slots[i].getIsOccupied()) {
                cout << "OCCUPIED by " << slots[i].getParkedVehicle()->getVehicleType() 
                     << " (" << slots[i].getParkedVehicle()->getLicensePlate() << ")]\n";
            } else {
                cout << "EMPTY]\n";
            }
        }
        cout << "===========================================\n";
    }

    bool parkVehicle(Vehicle* v) {
        string requiredSize;
        if (v->getVehicleType() == "Bike") requiredSize = "Small";
        else if (v->getVehicleType() == "Car") requiredSize = "Medium";
        else if (v->getVehicleType() == "Truck") requiredSize = "Large";

        for (int i = 0; i < 5; i++) {
            if (!slots[i].getIsOccupied()) {
                bool sizeMatches = false;
                if (requiredSize == "Small") sizeMatches = true; 
                if (requiredSize == "Medium" && (slots[i].getSlotSize() == "Medium" || slots[i].getSlotSize() == "Large")) sizeMatches = true;
                if (requiredSize == "Large" && slots[i].getSlotSize() == "Large") sizeMatches = true;
                if (requiredSize == "Small" && slots[i].getSlotSize() == "Small") sizeMatches = true; 

                if (sizeMatches) {
                    slots[i].occupySlot(v);
                    cout << "\nSuccess: " << v->getVehicleType() << " parked in Slot " << slots[i].getSlotID() << endl;
                    return true;
                }
            }
        }
        cout << "\nError: No suitable empty slot available for this " << v->getVehicleType() << "!\n";
        return false;
    }

    void checkoutVehicle(string plate, int exitTime) {
        for (int i = 0; i < 5; i++) {
            if (slots[i].getIsOccupied() && slots[i].getParkedVehicle()->getLicensePlate() == plate) {
                Vehicle* v = slots[i].getParkedVehicle();
                double fee = v->calculateFee(exitTime);
                int duration = exitTime - v->getEntryTime();
                if (duration <= 0) duration = 1;

                cout << "\n--- Processing Checkout ---";
                cout << "\nVehicle Type : " << v->getVehicleType();
                cout << "\nLicense Plate: " << v->getLicensePlate();
                cout << "\nTotal Hours  : " << duration << " hours";
                cout << "\nTotal Fee    : PKR " << fee;
                cout << "\n---------------------------";
                cout << "\nSlot " << slots[i].getSlotID() << " is now FREE.\n";

                 ofstream revenueFile("revenue_log.txt", ios::app);
                
                if (revenueFile.is_open()) {
                    revenueFile << "Plate: " << v->getLicensePlate() 
                                << " | Type: " << v->getVehicleType() 
                                << " | Hours: " << duration 
                                << " | Earned: PKR " << fee << "\n";
                    
                    revenueFile.close(); 
                    cout << "(Transaction successfully logged to revenue_log.txt)\n";
                } else {
                    cout << "(Warning: Could not open revenue file to log transaction!)\n";
                }

                delete v; 
                slots[i].vacateSlot();
                return;
            }
        }
        cout << "\nError: Vehicle with plate " << plate << " not found in the parking lot.\n";
    }

    ~ParkingPlaza() {
        for (int i = 0; i < 5; i++) {
            if (slots[i].getIsOccupied()) {
                delete slots[i].getParkedVehicle();
            }
        }
    }
};
int main() {
    ParkingPlaza plaza;
    string plate;
    int entry, exit, type, choice;

    while (true) {
        plaza.displayDashboard();
        cout << "\n1. Park a Vehicle\n2. Checkout a Vehicle\n3. View Revenue Log (Read File)\n4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Vehicle Type (1 for Bike, 2 for Car, 3 for Truck): ";
            cin >> type;
            cout << "Enter License Plate: ";
            cin >> plate;
            cout << "Enter Entry Hour (0-23): ";
            cin >> entry;

            Vehicle* newVehicle = nullptr;
            if (type == 1) newVehicle = new Bike(plate, entry);
            else if (type == 2) newVehicle = new Car(plate, entry);
            else if (type == 3) newVehicle = new Truck(plate, entry);
            else {
                cout << "Invalid Type!\n";
                continue;
            }
            
            if (!plaza.parkVehicle(newVehicle))  delete newVehicle;
    }

         else if (choice == 2) {
            cout << "Enter License Plate to checkout: ";
            cin >> plate;
            cout << "Enter Exit Hour (0-23): ";
            cin >> exit;
            plaza.checkoutVehicle(plate, exit);
		}else if (choice==3){
			ifstream readFile("revenue_log.txt");
            string line;

            cout << "\n========= HISTORICAL REVENUE LOG =========\n";
            if (readFile.is_open()) {
                int recordCount = 0;
                while (getline(readFile, line)) {
                    cout << line << endl;
                    recordCount++;
                }
                if (recordCount == 0) {
                    cout << "Log file is empty. No transactions yet.\n";
                }
                readFile.close();
            } else {
                cout << "No history found! (File does not exist yet).\n";
            }
            cout << "==========================================\n";
        } else if (choice == 4) {
            cout << "\nExiting System. Goodbye!\n";
            break;
        } else {
            cout << "Invalid Choice!\n";
        }
    }
    return 0;
}
