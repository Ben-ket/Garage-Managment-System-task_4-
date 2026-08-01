#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <cctype>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Car;
int carNumExists(const vector<unique_ptr<Car>>& garage, int num);

class Car{
protected:
    int carNumber = 0;
    string fullName;
    int age = 0;
    string type;
    string racingTeam;
    double speed = 0.0;
    int capacity = 0;
    double perfScore = 0.0;
public:

    virtual ~Car() = default;

    Car() = default;

    static unique_ptr<Car> checkIn(const vector<unique_ptr<Car>>& garage);
    

    virtual void display_info(){
        cout << "Car Number: " << this->carNumber << endl;
        cout << "Full Name: " << this->fullName << endl;
        cout << "Age: " << this->age << endl;
        cout << "Type: " << this->type << endl;
        cout << "Racing Team: " << this->racingTeam << endl;
        cout << "Speed: " << this->speed << endl;
        cout << "Capacity: " << this->capacity << endl;
        cout << "Performance Score: " << this->perfScore << endl; 
    }
    
    virtual void inputData(const vector<unique_ptr<Car>>& garage) {
        int unique  = 0;
        do{
        
            cout << "Enter Unique Car Number: ";
            cin >> carNumber;

            if(carNumExists(garage, carNumber)){
                cout << "Car Number alraedy exist, try Another\n";
            }else{
                unique = 1;
            }

        }while(!unique);
        
        cin.ignore();
        cout << "Enter Car Full Name: ";
        getline(cin, fullName);

        do {
            cout << "Enter Car Age: ";
            cin >> age;
        } while (age <= 0);

        cin.ignore();
        cout << "Enter Racing Team Name: ";
        getline(cin, racingTeam);

        do {
            cout << "Enter Speed: ";
            cin >> speed;
        } while (speed <= 0);

        do {
            cout << "Enter Capacity: ";
            cin >> capacity;
        } while (capacity <= 0);


    }

    // Constructer
    Car(int carNumber, string fullName, int age, string type, string racingTeam, double speed, double capacity){
        this->carNumber = carNumber;
        this->fullName = fullName;
        this->age = age;
        this->type = type;
        this->racingTeam = racingTeam;
        this->speed = speed;
        this->capacity = capacity;
    }

    int getCarNum() const { return carNumber; };

    virtual json jsonConvert() const{
        return json{
            {"carNumber", carNumber},
            {"fullName", fullName},
            {"age", age},
            {"type", type},
            {"racingTeam", racingTeam},
            {"speed", speed},
            {"capacity", capacity},
            {"perfScore", perfScore}
        };
    }

    virtual void fromJson(const json& j) {
        carNumber = j["carNumber"];
        fullName = j["fullName"];
        age = j["age"];
        type = j["type"];
        racingTeam = j["racingTeam"];
        speed = j["speed"];
        capacity = j["capacity"];
        perfScore = j["perfScore"];
    }

    virtual void tuneUp() {
        cin.ignore();
        cout << "Enter New Full Name (Current: " << fullName << "): ";
        getline(cin, fullName);

        do {
            cout << "Enter New Age (Current: " << age << "): ";
            cin >> age;
        } while (age <= 0);

        cin.ignore();
        cout << "Enter New Racing Team Name (Current: " << racingTeam << "): ";
        getline(cin, racingTeam);

        do {
            cout << "Enter New Speed (Current: " << speed << "): ";
            cin >> speed;
        } while (speed <= 0);

        do {
            cout << "Enter New Capacity (Current: " << capacity << "): ";
            cin >> capacity;
        } while (capacity <= 0);
    }


};

class Racer : public Car{
private:
    int races = 0;
    int laps = 0;

public:
    Racer() {type = "Racer";}

    void display_info() override{
        
        Car::display_info();

        cout << "Number of Races Completed: " << this->races << endl;
        cout << "Laps Completed: " << this->laps << endl;

    }

