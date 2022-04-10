// https://github.com/KHvic/uva-online-judge/blob/master/10138-CDVII.cpp
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=32&page=show_problem&problem=1079
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef struct {
    string licensePlate;
    int month, day, hour, minute, km;
    bool stats;  // true when status = enter and false when exit;
} Record;

// COUT overload for Record struct
ostream& operator<<(ostream&, const Record&);

int main() {
    // Control variables
    string stats;
    char ignore;
    int cases = 0;
    string line;

    scanf("%d\n\n", &cases);

    for (int i = 0; i < cases; i++) {
        int tollFares[24];
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
                record.minute >> ignore >> stats >> record.km;

            record.stats = (stats == "enter") ? true : false;

            // Insert record to map where key equals to license plate
            records[record.licensePlate].push_back(record);

            cout << record << endl;
        }
    }

    return 0;
}

ostream& operator<<(ostream& os, const Record& rec) {
    os << rec.licensePlate << " - " << rec.month << "/" << rec.day << "-T-"
       << rec.hour << ":" << rec.minute << " -> KM: " << rec.km;
    return os;
}