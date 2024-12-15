#include <bits/stdc++.h>
using namespace std;



pair<vector<pair<int, int>>, bool> bfs (vector<string> &map,vector<vector<bool>> &visited, int i , int j, pair<int, int> &movement){
    if (map[i][j] == '#'){
        return {{}, false};
    }
    if (map[i][j] == '.'){
        return {{}, true};
    }
    pair<vector<pair<int, int>>, bool> adj = {{}, true};
    visited[i][j] = true;
    if (map[i][j] == '[' && !visited[i][j + 1]){
        adj = bfs(map,visited, i, j + 1, movement);
    }
    else if (map[i][j] == ']' && !visited[i][j - 1]){
        adj = bfs(map,visited, i, j - 1, movement);
    }
    pair<vector<pair<int, int>>, bool> adj2 = bfs(map,visited, i + movement.first, j + movement.second, movement);
    auto &[v1, b1] = adj;
    auto &[v2, b2] = adj2;
    if (!b1 || !b2){
        return {{}, false};
    }
    v1.insert(v1.end(), v2.begin(), v2.end());
    v1.push_back({i, j});
    return {v1, true};
}





int main(){
    vector<string> map, map_copy;
    fstream file = fstream("input.txt", ios::in);
    string movements;
    string line;
    while (getline(file, line)){
        if (line.empty()){
            break;
        }
        map.push_back(line);
    }
    map_copy = map;
    while (getline(file, line)){
        movements += line;
    }
    file.close();
    const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int x = 0, y = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }
    for (auto &ch: movements){
        pair<int, int> next = {x, y};
        pair<int, int> d;
        switch (ch){
            case '^':
                d = directions[0];
                break;
            case 'v':
                d = directions[1];

                break;
            case '<':
                d = directions[2];
                break;
            case '>':
                d = directions[3];
                break;
        }
        next = {next.first + d.first, next.second + d.second};
        while (map[next.first][next.second] == 'O'){
            next.first += d.first;
            next.second += d.second;
        }
        if (map[next.first][next.second] == '#' || map[next.first][next.second] == '@'){
            continue;
        }
        while (next.first != x || next.second != y){
            swap(map[next.first][next.second], map[next.first - d.first][next.second - d.second]);
            next.first -= d.first;
            next.second -= d.second;
        }
        x += d.first;
        y += d.second;
        
    }
    
    int res = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] == 'O'){
                res += 100 * i + j;
            }
        }
    }
    cout << "Part 1: " << res << endl;
    map = map_copy;
    vector<string> n_map;
    for (auto &line: map){
        string l = "";
        for (auto &ch: line){
            switch (ch){
                case '#':
                    l += "##";
                    break;
                case 'O':
                    l += "[]";
                    break;
                case '.':
                    l += "..";
                    break;
                case '@':
                    l += "@.";
                    break;
            }
        }
        n_map.push_back(l);
    }
    map = n_map;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }
    for (auto &ch: movements){
        pair<int, int> next = {x, y};
        pair<int, int> d;
        bool up_down = false;
        switch (ch){
            case '^':
                d = directions[0];
                up_down = true;
                break;
            case 'v':
                d = directions[1];
                up_down = true;
                break;
            case '<':
                d = directions[2];
                break;
            case '>':
                d = directions[3];
                break;
        }
        next = {next.first + d.first, next.second + d.second};
        if (!up_down){
            while (map[next.first][next.second] == '[' || map[next.first][next.second] == ']'){
                next.first += d.first;
                next.second += d.second;
            }
            if (map[next.first][next.second] == '#' || map[next.first][next.second] == '@'){
                continue;
            }
            while (next.first != x || next.second != y){
                swap(map[next.first][next.second], map[next.first - d.first][next.second - d.second]);
                next.first -= d.first;
                next.second -= d.second;
            }
        }
        else{
            vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
            pair<vector<pair<int, int>>, bool> adj = bfs(map, visited, next.first, next.second, d);
            if (!adj.second){
                continue;
            }
            auto copy = map;
            for (auto &[i, j]: adj.first){
                copy[i][j] = '.';
            }
            for (auto &[i, j]: adj.first){
                copy[i + d.first][j + d.second] = map[i][j];
            }
            copy[x][y] = '.';
            copy[x + d.first][y + d.second] = '@';
            map = copy;
        }
        
        x += d.first;
        y += d.second;
    }
    res = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] == '['){
                res += 100 * i + j;
            }
        }
    }
    cout << "Part 2: " << res << endl;
    
}