#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctype.h>

using namespace std;

unordered_map<char, string> prefTable; //table of prefs
unordered_map<char, bool> men; // if man is engaged
unordered_map<char, bool> women; // if woman is engaged
unordered_map<char, char> pairs; // final pairs of marriages
int menUnengaged = 0; // number of unengaged men
int womenUnengaged = 0; // number of unengaged women

// debugging functions
void coutPrefTable() {
	for ( auto i : prefTable) {
		cout << i.first << " prefers " << i.second << endl;
	}
}

void coutMen() {
	for (auto i : men) {
		string status = i.second ? "engaged" : "not engaged";
		cout << i.first << " is " << status << endl;
	}
}

void coutWomen() {
	for (auto i : women) {
		string status = i.second ? "engaged" : "not engaged";
		cout << i.first << " is " << status << endl;
	}

}

// creates preference table
// assumes person is first char and preferences are given correctly
// O(n)
void createPrefTable() {
	string line;
	while (getline(cin, line)) {
		char person = *line.begin();
		string preferences = "";
		for (auto i = line.begin() + 1; i < line.end(); i++) {
			if (*i != ' ' && *i != ',') {
				preferences += *i;
			}
		}
		prefTable.emplace(person, preferences);
		isupper(person) ? (men.emplace(person, false), menUnengaged++) : (women.emplace(person, false), womenUnengaged++);
	}
}

// returns man engaged to woman
// O(n)
char getEngagedMan(char woman) {
	for (auto i : pairs) {
		if (i.second == woman) {
			return i.first;
		}
	}
	return '\0';
}

// engages man and woman :)
// O(1)
void engage(char man, char woman) {
	women[woman] = true;
	men[man] = true;
	pairs.emplace(man, woman);
	menUnengaged--;
	womenUnengaged--;
}

// divorces engagedMan :(
// O(1)
void divorce(char engagedMan) {
	pairs.erase(pairs.find(engagedMan));
	men[engagedMan] = false;
	menUnengaged++;
	womenUnengaged++;
}

int main(int argc, const char * argv[]) {

	createPrefTable();

	// creating pairs
	while (menUnengaged && womenUnengaged) { // while there at least 1 unengaged man/woman
		for ( auto i : men) { // O(n)
			//continue if man is engaged
			if (i.second)
				continue;

			char man = i.first;
			all_of(prefTable[man].begin(), prefTable[man].end(), [man](char woman) { // O(n)
				if (women[woman]) {
					char engagedMan = getEngagedMan(woman);
					if (prefTable[woman].find(man) < prefTable[woman].find(engagedMan)) {
						divorce(engagedMan);
						engage(man, woman);
						return false;
					}
					return true;
				}
				else {
					engage(man, woman);
					return false;
				}
			});
		}
	}

	// cout pairs
	for (auto i : pairs) {
		cout << i.first << ":" << i.second << endl;
	}

	return 0;
}