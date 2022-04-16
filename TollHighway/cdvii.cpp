// Used references
// https://github.com/KHvic/uva-online-judge/blob/master/10138-CDVII.cpp
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=32&page=show_problem&problem=1079

#include <bits/stdc++.h>

#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Fee per trip
#define FEE_PER_TRIP 1

// Dollars charged
#define ACCOUNT_CHARGE 2

// Total number of fares
#define TOTAL_FARES 24
typedef struct {
    string licensePlate;
    int month, day, hour, minute, km;
    bool stats;  // true when status = enter and false when exit;
} Record;

/**
 * @brief Get the time in milliseconds for a given record
 *
 * @param record The photo record for a given vehicle
 * @return Time in millisecond (Integer)
 */
int getTime(Record record);

/**
 * @brief Compare two given records by analyzing its time in milliseconds
 *
 * @param a First record
 * @param b Second record
 * @return true if a < b and false otherwise
 */
bool compareRecords(Record a, Record b);

/**
 * @brief Calculate and present the bill for each month and each vehicle
 *
 * @param fares The toll fares for each hour of the day
 * @param records The travel record for each vehicle
 */
void solve(double fares[TOTAL_FARES], map<string, vector<Record>> records);

// COUT overload for Record struct
ostream &operator<<(ostream &, const Record &);

int main() {
    // Control variables
    string stats;
    char ignore;
    int cases = 0;
    string line;

    scanf("%d\n\n", &cases);

    for (int i = 0; i < cases; i++) {
        double tollFares[24];
        map<string, vector<Record>> records;

        // Read fares
        for (int j = 0; j < 24; j++) {
            cin >> tollFares[j];
        }

        cin.ignore();

        while (getline(cin, line) && !line.empty()) {
            stringstream lineStream(line);

            // Read records;
            Record record;
            lineStream >> record.licensePlate >> record.month >> ignore >>
                record.day >> ignore >> record.hour >> ignore >>
                record.minute >> stats >> record.km;

            record.stats = (stats == "enter") ? true : false;

            // Insert record to map where key equals to license plate
            records[record.licensePlate].push_back(record);
        }

        solve(tollFares, records);
        if (i != cases - 1) cout << endl;
    }

    return 0;
}

ostream &operator<<(ostream &os, const Record &rec) {
    os << rec.licensePlate << " - " << rec.month << "/" << rec.day << "-T-"
       << rec.hour << ":" << rec.minute << " -> KM: " << rec.km << " ["
       << rec.stats << "]";
    return os;
}

int getTime(Record record) {
    int monthInSeconds = 30 * 24 * 60 * 60;
    int daysInSeconds = 24 * 60 * 60;
    int hoursInSeconds = 60 * 60;
    int minutesInSeconds = 60;

    return ((record.month - 1) * monthInSeconds +
            (record.day - 1) * daysInSeconds + record.hour * hoursInSeconds +
            record.minute * minutesInSeconds) *
           100;
}

bool compareRecords(Record a, Record b) { return getTime(a) < getTime(b); }

void solve(double fares[TOTAL_FARES], map<string, vector<Record>> records) {
    map<string, vector<Record>>::iterator vehicle = records.begin();

    while (vehicle != records.end()) {
        vector<Record> vehicleRecord = vehicle->second;
        sort(vehicleRecord.begin(), vehicleRecord.end(), compareRecords);

        double bill = 0.0;

        for (int i = 1; i < (int)vehicleRecord.size(); i++) {
            if (vehicleRecord[i - 1].stats && !vehicleRecord[i].stats) {
                bill += FEE_PER_TRIP;
                bill += (fares[vehicleRecord[i - 1].hour] / 100) *
                        abs(vehicleRecord[i].km - vehicleRecord[i - 1].km);
            }
        }

        if (abs(bill - 0) > 0.000001) {
            cout << vehicle->first;
            printf(" $%.2lf\n", bill + ACCOUNT_CHARGE);
        }

        vehicle++;
    }
}