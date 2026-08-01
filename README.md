# Garage Management System (task_4)

A CLI-based garage inventory and car management system written in C++. The project Uses OOP and Saves the state to external JSON storage using nlohmann's json.hpp.

## includes features like: 
- Vehicle Check-In: Add new vehicles to the inventory as either a Racer or a Support_Vehicle or AmbulanceCar. Automatically enforces unique car numbers across the Garage
- Garage Inventory View: Display detailed specifications and calculated performance scores for every checked-in vehicle
- Tune-Up System: Modify vehicle details (such as speed, capacity, crew size, or race history) and instantly recalculate performance scores
- Vehicle Retirement: Remove vehicles from the garage with built-in user confirmation
- Search System: Search for specific vehicles by unique car number or partial fullname string matching
- Garage Reporting: Reports total inventory counts, calculates average performance scores across all vehicles, and groups car counts by racing teams
- Automatic JSON Persistence: Loads existing data from garage.json on program startup and automatically saves updates following check-ins, tune-ups, or retirements.

## External Dependencies
- nlohmann/json.hpp: Header-only JSON library used for parsing input/output files.

## Prerequisites & Building
- A C++11 compliant compiler (GCC, Clang, or MSVC) supporting smart pointers (std::unique_ptr, std::make_unique).
- son.hpp present in your include directory or project folder.


Couldn't Do the GUI Bonus because of the time constraint and Qt Was Hard :)
But was able to the AmbulanceCar Bonus