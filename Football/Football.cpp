// Used references:
// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1135
// https://stackoverflow.com/questions/15927583/how-to-suppress-warning-control-reaches-end-of-non-void-function
// https://github.com/Sharknevercries/Online-Judge/blob/master/UVA/Volume%20CI/10194%20Football%20(aka%20Soccer).cpp ->
// Lexicographical sorting

#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
typedef struct _team {
    string name;
    int teamRank;
    int points;
    int games;
    int wins;
    int ties;
    int losses;
    int goalsScored;
    int goalsAgainst;
    int goalsDifference;

    /**
     * @brief Compare two teams according to the tournament rules.
     * @param a Any team
     * @param b Any team
     * @note Comparison rule:
     * 1. Most points earned.
     * 2. Most wins.
     * 3. Most goal difference (i.e. goals scored - goals against)
     * 4. Most goals scored.
     * 5. Less games played.
     * 6. Lexicographic order.
     */
    bool operator<(const _team &team) const {
        if (points != team.points)
            return points > team.points;
        else if (wins != team.wins)
            return wins > team.wins;
        else if (goalsDifference != team.goalsDifference)
            return goalsDifference > team.goalsDifference;
        else if (goalsScored != team.goalsScored)
            return goalsScored > team.goalsScored;
        else if (games != team.games)
            return games < team.games;
        else
            // In order to sort in lexicographical order, consider:
            // * each characters as lowercase
            // * if string 'a' reaches its end, than it comes before 'b'
            // * if string 'b' reaches its end, than it comes before 'a'
            // * if the compared char from 'a' has a smaller ASCII value than char from 'b'. Then, 'a' comes before.
            for (int i = 0; i >= 0; i++) {
                if (name[i] == '\0') return true;
                if (team.name[i] == '\0') return false;
                if (tolower(name[i]) < tolower(team.name[i])) return true;
                if (tolower(name[i]) > tolower(team.name[i])) return false;
            }
    }
} Team;
#pragma GCC diagnostic pop

// For a given pair of teams, compare both according to the tournament rules
bool compareTeams(Team *a, Team *b) { return *a < *b; }

// For a given team, calculates the amount of points earned
int calculatePoints(Team team) { return 3 * team.wins + team.ties; }

// Overloading operator for cout
ostream &operator<<(ostream &os, const Team &team) {
    os << team.teamRank << ") " << team.name << " " << calculatePoints(team) << "p, " << team.games << "g ("
       << team.wins << "-" << team.ties << "-" << team.losses << "), " << team.goalsDifference << "gd ("
       << team.goalsScored << "-" << team.goalsAgainst << ")";
    return os;
}

/**
 * @brief Problem: 10194 - Football (aka Soccer)
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 *
 * @ignore
 * Find at:
 * https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1135
 */
int main() {
    int tournaments;
    scanf("%d\n", &tournaments);

    for (int i = 0; i < tournaments; i++) {
        // Read tournament name
        string tournament;
        getline(cin, tournament);

        int nteams;
        scanf("%d\n", &nteams);
        map<string, Team *> teamsMap;
        vector<Team *> teamsVector(nteams, NULL);

        // Read and map teams
        for (int j = 0; j < nteams; j++) {
            string name;
            getline(cin, name);

            Team *team = new Team();
            team->name = name;
            teamsMap[name] = team;
            teamsVector[j] = team;
        }

        // Read and map each game to each team
        int ngames;
        string gameBuffer;
        scanf("%d\n", &ngames);

        for (int j = 0; j < ngames; j++) {
            getline(cin, gameBuffer);

            string teamNameA, scoreA, teamNameB, scoreB;
            int goalsA, goalsB, idx = 0;

            // Using map, map game to team A
            for (idx = 0; gameBuffer[idx] != '#'; idx++) teamNameA.push_back(gameBuffer[idx]);
            idx += 1;
            for (idx = idx; gameBuffer[idx] != '@'; idx++) scoreA.push_back(gameBuffer[idx]);
            idx += 1;

            goalsA = stoi(scoreA);
            teamsMap[teamNameA]->goalsScored += goalsA;

            // Using map, map game to team B
            for (idx = idx; gameBuffer[idx] != '#'; idx++) scoreB.push_back(gameBuffer[idx]);
            idx += 1;
            for (idx = idx; gameBuffer[idx] != '\n' && gameBuffer[idx] != '\0'; idx++)
                teamNameB.push_back(gameBuffer[idx]);
            idx += 1;

            goalsB = stoi(scoreB);
            teamsMap[teamNameB]->goalsScored += goalsB;

            // Update goals against, goals difference, and games
            teamsMap[teamNameA]->goalsAgainst += goalsB;
            teamsMap[teamNameB]->goalsAgainst += goalsA;
            teamsMap[teamNameA]->goalsDifference += (goalsA - goalsB);
            teamsMap[teamNameB]->goalsDifference += (goalsB - goalsA);
            teamsMap[teamNameA]->games += 1;
            teamsMap[teamNameB]->games += 1;

            if (goalsA > goalsB) {
                teamsMap[teamNameA]->wins += 1;
                teamsMap[teamNameA]->points += 3;
                teamsMap[teamNameB]->losses += 1;
            } else if (goalsA < goalsB) {
                teamsMap[teamNameB]->wins += 1;
                teamsMap[teamNameB]->points += 3;
                teamsMap[teamNameA]->losses += 1;
            } else {
                teamsMap[teamNameA]->ties += 1;
                teamsMap[teamNameB]->ties += 1;
                teamsMap[teamNameA]->points += 1;
                teamsMap[teamNameB]->points += 1;
            }
        }

        sort(teamsVector.begin(), teamsVector.end(), compareTeams);

        //  Print the result
        cout << tournament << endl;
        int counter = 1;
        for (Team *team : teamsVector) {
            team->teamRank = counter;
            cout << *team << endl;
            counter++;
        }

        teamsMap.clear();
        teamsVector.clear();

        if (i < tournaments - 1) printf("\n");
    }

    return 0;
}
