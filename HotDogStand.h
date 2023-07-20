#include <string>
#include <iostream>

class HotDogStandsClass {
private:
    std::string identification;   // unique identification string
    std::string location;         // address of the stand
    double costPerHotdog;         // cost per hotdog
    int totalHotdogsSold;         // total hot dogs sold across all stands
    int hotdogsInventoryAmount;   // hot dogs inventory amount
    int hotdogsSoldCount;         // hot dogs sold count for this stand
    
public:
    // Constructor with parameters
    HotDogStandsClass(std::string id, std::string loc, double cost , int totalSold , int inventory, int soldCount );

    // Getter and Setter methods for private instance variables
    std::string getIdentification() const;
    void setIdentification(std::string id);
    std::string getLocation() const;
    void setLocation(std::string loc);
    double getCostPerHotdog() const;
    void setCostPerHotdog(double cost);
    int getTotalHotdogsSold() const;
    void setTotalHotdogsSold(int totalSold);
    int getHotdogsInventoryAmount() const;
    void setHotdogsInventoryAmount(int inventory);
    int getHotdogsSoldCount() const;
    void setHotdogsSoldCount(int soldCount);

    // Method to buy hot dogs
    void hotDogsBuy(int n);

    // Method to add hot dogs to inventory
    void stockInventory(int n);
};

