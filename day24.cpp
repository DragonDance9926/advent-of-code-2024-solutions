#include <bits/stdc++.h>
#include <regex>
using namespace std;

//REGEX: (\w+) (\w+) (\w+) -> (\w+)





int main(){
    fstream file;
    file.open("input.txt");
    string line;
    map<string, int> m;
    while (getline(file, line)){
        if (line == "") break;
        string var = line.substr(0, 3);
        string val = line.substr(line.find(" ") + 1);
        m[var] = stoi(val);
    }
    vector<tuple<string, string, string, string>> v;
    regex r("(\\w+) (\\w+) (\\w+) -> (\\w+)");
    while (getline(file, line)){
        if (line == "") break;
        smatch m1;
        regex_match(line, m1, r);
        v.push_back({m1[1], m1[2], m1[3], m1[4]});
    }
    file.close();
    while (v.size() > 0){
        vector<int> to_delete;
        for (int i = 0; i < v.size(); i++){
            auto &[a, op, b, c] = v[i];
            if (m.find(a) != m.end() && m.find(b) != m.end()){
                if (op == "AND") {m[c] = m[a] & m[b];}
                else if (op == "OR") {m[c] = m[a] | m[b];}
                else if (op == "XOR") {m[c] = m[a] ^ m[b];}
                else {m[c] = m[b];}
                to_delete.push_back(i);
            }
        }
        for (int i = to_delete.size() - 1; i >= 0; i--){
            v[to_delete[i]] = {"", "", "", ""};
        }
        v.erase(remove(v.begin(), v.end(), tuple<string, string, string, string>{"", "", "", ""}), v.end());

    }
    string res = "";
    for (auto [k,v]: m){
        if (k[0] == 'z'){
            res += to_string(v);
        }
    }
    reverse(res.begin(), res.end());
    //write in decimal
    cout << res << endl;
    cout << stoull(res, 0, 2) << endl;
    return 0;

}