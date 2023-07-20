#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include "HotDogStand.h"

#define HOT_DOGS_STANDS_INIT "./InfoHotDogStands.txt" // filepath to intial value of hotdog stands
#define INFO_GLOBAL_SOLD "./InfoGlobalSold.txt" // filepath to global sold
#define INFO_HOT_DOG_STANDS_TRANSACTIONS "./InfoHotDogStandTransactions.txt"  // filepath to all transaction that will take place 
#define TRANSACTION_TYPE_BUY "buy"  //buy transaction type
#define TRANSACTION_TYPE_STOCK "stock inventory"  //stock transaction type

using namespace std;
/**
 * get tokens from lines
 * 
 */
vector<string> getTokensFromLine(string line){
    stringstream ss(line); // stringstream object 
    vector<string> tokens; // vector array of the tokens 
    string token; // the token
    while (getline(ss, token, ',')) {
        tokens.push_back(token); // push token to tokens vector
    }
 return tokens;
} 
// reading global sold files
string readGlobalSold(){
   ifstream infile(INFO_GLOBAL_SOLD); // create input file stream
    if (infile.is_open()) { // check if the file is open
        string line;
        while (getline(infile, line)) { // read data from the file line by line
            return line; // print the data to the console
        }
        infile.close(); // close the file
    }
    else {
        cout << "Unable to open file."<< INFO_GLOBAL_SOLD << endl;
    }
    return "0";
}
// writing  global sold files
void writeGlobalSold(int currentGlobalSold){
    ofstream outfile(INFO_GLOBAL_SOLD); // create output file stream
    if (outfile.is_open()) { // check if the file is open
        outfile << currentGlobalSold; // write data to the file
        outfile.close(); // close the file
    }
    else {
        cout << "Unable to open file."<< INFO_GLOBAL_SOLD << endl;
    }
}
/**
 * display function
*/
void  display(vector<HotDogStandsClass*>  hotDogsStands,string transaction, int count, int totalTransactions){
int globalHotDogCount = stoi(readGlobalSold()); // string to integer
vector<string> tokens = getTokensFromLine(transaction);
   int size = tokens.size(); // size of the token array
    try
    {

    string standId = tokens.at(0);
    string transactionType = tokens.at(1);
    int numberOfHotDogs = stoi(tokens.at(2));

       // show while it's not a buying transaction and at the very end after all transaction
    if(transactionType != TRANSACTION_TYPE_BUY){
    cout<< " intial state for stands" << endl;
    cout << setfill('=') << setw(60) << "" << endl;
    for(const auto& stand : hotDogsStands){
        if(standId == stand->getIdentification()){
        stand->stockInventory(numberOfHotDogs);
        }
        // display
        cout<< "Stand Id  :"<< stand->getIdentification() << endl;
        cout<< "Address  :"<< stand->getLocation() << endl;
        cout<< "Price  :"<< stand->getCostPerHotdog() << endl;
        cout<< "Inventory  :"<< stand->getHotdogsInventoryAmount() << endl;
        cout<< "Store Sold  :"<< stand->getHotdogsInventoryAmount()<< " at $"<<stand->getCostPerHotdog()<< "  ea"<< endl << endl;
        
    }
      // stock

    }
    else{
      cout << setfill('=') << setw(60) << "" << endl << endl;
      cout << "Process transactions:" << endl;
      cout << setfill('=') << setw(60) << "" << endl << endl;
      cout << setfill('-') << setw(60) << "" << endl << endl;
      cout << "HotDog Stand Current Status : "<< endl <<endl;
      for(const auto& stand : hotDogsStands){
        if(stand->getIdentification() == standId){
          // before
            cout<< "Stand Id  :"<< stand->getIdentification() << endl;
            cout<< "Address  :"<< stand->getLocation() << endl;
            cout<< "Price  :"<< stand->getCostPerHotdog() << endl;
            cout<< "Inventory  :"<< stand->getHotdogsInventoryAmount() << endl;
            cout<< "Store Sold  :"<< stand->getHotdogsInventoryAmount()<< " at $"<<stand->getCostPerHotdog()<< "  ea"<< endl << endl;

            // transact
            cout<< "Transaction :"<< endl<<endl;
            cout<< "Transaction Stand Id :"<< standId << endl;
            cout<< "Transaction Id :"<< transactionType << endl;
            cout<< "Transaction Argument :"<< numberOfHotDogs << endl << endl;

            // do the computations and update 
            stand->hotDogsBuy(numberOfHotDogs);

            //after
            cout << "HotDog Stand Status After Transaction : "<< endl <<endl;
            cout<< "Stand Id  :"<< stand->getIdentification() << endl;
            cout<< "Address  :"<< stand->getLocation() << endl;
            cout<< "Price  :"<< stand->getCostPerHotdog() << endl;
            cout<< "Inventory  :"<< stand->getHotdogsInventoryAmount() << endl;
            cout<< "Store Sold  :"<< numberOfHotDogs << " at $"<<stand->getCostPerHotdog()<< "  ea"<< endl << endl;

            // calculate globalCount
            // if(!numberOfHotDogs > stand->getHotdogsInventoryAmount()){

                globalHotDogCount += stand->getHotdogsSoldCount();
                stand->setTotalHotdogsSold(globalHotDogCount);
        }
      }
    }
  }
  catch(const out_of_range& e)
    {
    cerr <<"Out of Range Err"<< e.what() << '\n';
  }
cout << endl<< endl << "Global Count :" << globalHotDogCount << endl << endl ;
writeGlobalSold(globalHotDogCount);


cout << setfill('-') << setw(60) << "" << endl << endl;
cout << "Please press enter key once or twice to continue... ";
} 


