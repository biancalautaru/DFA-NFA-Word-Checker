#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
ifstream fin("config_dfa.txt");
bool ok;
string line, start, cuvant;
vector<string> states;
unordered_map<string, bool> final;
vector<char> sigma;
unordered_map<string, vector<pair<string, char>>> automat;
unordered_map<char, int> fr;

string extract_state(string line, int &ind) {
	string state = "q";
	for (int i = 0; i < line.size(); i++)
		if (line[i] == 'q') {
			int j;
			for (j = i + 1; j < line.size() && line[j] != ' ' && line[j] != ','; j++)
				state += line[j];
			ind = j - 1;
			break;
		}
	return state;
}

int main() {
	while (getline(fin, line))
		if (line.find('#') == string::npos) {
			if (line.find("States:") != string::npos) {
				getline(fin, line);
				while (line.find("End") == string::npos) {
					if (line[0] != '#') {
						int ind = -1;
						string state = extract_state(line, ind);
						states.push_back(state);
						if (line.find('S') != string::npos)
							if (ok == false) {
								start = state;
								ok = true;
							}
							else {
								cout << "Automat Invalid!";
								return 0;
							}
						if (line.find('F') != string::npos)
							final[state] = true;
					}
					getline(fin, line);
				}
			}
			if (line.find("Sigma:") != string::npos) {
				getline(fin, line);
				while (line.find("End") == string::npos) {
					if (line[0] != '#')
						for (int i = 0; i < line.size(); i++)
							if (line[i] != ' ')
								sigma.push_back(line[i]);
					getline(fin, line);
				}
			}
			if (line.find("Transitions:") != string::npos) {
				getline(fin, line);
				while (line.find("End") == string::npos) {
					if (line[0] != '#') {
						int ind = -1;
						string state1 = extract_state(line, ind);
						char litera;
						for (int i = ind + 1; i < line.size(); i++)
							if (line[i] != ' ' && line[i] != ',') {
								litera = line[i];
								ind = i;
								break;
							}
						string state2 = extract_state(line.substr(ind + 1), ind);
						automat[state1].push_back({state2, litera});
					}
					getline(fin, line);
				}
			}
		}
	for (auto transition : automat) {
		if (find(states.begin(), states.end(), transition.first) == states.end()) {
			cout << "Automat Invalid!";
			return 0;
		}
		for (auto pair : transition.second) {
			if (find(states.begin(), states.end(), pair.first) == states.end()) {
				cout << "Automat Invalid!";
				return 0;
			}
			if (find(sigma.begin(), sigma.end(), pair.second) == sigma.end()) {
				cout << "Automat Invalid!";
				return 0;
			}
		}
	}
	for (auto state : states) {
		for (auto pair : automat[state]) {
			if (fr[pair.second] == 1) {
				cout << "Automat Finit Nedeterminist";
				return 0;
			}
			fr[pair.second] = 1;
		}
		fr.clear();
	}
	cout << "Automat Finit Determinist\n";
	cout << "Introduceti cuvantul de verificat: ";
	cin >> cuvant;
	string crt = start;
	for (int i = 0; i < cuvant.size(); i++) {
		string next;
		for (int j = 0; j < automat[crt].size(); j++)
			if (cuvant[i] == automat[crt][j].second) {
				next = automat[crt][j].first;
				break;
			}
		if (next.empty()) {
			cout << "Cuvant respins!";
			return 0;
		}
		crt = next;
	}
	if (!final[crt])
		cout << "Cuvant respins!";
	else
		cout << "Cuvant acceptat!";
	return 0;
}