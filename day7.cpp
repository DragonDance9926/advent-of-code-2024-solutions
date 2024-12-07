#include <bits/stdc++.h>
using namespace std;

bool isPossible (pair<long long,vector<long long>> &p,bool tristate = false, long long index = 0, long long val = 0){
    //cout << index << " " << val << endl;
    if (index == p.second.size()){
        return val == p.first;
    }
    if (index == 0){
        return isPossible(p, tristate, index + 1, p.second[index]);
    }
    return isPossible(p,tristate, index + 1, val + p.second[index]) || isPossible(p,tristate, index + 1, val * p.second[index])|| (
        tristate && isPossible(p,tristate, index + 1, stoll(to_string(val) + to_string(p.second[index])))
    );
}




int main(){
    vector<pair<long long,vector<long long>>> v;
    string line;
    fstream file = fstream("input.txt", ios::in);
    while (getline(file, line)){
        long long n1 = stoll(line.substr(0, line.find(":")));
        line = line.substr(line.find(":") + 2);
        vector<long long> v1;
        stringstream ss(line);
        string temp;
        while (getline(ss, temp, ' ')){
            v1.push_back(stoi(temp));
        }
        v.push_back({n1, v1});
    }
    file.close();
    long long sum = 0;
    long long sum2 = 0;
    for (auto &p : v){
        
        if (isPossible(p)){
            //cout << p.first << endl;
            sum += p.first;
        }
        if (isPossible(p, true)){
            //cout << p.first << endl;
            sum2 += p.first;
        }
    }
    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << sum2 << endl;
    return 0;
}