    void inputData(const vector<unique_ptr<Car>>& garage) override{

        Car::inputData(garage);
        
        do {
            cout << "Enter Number of Races Completed: ";
            cin >> races;
        } while (races <= 0);

        do {
            cout << "Enter Number of Laps Completed: ";
            cin >> laps;
        } while (laps <= 0);

        this->perfScore = this->speed * 10 + this->capacity;


    }

    json jsonConvert() const override{
        json j  = Car::jsonConvert();
        j["races"] = races;
        j["laps"] = laps;
        return j;
    }

    void fromJson(const json& j) override {
        Car::fromJson(j);
        races = j["races"];
        laps = j["laps"];
    }

    void tuneUp() override {
    Car::tuneUp();

    do {
        cout << "Enter New Number of Races Completed (Current: " << races << "): ";
        cin >> races;
    } while (races <= 0);

    do {
        cout << "Enter New Laps Completed (Current: " << laps << "): ";
        cin >> laps;
    } while (laps <= 0);

    this->perfScore = this->speed * 10 + this->capacity;
    cout << "\nCar tuned up Successfully\n";
}

};

class Support_Vehicle : public Car{
private:
    int crew = 0;
    int reliability = 0;

public:
    Support_Vehicle() { type = "Support_Vehicle"; }

    void display_info() override{
       
        Car::display_info();

        cout << "Crew Size: " << this->crew << endl;
        cout << "Reliability Rating: " << this->reliability << endl;

    }

    void inputData(const vector<unique_ptr<Car>>& garage) override{

        Car::inputData(garage);
        
        do {
            cout << "Enter Crew Size: ";
            cin >> crew;
        } while (crew <= 0);

        do {
            cout << "Enter Reliability Rating: ";
            cin >> reliability;
        } while (reliability <= 0);

         this->perfScore = this->speed * 5 + this->capacity * 5;


    }

    json jsonConvert() const override{
        json j  = Car::jsonConvert();
        j["crew"] = crew;
        j["reliability"] = reliability;
        return j;
    }

    void fromJson(const json& j) override {
        Car::fromJson(j);
        crew = j["crew"];
        reliability = j["reliability"]; 
    }

    void tuneUp() override {
    Car::tuneUp();

    do {
        cout << "Enter New Crew Size (Current: " << crew << "): ";
        cin >> crew;
    } while (crew <= 0);

    do {
        cout << "Enter New Reliability Rating (Current: " << reliability << "): ";
        cin >> reliability;
    } while (reliability <= 0);

    this->perfScore = this->speed * 5 + this->capacity * 5;
    cout << "\nCar tuned up successfully\n";
}
};

class AmbulanceCar : public Car{
private:
    int medicalSupplies = 0;

public:
    AmbulanceCar() { type = "AmbulanceCar"; }

    void display_info() override{
       
        Car::display_info();

        cout << "Medical Supplies: " << this->medicalSupplies << endl;

    }

    void inputData(const vector<unique_ptr<Car>>& garage) override{

        Car::inputData(garage);
        
        do {
            cout << "Enter Amount of Medical Supplies: ";
            cin >> medicalSupplies;
        } while (medicalSupplies <= 0);


         this->perfScore = this->speed * 10 + this->capacity * 10;


    }

    json jsonConvert() const override{
        json j  = Car::jsonConvert();
        j["medicalSupplies"] = medicalSupplies;
        return j;
    }

    void fromJson(const json& j) override {
        Car::fromJson(j);
        medicalSupplies = j["medicalSupplies"]; 
    }

    void tuneUp() override {
    Car::tuneUp();

    do {
        cout << "Enter New Medical Supplies Amount (Current: " << medicalSupplies << "): ";
        cin >> medicalSupplies;
    } while (medicalSupplies <= 0);

    this->perfScore = this->speed * 10 + this->capacity * 10;
    cout << "\nCar tuned up successfully\n";
}
};

