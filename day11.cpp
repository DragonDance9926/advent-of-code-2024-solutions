#include <bits/stdc++.h>
using namespace std;



int main(){
    string line;
    fstream file = fstream("input.txt", ios::in);
    //one line of input
    vector<string> v;
    unordered_map<string, long long> m;
    getline(file, line);
    file.close();
    stringstream ss(line);
    string temp;
    while (getline(ss, temp, ' ')){
        v.push_back(temp);
        m[temp]++;
    }
    for (int i = 0; i < 25; i++){
        vector<string> v1;
        for (int j = 0; j < v.size(); j++){
            long long val = stoll(v[j]);
            if (val == 0){
                v1.push_back("1");
            }
            else if (v[j].size() % 2 == 0){
                long long first_half = stoll(v[j].substr(0, v[j].size() / 2));
                long long second_half = stoll(v[j].substr(v[j].size() / 2, v[j].size() / 2));
                v1.push_back(to_string(first_half));
                v1.push_back(to_string(second_half));
            }
            else{
                v1.push_back(to_string(val * 2024));
            }
        }
        v = v1;
    }
    cout << v.size() << endl;
    for (int i = 0; i < 75; i++){
        unordered_map<string, long long> m1;
        for (auto &[k, v]: m){
            long long val = stoll(k);
            if (val == 0){
                m1["1"] += v;
            }
            else if (k.size() % 2 == 0){
                long long first_half = stoll(k.substr(0, k.size() / 2));
                long long second_half = stoll(k.substr(k.size() / 2, k.size() / 2));
                m1[to_string(first_half)] += v;
                m1[to_string(second_half)] += v;
            }
            else{
                m1[to_string(val * 2024)] += v;
            }
        }
        m = m1;
    }
    long long res = 0;
    for (auto &[k, v]: m){
        res += v;
    }
    cout << res << endl;
    return 0;
}