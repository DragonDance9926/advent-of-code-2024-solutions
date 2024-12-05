#include <bits/stdc++.h>
using namespace std;

int main() {
    fstream file = fstream("input.txt", ios::in);
    vector<pair<int, int>> edges;
    vector<vector<int>> check;
    string line;
    while (getline(file, line)) {
        if (line == "") break;
        //a|b
        int n1 = stoi(line.substr(0, line.find('|')));
        int n2 = stoi(line.substr(line.find('|') + 1));
        edges.push_back({n1, n2});
    }
    while (getline(file, line)) {
        if (line == "") break;
        vector<int> temp;
        int x;
        string s;
        stringstream ss(line);
        while (getline(ss, s, ',')) {
            x = stoi(s);
            temp.push_back(x);
        }
        check.push_back(temp);
    }
    file.close();
    unordered_map<int, vector<int>> graph;
    for (auto &x : edges) {
        graph[x.first].push_back(x.second);
    }
    int sum = 0;
    for (auto &x: check){
        bool flag = true;
        int err_index = -1;
        for (int i = 0;flag && i < x.size(); i++){
            for (int j = i + 1; j < x.size(); j++){
                if (find(graph[x[i]].begin(), graph[x[i]].end(), x[j]) == graph[x[i]].end()){
                    flag = false;
                    break;
                }
            }
            
        }
        if (flag){
            sum += x[x.size() / 2];
        }
    }
    cout << "Part 1: " << sum << endl;
    sum = 0;
    for (auto &x: check){
        bool wasIncorrect = false;
        bool flag = true;
        while (flag){
            flag = false;
            int err_index = -1;
            for (int i = 0;!flag && i < x.size(); i++){
                for (int j = i + 1; j < x.size(); j++){
                    if (find(graph[x[i]].begin(), graph[x[i]].end(), x[j]) == graph[x[i]].end()){
                        flag = true;
                        wasIncorrect = true;
                        //swap(x[i], x[j]);
                        auto temp = x[i];
                        x[i] = x[j];
                        x[j] = temp;

                        break;
                    }
                }
                
            }
        }
        if (wasIncorrect){
            sum += x[x.size() / 2];
        }
    }
    cout << "Part 2: " << sum << endl;
    return 0;
}