#include "HotDogStand.h"

// Constructor implementation
HotDogStandsClass::HotDogStandsClass(std::string id, std::string loc, double cost, int totalSold, int inventory, int soldCount) {
    this->identification = id;
    this->location = loc;
    this->costPerHotdog = cost;
    this->totalHotdogsSold = totalSold;
    this->hotdogsInventoryAmount = inventory;
    this->hotdogsSoldCount = soldCount;
}

// Getter and Setter implementations
std::string HotDogStandsClass::getIdentification() const {
    return identification;
}

void HotDogStandsClass::setIdentification(std::string id) {
    this->identification = id;
}

std::string HotDogStandsClass::getLocation() const {
    return location;
}

void HotDogStandsClass::setLocation(std::string loc) {
    this->location = loc;
}

double HotDogStandsClass::getCostPerHotdog() const {
    return costPerHotdog;
}

void HotDogStandsClass::setCostPerHotdog(double cost) {
    this->costPerHotdog = cost;
}

int HotDogStandsClass::getTotalHotdogsSold() const {
    return totalHotdogsSold;
}

void HotDogStandsClass::setTotalHotdogsSold(int totalSold) {
    this->totalHotdogsSold = totalSold;
}

int HotDogStandsClass::getHotdogsInventoryAmount() const {
    return hotdogsInventoryAmount;
}

void HotDogStandsClass::setHotdogsInventoryAmount(int inventory) {
    hotdogsInventoryAmount = inventory;
}

int HotDogStandsClass::getHotdogsSoldCount() const {
    return hotdogsSoldCount;
}

void HotDogStandsClass::setHotdogsSoldCount(int soldCount) {
    this->hotdogsSoldCount = soldCount;
}

// Method to buy hot dogs
void HotDogStandsClass::hotDogsBuy(int n) {
    if (this->hotdogsInventoryAmount == 0 ) {
        std::cout << "Sorry, we are out of hotdogs. Please try again later." << std::endl << std::endl;
        setHotdogsSoldCount(0);
        return;
    }
    if (n > this->hotdogsInventoryAmount) {
        std::cout << "Sorry, we only have " << this->hotdogsInventoryAmount << " hotdogs left. Please try again."<< std::endl << std::endl;
        setHotdogsSoldCount(0);
        return;
    }
    this->hotdogsSoldCount = n;
    this->totalHotdogsSold += n;
    this->hotdogsInventoryAmount -= n;
    std::cout << "Enjoy your " << n << " hot dogs! Thank you for your purchase."<< std::endl << std::endl;
}

  // stockInventory(n) method
  void HotDogStandsClass::stockInventory(int n) {
      setHotdogsInventoryAmount(this->hotdogsInventoryAmount += n);
      std::cout << "Inventory successfully restocked. Current hot dog inventory: " << this->hotdogsInventoryAmount<< std::endl << std::endl;
  }