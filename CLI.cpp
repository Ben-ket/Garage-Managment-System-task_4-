#include "Garage.hpp"

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