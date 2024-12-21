#include <bits/stdc++.h>
using namespace std;

bool isInBounds(int i, int j, vector<string> &k){
    return i >= 0 && i < k.size() && j >= 0 && j < k[0].size() && k[i][j] != ' ';
}

unordered_map<char, pair<int, int>> dir = {
    {'^', {-1, 0}},
    {'v', {1, 0}},
    {'<', {0, -1}},
    {'>', {0, 1}}
};

string pfs(string &seq, vector<string> &k1, char k1i, vector<string> &k2, char k2i, vector<string> &k3, char k3i){
    pair<int, int> pos1, pos2, pos3;
    for(int i = 0; i < k1.size(); i++){
        for(int j = 0; j < k1[i].size(); j++){
            if(k1[i][j] == k1i){
                pos1 = {i, j};
                break;
            }
        }
    }
    for(int i = 0; i < k2.size(); i++){
        for(int j = 0; j < k2[i].size(); j++){
            if(k2[i][j] == k2i){
                pos2 = {i, j};
                break;
            }
        }
    }
    for (int i = 0; i < k3.size(); i++){
        for (int j = 0; j < k3[i].size(); j++){
            if (k3[i][j] == k3i){
                pos3 = {i, j};
                break;
            }
        }
    }
    //ind, path, pos1, pos2, pos3
    auto cmp = [](tuple<string, int, pair<int, int>, pair<int, int>, pair<int, int>> &a, tuple<string, int, pair<int, int>, pair<int, int>, pair<int, int>> &b){
        return get<0>(a).size() > get<0>(b).size();
    };
    priority_queue<tuple<string, int, pair<int, int>, pair<int, int>, pair<int, int>>, vector<tuple<string, int, pair<int, int>, pair<int, int>, pair<int, int>>>, decltype(cmp)> pq(cmp);
    pq.push({"", 0, pos1, pos2, pos3});
    set<tuple<int, pair<int, int>, pair<int, int>, pair<int, int>>> visited;
    while(!pq.empty()){
        auto [path, ind, pos1, pos2, pos3] = pq.top();
        pq.pop();
        if(ind == seq.size()){
            path.pop_back();
            return path;
        }
        auto [i1, j1] = pos1;
        auto [i2, j2] = pos2;
        auto [i3, j3] = pos3;
        if (i1 < 0 || i1 >= k1.size() || j1 < 0 || j1 >= k1[0].size() || k1[i1][j1] == ' '){
            continue;
        }
        if (i2 < 0 || i2 >= k2.size() || j2 < 0 || j2 >= k2[0].size() || k2[i2][j2] == ' '){
            continue;
        }
        if (i3 < 0 || i3 >= k3.size() || j3 < 0 || j3 >= k3[0].size() || k3[i3][j3] == ' '){
            continue;
        }
        if (visited.count({ind, pos1, pos2, pos3})){
            continue;
        }
        visited.insert({ind, pos1, pos2, pos3});
        if (k3[i3][j3] != 'A'){
            pq.push({path + "A", ind, {i1, j1}, {i2 + dir[k3[i3][j3]].first, j2 + dir[k3[i3][j3]].second}, {i3, j3}});
        }
        else if (k3[i3][j3] == 'A'){
            if (k2[i2][j2] != 'A'){
                pq.push({path + "A", ind, {i1 + dir[k2[i2][j2]].first, j1 + dir[k2[i2][j2]].second}, {i2, j2}, {i3, j3}});
            }
            else if (k2[i2][j2] == 'A'){
                if (k1[i1][j1] == seq[ind]){
                    ind++;
                    path += "A";
                }
            }
            else{
                cout << "Error" << endl;
            }
        }
        else{
            cout << "Error" << endl;
        }
        for (auto &[k, v]: dir){
            pq.push({path + k, ind, {i1,j1}, {i2, j2}, {i3 + v.first, j3 + v.second}});
        }
    }
    return "";
}
//<vA<AA>>^AvAA^<A>Av<<A>^>AvA^Av<A^>A<Av<A>^>AAvA^A<v<A>A>^AAA<Av>A^A>
//<vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A
int main(){
    string s = "029A";
    vector<string> k1 = {
        "789",
        "456",
        "123",
        " 0A"
    };
    vector<string> k2 = {
        " ^A",
        "<v>"
    };
    fstream file("input.txt");
    vector<string> lines;
    while(getline(file, s)){
        lines.push_back(s);
    }
    file.close();
    int res = 0;
    for (auto &s: lines){
        int r = pfs(s, k1, 'A', k2, 'A', k2, 'A').size();
        cout << r << " " << stoi(s.substr(0, 3)) << endl;
        res += r * stoi(s.substr(0, 3));
    }
    cout << res << endl;
}