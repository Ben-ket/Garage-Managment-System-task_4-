#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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

    static unique_ptr<Car> checkIn();

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
    
    virtual void inputData() {
        cout << "Enter Unique Car Number: ";
        cin >> carNumber;
        
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

    void inputData() override{

        Car::inputData();
        
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

    void inputData() override{

        Car::inputData();
        
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

};

unique_ptr<Car> Car::checkIn(){
        string choice;
        unique_ptr<Car> car = nullptr;

        while(!car){
            cout << "Enter Car Type (Racer / Support_Vehicle): ";
            cin >> choice;

            if(choice == "Racer") {
                car = make_unique<Racer>();
            } else if (choice == "Support_Vehicle") {
                car = make_unique<Support_Vehicle>();
            } else {
                cout << "Invalid Type, Try again\n";
            }
        }

        car->inputData();

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
        }

        if (car) {
            car->fromJson(j);
            garage.push_back(move(car));
        }
    }

    cout << "Loaded " << garage.size() << " car from " << filename << "\n";
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

        

        switch(choice){
            case 1: {
                //Check in car
                unique_ptr<Car> car = Car::checkIn();
                garage.push_back(move(car));

                saveToJson(garage);

                cout << "\nCar Checked In Successfully!\n";
                break;
            }
            case 2:
                //View the Garage
                break;
            case 3:
                //Tune-Up Car
                break;
            case 4:
                //Retire Car
                break;
            case 5:
                //Find a Car
                break;
            case 6:
                //Garage Report
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