unique_ptr<Car> Car::checkIn(const vector<unique_ptr<Car>>& garage){
        string choice;
        unique_ptr<Car> car = nullptr;

        while(!car){
            cout << "Enter Car Type (Racer / Support_Vehicle / AmbulanceCar): ";
            cin >> choice;

            if(choice == "Racer") {
                car = make_unique<Racer>();
            } else if (choice == "Support_Vehicle") {
                car = make_unique<Support_Vehicle>();
            } else if (choice == "AmbulanceCar") {
                car = make_unique<AmbulanceCar>();
            } else {
                cout << "Invalid Type, Try again\n";
            }
        }

        car->inputData(garage);

        return car;
    }

void saveToJson(vector<unique_ptr<Car>>& garage, const string& filename = "garage.json") {
    json jsonArray = json::array();

    for (const auto& car : garage) {
        jsonArray.push_back(car->jsonConvert());
    }

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << jsonArray.dump(4);
        cout << "\nSuccessfully Garage saved to " << filename << endl;
    } else {
        cerr << "\n Error" << endl;
    }
}

void loadFromJson(vector<unique_ptr<Car>>& garage, const string& filename = "garage.json") {
    ifstream inFile(filename);
    
    if (!inFile.is_open()) {
        return;
    }

    json jsonArray;
   
    inFile >> jsonArray;
    
    inFile.close();

    garage.clear();

    for (const auto& j : jsonArray) {
        string carType = j.value("type", "");
        unique_ptr<Car> car = nullptr;

        if (carType == "Racer") {
            car = make_unique<Racer>();
        } else if (carType == "Support_Vehicle") {
            car = make_unique<Support_Vehicle>();
        } else if (carType == "AmbulanceCar") {
            car = make_unique<AmbulanceCar>();
        }

        if (car) {
            car->fromJson(j);
            garage.push_back(move(car));
        }
    }

    cout << "Loaded " << garage.size() << " car from " << filename << "\n";
}

int carNumExists(const vector<unique_ptr<Car>>& garage, int num){
    for (const auto& car : garage) {
        if (car->getCarNum() == num) {
            return 1;
        }
    }
    return 0;
}

void viewGarage(const vector<unique_ptr<Car>>& garage) {
    if (garage.empty()) {
        cout << "The garage is empty\n";
        return;
    }

    cout << "\n========== GARAGE INVENTORY ==========\n";
    for (size_t i = 0; i < garage.size(); i++) {
        cout << "\n[ Vehicle #" << (i + 1) << " ]\n";
        garage[i]->display_info();
        cout << "\n";
    }
}

void listCarNums(const vector<unique_ptr<Car>>& garage) {
    cout << "\nList of Car Numbers:\n";
    for (const auto& car : garage) {
        cout << "Car #" << car->getCarNum() << "\n";
    }
}

void tuneUpCar(vector<unique_ptr<Car>>& garage) {
    if (garage.empty()) {
        cout << "\nThe garage is empty\n";
        return;
    }

    listCarNums(garage);

    int targetNum;
    cout << "\nEnter Car Number to Tune-Up: ";
    cin >> targetNum;

    for (auto& car : garage) {
        if (car->getCarNum() == targetNum) {
            cout << "\n--- Editing Car #" << targetNum << " ---\n";
            car->tuneUp();
            saveToJson(garage);
            return;
        }
    }

    cout << "\n No Car with number " << targetNum << " was found\n";
}

void retireCar(vector<unique_ptr<Car>>& garage) {
    if (garage.empty()) {
        cout << "\nThe garage is empty\n";
        return;
    }

    listCarNums(garage);

    int targetNum;
    cout << "Enter Car Number to Retire: ";
    cin >> targetNum;

    for (auto it = garage.begin(); it != garage.end(); ++it) {
        if ((*it)->getCarNum() == targetNum) {
            
            char confirm;
            cout << "\nConfiramtion to retire Car #" << targetNum << "? (y/n): ";
            cin >> confirm;

            if (tolower(confirm) == 'y') {
                garage.erase(it);
                saveToJson(garage);
                cout << "\nCar #" << targetNum << " has been retired successfully.\n";
            } else {
                cout << "\nRetiring Cancelled\n";
            }
            return;
        }
    }

    cout << "\n No Car with number " << targetNum << " was found\n";
}

