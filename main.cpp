#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void clear_goats(list<Goat> &trp);
void any_old(list<Goat> &trp);
void all_old(list<Goat> &trp);
void find_goat(list<Goat> trp);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Clearing all goats.\n";
                clear_goats(trip);
                break;
            case 5:
                cout << "Checking for goats >=10 yrs old.\n";
                any_old(trip);
                break;
            case 6:
                cout << "Checking if all goats are >=10 yrs old.\n";
                all_old(trip);
                break;
            case 7:
                find_goat(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Clear all goats\n";
    cout << "[5] Check for goats >=10 yrs old\n";
    cout << "[6] Check if all goats are >=10 yrs old\n";
    cout << "[7] Find a goat by name\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

// ----------------------------
// My new functions
// ----------------------------
void clear_goats(list<Goat> &trp) {
    trp.clear();
}

void any_old(list<Goat> &trp) {
    bool hasOldGoat = any_of(trp.begin(), trp.end(), [](Goat g) { return g.get_age() > 10; });
    if (hasOldGoat) {
        cout << "There is at least one goat aged 10 or older in the trip.\n";
    } else {
        cout << "There are no goats aged 10 or older in the trip.\n";   
    }
}

void all_old(list<Goat> &trp) {
    bool allOldGoats = all_of(trp.begin(), trp.end(), [](Goat g) { return g.get_age() > 10; });
    if (allOldGoats) {
        cout << "All goats are aged 10 or older in the trip.\n";
    } else {
        cout << "Not all goats are aged 10 or older in the trip.\n";
    }
}

void find_goat(list<Goat> trp) {
    string name;
    cout << "Search for name: ";
    cin >> name;
    auto it = find_if(trp.begin(), trp.end(), [name](Goat g) { return g.get_name() == name; });
    if (it != trp.end()) {
        cout << "Goat found: " ;
        cout << "\t" << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
    } else {
        cout << "Goat with name " << name << " not found in the trip.\n";
    }
}