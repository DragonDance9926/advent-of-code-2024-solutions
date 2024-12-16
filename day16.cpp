#include <bits/stdc++.h>
using namespace std;
enum direction {NORTH, EAST, SOUTH, WEST};
const vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};


string to_string(pair<int, int> pos, enum direction dir){
    return to_string(pos.first) + " " + to_string(pos.second) + " " + to_string(dir);
}
string to_string(pair<int, int> pos){
    return to_string(pos.first) + " " + to_string(pos.second);
}

unordered_set<string> seen2;

void dfs (vector<string>& _map, vector<vector<vector<bool>>> &visited, pair<int, int> pos, enum direction dir, int steps, int min_steps, unordered_set<string> &seen){
    auto [x, y] = pos;
    if (min_steps < steps){
        return;
    }
    
    if (x < 0 || x >= _map.size() || y < 0 || y >= _map[x].size() || visited[x][y][dir]){
        return;
    }
    if (_map[x][y] == '#'){
        return;
    }
    seen.insert(to_string({x, y}, dir));
    if (_map[x][y] == 'E'){
        //min_steps = min(min_steps, steps);
        if (steps == min_steps){
            for (auto &s : seen){
                int x, y, dir;
                stringstream ss(s);
                ss >> x >> y >> dir;
                seen2.insert(to_string({x, y}));
            }
            //cout << endl;
        }
        return;
    }
    
    visited[x][y][dir] = true;
    
    //go along the same direction
    
    enum direction left = static_cast<direction>((dir + 3) % 4);
    enum direction right = static_cast<direction>((dir + 1) % 4);

    
    dfs(_map, visited, {x, y}, left, steps + 1000, min_steps, seen);
    dfs(_map, visited, {x, y}, right, steps + 1000, min_steps, seen);
    dfs(_map, visited, {x + dirs[dir].first, y + dirs[dir].second}, dir, steps + 1, min_steps, seen);
    seen.erase(to_string({x, y}, dir));
    visited[x][y][dir] = false;
}






int main(){
    vector<string> _map;
    fstream file = fstream("input.txt", ios::in);
    string line;
    while (getline(file, line)){
        _map.push_back(line);
    }
    file.close();
    pair<int, int> pos = {0, 0}, pos_copy;
    bool found = false;
    for (int i = 0;!found && i < _map.size(); i++){
        for (int j = 0;!found && j < _map[i].size(); j++){
            if (_map[i][j] == 'S'){
                pos = {i, j};
                found = true;
            }
        }
    }
    tuple<int, pair<int, int>, enum direction> start = {0, pos, EAST};
    //min heap
    priority_queue<tuple<int, pair<int, int>, enum direction>, vector<tuple<int, pair<int, int>, enum direction>>, greater<tuple<int, pair<int, int>, enum direction>>> pq;
    vector<vector<vector<bool>>> visited(_map.size(), vector<vector<bool>>(_map[0].size(), vector<bool>(4, false)));
    pq.push(start);
    int min_steps = INT_MAX;
    while (!pq.empty()){
        auto [steps, pos, dir] = pq.top();
        pq.pop();
        auto [x, y] = pos;
        if (x < 0 || x >= _map.size() || y < 0 || y >= _map[x].size() || visited[x][y][dir]){
            continue;
        }
        if (_map[x][y] == '#'){
            continue;
        }
        if (_map[x][y] == 'E'){
            min_steps = steps;
            break;
        }
        visited[x][y][dir] = true;
        //go along the same direction
        pq.push({steps + 1, {x + dirs[dir].first, y + dirs[dir].second}, dir});
        enum direction left = static_cast<direction>((dir + 3) % 4);
        enum direction right = static_cast<direction>((dir + 1) % 4);

        //turn left
        pq.push({steps + 1000, {x, y}, left});
        //turn right
        pq.push({steps + 1000, {x, y}, right});
        
    }
    cout << min_steps << endl;
    //part 2
    unordered_set<string> seen;
    for (int i = 0; i < visited.size(); i++){
        for (int j = 0; j < visited[i].size(); j++){
            for (int k = 0; k < visited[i][j].size(); k++){
                visited[i][j][k] = false;
            }
        }
    }
    dfs(_map, visited, pos, EAST, 0, min_steps, seen);
    cout << seen2.size() << endl;

    return 0;
}