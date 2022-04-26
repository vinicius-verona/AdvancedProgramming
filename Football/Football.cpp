// Used references:
// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1135

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define TOURNAMENT_NAME 100
#define TEAM_NAME       30
#define GAME_MAXSIZE    2 * TEAM_NAME + 4

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
     * @brief Compare two contestants according to the contest rules.
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
    bool operator<(const _team& team) const {
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
        else if (name != team.name)
            return name < team.name;
    }
} Team;

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
        size_t buffersize = TOURNAMENT_NAME;
        char* tournament = (char*)malloc((TOURNAMENT_NAME + 1) * sizeof(char));
        getline(&tournament, &buffersize, stdin);

        int nteams;
        scanf("%d", &nteams);
        map<string, Team*> teamsMap;
        vector<Team*> teamsVector(nteams, Team());

        // Read and map teams
        for (int j = 0; j < nteams; j++) {
            char* name = (char*)malloc((TEAM_NAME + 1) * sizeof(char));
            buffersize = TEAM_NAME + 1;
            getline(&name, &buffersize, stdin);

            int length = strlen(name);
            name[length - 1] = '\0';

            Team* team = new Team();
            team->name teamsMap[name] = team;
            teamsVector[j] = team;
            free(name);
        }

        // Read and map each game to each team
        int ngames;
        char* gameBuffer = (char*)malloc((GAME_MAXSIZE + 1) * sizeof(char));
        buffersize = GAME_MAXSIZE + 1;
        scanf("%d", &ngames);

        for (int j = 0; j < ngames; j++) {
            int read = getline(&gameBuffer, &buffersize, stdin);

            string teamNameA, scoreA, teamNameB, scoreB;
            int goalsA, goalsB, idx = 0;

            // Using map, map game to team A
            for (idx = 0; gameBuffer[idx] != '#'; idx++) teamNameA.push_back(gameBuffer[idx]);
            idx += 1;
            for (idx = idx; gameBuffer[idx] != '@'; idx++) scoreA.push_back(gameBuffer[idx]);
            idx += 1;
            goalsA = stoi(scoreA);
            teamsMap[teamNameA].goalsScored = goalsA;

            // Using map, map game to team B
            for (idx = 0; gameBuffer[idx] != '#'; idx++) scoreB.push_back(gameBuffer[idx]);
            idx += 1;
            for (idx = idx; gameBuffer[idx] != '\n' && gameBuffer[idx] != '\0'; idx++)
                teamNameB.push_back(gameBuffer[idx]);
            idx += 1;
            goalsB = stoi(scoreB);
            teamsMap[teamNameB].goalsScored = goalsB;

            // Update goals against
            teamsMap[teamNameA].goalsAgaint = goalsB;
            teamsMap[teamNameB].goalsAgaint = goalsA;
        }

        // sort(submissions.begin(), submissions.end());

        if (i < tournaments - 1) printf("\n");
    }

    return 0;
}
