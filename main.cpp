#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Car{
private:
    int carNumber;
    string fullName;
    int age;
    string type;
    string racingTeam;
    double speed;
    double capacity;
    double perfScore;
public:
    void display_info(){
        cout << "Car Number: " << this->carNumber << endl;
        cout << "Full Name: " << this->fullName << endl;
        cout << "Age: " << this->age << endl;
        cout << "Type: " << this->type << endl;
        cout << "Racing Team: " << this->racingTeam << endl;
        cout << "Speed: " << this->speed << endl;
        cout << "Capacity: " << this->capacity << endl;
        cout << "Performance Score: " << this->perfScore << "\n\n"; 
    }

    
};




int main(){

    vector<Car> cars;

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
    }
    


    

    return 0;
}