void findCar(const vector<unique_ptr<Car>>& garage) {
    if (garage.empty()) {
        cout << "\nThe garage is empty\n";
        return;
    }

    int searchType = 0;
    cout << "\nSearch Car By:\n";
    cout << "1- Car Number\n";
    cout << "2- Full Name\n";
    cout << "Enter choice: ";
    cin >> searchType;

    bool found = false;

    if (searchType == 1) {
        int targetNum;
        cout << "Enter Car Number: ";
        cin >> targetNum;

        for (const auto& car : garage) {
            if (car->getCarNum() == targetNum) {
                cout << "\nMatching Car Found\n";
                car->display_info();
                found = true;
                break;
            }
        }
    } 
    else if (searchType == 2) {
        cin.ignore();
        string targetName;
        cout << "Enter Full Name (or part of name): ";
        getline(cin, targetName);

        cout << "\nSearch Results\n";
        for (const auto& car : garage) {
            string carName = car->jsonConvert().value("fullName", "");
            
            if (carName.find(targetName) != string::npos) {
                cout << "\n\n";
                car->display_info();
                cout << "\n\n";
                found = true;
            }
        }
    } 
    else {
        cout << "\nInvalid search choice\n";
        return;
    }

    if (!found) {
        cout << "\nNo matching cars found\n";
    }
}

struct TeamCount {
    string teamName;
    int count = 0;
};

void garageReport(const vector<unique_ptr<Car>>& garage) {
    if (garage.empty()) {
        cout << "\nThe garage is empty\n";
        return;
    }

    int totalCars = garage.size();
    double totalPerfScore = 0.0;
    vector<TeamCount> teams;

    for (const auto& car : garage) {
        json j = car->jsonConvert();

        totalPerfScore += j.value("perfScore", 0.0);

        string team = j.value("racingTeam", "Unassigned");
        if (team.empty()) team = "Unassigned";


        bool found = false;
        for (auto& tc : teams) {
            if (tc.teamName == team) {
                tc.count++;
                found = true;
                break;
            }
        }
        if (!found) {
            teams.push_back({team, 1});
        }
    }

    double avgPerfScore = totalPerfScore / (double) totalCars;

  
    cout << "\n             GARAGE REPORT               \n";
    cout << "Total Cars Checked In: " << totalCars << "\n";
    cout << "Average Performance Score: " << avgPerfScore << "\n\n";

    cout << "Cars Per Racing Team\n";
  
    for (const auto& tc : teams) {
        cout << "  - " << tc.teamName << ": " << tc.count << " car(s)\n";
    }
    cout << "\n\n";
}


int main(){
    vector<unique_ptr<Car>> garage;

    loadFromJson(garage);

    //Main Menu
    int choice = 0;

    while (choice != 7)
    {

       cout <<  "1- Check in a Car\n"
                "2- View The Garage\n"
                "3- Tune-Up Car\n"
                "4- Retire Car\n"
                "5- Find a Car\n"
                "6- Garage Report\n"
                "7- Quit\n\n" 
                "Enter Your Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n'); 
            cout << "Invalid input, Please enter a number\n\n";
            continue;
        }

        switch(choice){
            case 1: {
                //Check in car
                unique_ptr<Car> car = Car::checkIn(garage);
                garage.push_back(move(car));

                saveToJson(garage);

                cout << "\nCar Checked In Successfully!\n";
                break;
            }
            case 2:
                //View the Garage
                viewGarage(garage);
                break;
            case 3:
                //Tune-Up Car
                tuneUpCar(garage);
                break;
            case 4:
                //Retire Car
                retireCar(garage);
                break;
            case 5:
                //Find a Car
                findCar(garage);
                break;
            case 6:
                //Garage Report
                garageReport(garage);
                break;
            case 7:
                //Quit
                cout << "\nGoodbye";
                break;
            default:
                cout << "Invalid Option\n";
                break;
        }
    }

    return 0;
}