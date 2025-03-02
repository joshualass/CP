#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    cout << fixed << setprecision(50);

    int t; cin >> t;
    while(t--){
        int n, m; cin >> n >> m;

        // build the cars map
        unordered_map<string, vector<int>> cars;
        for(int idx = 0; idx < n; ++idx){
            string name; int p, q, k; cin >> name >> p >> q >> k;
            cars[name] = {p, q, k};
        }
        
        // process events
        unordered_map<string, string> driving;
        unordered_map<string, int> bill;
        unordered_set<string> inUse;

        vector<pair<int, string>> quer;
        while(m--){
            int stTime; string line; cin >> stTime;
            getline(cin, line);

            quer.push_back({stTime, line});
        }

        sort(quer.begin(), quer.end());

        for (auto line: quer){
            istringstream fin(line.second);
            // cout << "line: " << line.second << endl;

            // int stTime = line.first;
            string person; char e; fin >> person >> e;
            // cout << "information: " << stTime << " " << person << " " << e << endl;

            // rent
            if (e == 'p'){
                // cout << "renting " << endl;
                string carUsed; fin >> carUsed;

                if (bill[person] == -1)
                    continue;

                // test if spy already driving or car in use
                if (driving.find(person) != driving.end() || (inUse.find(carUsed) != inUse.end())){
                    bill[person] = -1;
                }
                else {
                    driving[person] = carUsed;
                    inUse.insert(carUsed);

                    // add pickup cost
                    bill[person] += cars[carUsed][1];
                }

            }

            // return
            else if (e == 'r'){
                // cout << "returning" << endl;
                int d; fin >> d;

                if (bill[person] == -1)
                    continue;

                // person wasn't driving a car
                if (driving.find(person) == driving.end()){
                    bill[person] = -1;
                }

                else {
                    // add the cost per mile
                    bill[person] += cars[driving[person]][2] * d;
                    // remove the car from sets
                    inUse.erase(driving[person]);
                    driving.erase(person);
                }

            }

            // accident
            else if (e == 'a'){
                // cout << "crashing " << endl;
                int s; fin >> s;

                if (bill[person] == -1)
                    continue;

                // errors: no car in use
                if (driving.find(person) == driving.end()){
                    bill[person] = -1;
                }

                else {
                    // add the crash cost
                    bill[person] += ceil((double)cars[driving[person]][0] * s / 100);
                }
            }

            // cout << "total spies driving: " << driving.size() << endl;
            // cout << "total cars in use" << inUse.size() << endl;

        }

        // error : car was not returned
        for (auto& entry : driving){
            bill[entry.first] = -1;
        }

        vector<string> ans;
        for (auto & ppl : bill){
            string newSpy = ppl.first + " ";
            if (ppl.second == -1){
                newSpy += "INCONSISTENT";
            }
            else {
                newSpy += to_string(ppl.second);
            }
            ans.push_back(newSpy);
        }

        sort(ans.begin(), ans.end());
        for (auto val : ans){
            cout << val << endl;
        }

        // cases: car already in use, spy already driving, spy not driving and returns
        // spy doesn't return, accident happen when not using car
        // spy returns the wrong car

        // two accidents back-to-back
    }
    
}