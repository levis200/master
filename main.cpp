#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;


struct Team
{
    string name;
    string town;
    string stadium;
};

struct Game
{
    int homeTeam;
    int awayTeam;
    int leg;
    int weekend;
};

// This function is used to read teams from the csv file
vector<Team> readCSV(const string & teams_csvFile) {

    ifstream file("teams_csvFile"); // This is used to open the csv file
    string line;

    getline(file, line); // This reads a line from the file

    vector<Team> teams;
    if (file.is_open()) // This checks if the file is open
    while (getline(file, line)) {
        Team newTeam; // Create a new team object
        stringstream ss(line);

        Team team;
        istream s;
        // This is to extract and read the team information
        getline(s, team.name, '\t' );
        getline(s, team.town, '\t' );
        getline(s, team.stadium, '\t' );
        teams.push_back(team);

        file.close();
    } else {
        cout<<"Unable to open file"<<endl;

    }
    return teams;

  }
  int main() {
      string filename = "C:\Users\linds\downloads\teams_csvFile.csv";
      const string teams_csvFile;
  vector<Team> teams = readCSV(teams_csvFile);

 // This is to print all teams
 for (const auto & [name, town, stadium]: teams) {
     cout<< "Team: "<<name << ", Town: "<<town << ", Stadium:" <<stadium<<endl;
    }

   return 0;
  }
  //Generating the fixtures
  void generateFixtures(const vector<Team> &teams) {
      int totalTeams = team.size();
      vector<vector<Team>> fixtures;

      //This is used to generate home and away fixtures
      for (int i=0; i < totalTeams; ++i) {
          for (int j = i + 1; j < totalTeams; ++j) {
          //Generate fixtures for teams from different local towns
          fixtures.push_back({teams[i], teams[j]});
          fixtures.push_back({teams[j], teams[i]});

          }
      }

  //Shuffle fixtures to randomize
   srand(time(0));
   random_shuffle(fixtures.begin(), fixtures.end());

  //Output fixtures which will be grouped by weekends
  int weekend = 1;
  for (size_t i = 0; i < fixtures.size(); i+= 2) {
    cout << "Weekend #"<< weekend <<endl;
    cout << fixtures[i].first.name << "vs" << fixtures[i].second.name << "at" << fixtures[i].first.stadium <<endl;

    if (i + 1 < fixtures.size()) {
       cout << fixtures[i+1].first.name << "vs" <<fixtures[i+1].second.name << "at" << fixtures[i+1].first.stadium
       <<endl;
    }
    cout <<endl;
    weekend++;
  }

 }
//This is used to save the generated fixtures to a csv file
void saveFixturesToFile(const vector<pair<Team, Team>> &fixtures, const string &filename) {
   ofstream file(filename);
   if (file.is_open()) {
       file << "Weekend,Team1,Team2,Stadium,Leg\n";
       int weekend = 1;
       for (size_t i = 0; i < fixtures.size(); i+=2) {
           file << "Weekend #" << weekend << "," << fixtures[i].first.name << "," << fixtures[i].second.name << ","
           << fixtures[i].first.stadium << "Leg 1\n";
           if (i + 1 < fixtures.size()) {
              file << "Weekend #" << weekend << ";" << fixtures[i + 1].first.name << "," << fixtures[i + 1].second.name
              << "," << fixtures[i + 1].first.stadium << "Leg 1\n";
           }
           weekend++;
       }
       file.close();
   } else{
      cout << "Unable to open file for writing" <<endl;
   }

}

