#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TransportCard {
private:
    string cardID;
    bool isActive;

public:

    TransportCard(string id) : cardID(id), isActive(false) {}

    void activateCard() { isActive = true; }

    void deactivateCard() { isActive = false; }

    bool getStatus() const { return isActive; }

};


class BusStop {

private:
    string stopID;
    string location;

public:

    BusStop(string id, string loc) : stopID(id), location(loc) {}

    string getStopInfo() const { return location; }

};


class BusRoute {

private:
    string routeID;
    vector<BusStop> stops;

public:

    BusRoute(string id) : routeID(id) {}

    void addStop(BusStop stop) { stops.push_back(stop); }

};


class Bus {

private:
    string busID;
    BusRoute* assignedRoute;


public:
    Bus(string id) : busID(id), assignedRoute(nullptr) {}
    void assignRoute(BusRoute* route) { assignedRoute = route; }


};

class Attendance {

public:
    static void recordTap(string studentID) {
        cout << "Attendance recorded for student: " << studentID << endl;
    }
};


class Student {

private:
    string studentID;
    string name;
    TransportCard card;
    string assignedStop;

public:

    Student(string id, string n, string cardID, string stop) : studentID(id), name(n), card(cardID), assignedStop(stop) {}

    void registerForTransport() { cout << name << " registered for transport.\n"; }

    void paySemesterFee() { card.activateCard(); cout << name << "'s transport card is now active.\n"; }

    void tapCard() {
        if (card.getStatus()) {
            Attendance::recordTap(studentID);
        } else {
            cout << "Card inactive. Please pay semester fee.\n";
        }
    }
    
};

int main() {
    BusStop stop1("S1", "Gate 1");
    BusStop stop2("S2", "Library");
    
    BusRoute route("R1");
    route.addStop(stop1);
    route.addStop(stop2);
    
    Bus bus("B1");
    bus.assignRoute(&route);
    
    Student student("123", "Ali", "C001", "Gate 1");
    student.registerForTransport();
    student.paySemesterFee();
    student.tapCard();
    
    return 0;
}