/**
 * map tokens to class stands
 * 
 */ 
HotDogStandsClass* initHotDogsStands(string line){
 // read each token
 vector<string> tokens = getTokensFromLine(line);
 int size = tokens.size();
 // loop through all tokens
  try {
   if(size  != 5){
    throw "Size err";

   }
 if(!tokens.empty()){
      try
      {

        string standID = tokens.at(0);
        string  location = tokens.at(1);
        double cost = stod(tokens.at(2));
        int totalHotDogSold = stoi(tokens.at(3));
        int hotdogsInventoryAmount = stoi(tokens.at(4));
        return new HotDogStandsClass(standID, location, cost, totalHotDogSold, hotdogsInventoryAmount, 0); 
        }
        catch (const out_of_range& e) {
    // Handle the out-of-range error here
    cerr << "Out of Range Error: " << e.what() << endl;
    }
}
else{
  cout << "Warning failed to map the tokens from text file to the class"<< endl <<" intializing one default stand" << endl;
}
}catch(string err){
  cout << err << endl;
  }
return new HotDogStandsClass("Stand1","No Location",0.00, 0,0,0);
}

int main(){ 
 vector<HotDogStandsClass*> hotDogsStands; // use a vector to store HotDogStandsClass objects
 vector<string> hotDogTransactions; // vector for every hotdog transaction
// print what the service is
cout << setfill('=') << setw(60) << "" << endl;
cout << setfill(' ') << setw(50) << "Hotdogs – The World's Greatest Cost Effective" << endl;
cout << setfill(' ') << setw(40)<< "Wholesome Nutritious Food" << endl;
cout << setfill('=') << setw(60) << "" << endl;
// load intial state of all hotdogs stands
    ifstream file(HOT_DOGS_STANDS_INIT);
    if (file.is_open()) {
        string line; // initial state of every stand
      while (getline(file, line)) {
           // map each  and allocate a new HotDogStandsClass pointer and store it in the vector
            HotDogStandsClass* newStand = initHotDogsStands(line);// create a new HotDogStandsClass object for each line
            hotDogsStands.push_back(newStand);// add the new object to the vector
        }
        file.close();
    }else {
        cerr << "Unable to open file: "<< HOT_DOGS_STANDS_INIT;
    };
 // read the transaction 
    ifstream transFile(INFO_HOT_DOG_STANDS_TRANSACTIONS);
    if (transFile.is_open()) {
        string line;
      while (getline(transFile, line)) {
          hotDogTransactions.push_back(line);
        }
        transFile.close();
    }else {
        cerr << "Unable to open file: "<< HOT_DOGS_STANDS_INIT;
    };


    int count = 0;
    bool START_TRANS = true;
    char ch;
    while(START_TRANS){
      // if transaction is empty exit
        if (hotDogTransactions.empty()) {
            cout << "No transactions to display. Exiting program..." << endl;
            break;
        }  
    if(count == hotDogTransactions.size()){
      // FINAL DISPLAY 
    cout << setfill('=') << setw(65) << "" << endl;
    cout << "Final State of the Stand and Global Count"<< endl;
    cout << setfill('=') << setw(65) << "" << endl << endl;

    for(const auto& stand : hotDogsStands){
        // display
        cout<< "Stand Id  :"<< stand->getIdentification() << endl;
        cout<< "Address  :"<< stand->getLocation() << endl;
        cout<< "Price  :"<< stand->getCostPerHotdog() << endl;
        cout<< "Inventory  :"<< stand->getHotdogsInventoryAmount() << endl;
        cout<< "Store Sold  :"<< stand->getHotdogsInventoryAmount()<< " at $"<<stand->getCostPerHotdog()<< "  ea"<< endl << endl;
        // cout<< "Total Sold  :"<< stand->getTotalHotdogsSold() << endl << endl;
    }

    // global count READ from file
    cout << endl<< endl << "Global Count :" << readGlobalSold() << endl << endl ; 


    cout << "Please press enter key once or twice to exit... ";
    bool done = false;
        while (!done) {
            cin.get(ch);
            if (ch == '\n') {
                cin.ignore(256, '\n'); // ignore any remaining characters in the input buffer
                done = true;
            }
        }
        START_TRANS = false;
    }
    else{
    // DO the transaction and displays
    display(hotDogsStands,hotDogTransactions.at(count), count, hotDogTransactions.size());
    count++;
    cin.get(ch);
    if (ch != '\n') {
    cout << "Invalid input. Exiting program..." << endl;
    break;
    }
    cin.ignore(256, '\n'); // ignore any remaining characters in the input buffer
    cout << "Continuing the program..." << endl;
    }
  
}

    return 0;
}

