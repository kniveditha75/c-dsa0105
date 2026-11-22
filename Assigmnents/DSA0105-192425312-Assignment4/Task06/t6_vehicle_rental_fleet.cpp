#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

// Task 6: Design Challenge — Vehicle Rental Fleet

class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool rented;

public:
    Vehicle(const std::string& reg, double rate) : regNo(reg), dailyRate(rate), rented(false) {}
    virtual ~Vehicle() = default;

    std::string getRegNo() const { return regNo; }
    bool isRented() const { return rented; }
    void setRented(bool r) { rented = r; }

    virtual double computeCharge(int days, int lateDays) const = 0;
    virtual void printDetails() const = 0;
};

class MotorVehicle : public Vehicle {
protected:
    double fuelLevel; // percentage or litres
    std::string serviceDueDate;

public:
    MotorVehicle(const std::string& reg, double rate, double fuel, const std::string& service)
        : Vehicle(reg, rate), fuelLevel(fuel), serviceDueDate(service) {}
};

class Car : public MotorVehicle {
    int seatingCapacity;

public:
    Car(const std::string& reg, double rate, double fuel, const std::string& service, int seats)
        : MotorVehicle(reg, rate, fuel, service), seatingCapacity(seats) {}

    double computeCharge(int days, int lateDays) const override {
        double base = days * dailyRate;
        double latePenalty = lateDays * (dailyRate * 1.5);
        return base + latePenalty;
    }

    void printDetails() const override {
        std::cout << "Car [Reg: " << regNo << ", Rate: Rs " << dailyRate << "/day, Seats: " << seatingCapacity 
                  << ", Rented: " << (rented ? "Yes" : "No") << "]\n";
    }
};

class ElectricCar : public Vehicle {
    double batteryCapacity; // kWh

public:
    ElectricCar(const std::string& reg, double rate, double battery)
        : Vehicle(reg, rate), batteryCapacity(battery) {}

    double computeCharge(int days, int lateDays) const override {
        double base = days * dailyRate;
        double chargingFee = batteryCapacity * 15.0; // Rs 15 per kWh
        double latePenalty = lateDays * (dailyRate * 1.5);
        return base + chargingFee + latePenalty;
    }

    void printDetails() const override {
        std::cout << "ElectricCar [Reg: " << regNo << ", Rate: Rs " << dailyRate << "/day, Battery: " << batteryCapacity 
                  << "kWh, Rented: " << (rented ? "Yes" : "No") << "]\n";
    }
};

// Extension: ElectricBus added without changing existing classes
class ElectricBus : public Vehicle {
    int passengerCapacity;
    double batteryCapacity;

public:
    ElectricBus(const std::string& reg, double rate, int passCap, double battery)
        : Vehicle(reg, rate), passengerCapacity(passCap), batteryCapacity(battery) {}

    double computeCharge(int days, int lateDays) const override {
        double base = days * dailyRate;
        double chargingFee = batteryCapacity * 20.0;
        return base + chargingFee + (lateDays * dailyRate * 2.0);
    }

    void printDetails() const override {
        std::cout << "ElectricBus [Reg: " << regNo << ", Rate: Rs " << dailyRate << "/day, Capacity: " << passengerCapacity 
                  << " passengers, Rented: " << (rented ? "Yes" : "No") << "]\n";
    }
};

int main() {
    std::cout << "=== TASK 6: VEHICLE RENTAL FLEET DEMONSTRATION ===\n";
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Car>("TN-01-AB-1234", 2500.0, 85.0, "2026-06-01", 5));
    fleet.push_back(std::make_unique<ElectricCar>("TN-07-EV-9999", 3500.0, 75.0));
    fleet.push_back(std::make_unique<ElectricBus>("TN-22-EB-5555", 8000.0, 40, 250.0)); // Extension

    for (const auto& v : fleet) {
        v->printDetails();
    }

    std::cout << "\n--- Renting and Returning with Late Charges ---\n";
    fleet[0]->setRented(true);
    double charge = fleet[0]->computeCharge(5, 2); // 5 days normal, 2 days late
    std::cout << "Rental charge for Car (5 days + 2 late days): Rs " << std::fixed << std::setprecision(2) << charge << '\n';

    double evCharge = fleet[1]->computeCharge(3, 0); // 3 days electric car
    std::cout << "Rental charge for ElectricCar (3 days): Rs " << std::fixed << std::setprecision(2) << evCharge << '\n';
    return 0;
}
