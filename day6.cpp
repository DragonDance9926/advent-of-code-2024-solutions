#include <bits/stdc++.h>
using namespace std;

enum direction {UP, RIGHT, DOWN, LEFT};
vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};


bool isBorder(vector<string> &mp, pair<int, int> pos, direction dir){
    if (dir == UP){
        return pos.first == 0;
    }
    if (dir == DOWN){
        return pos.first == mp.size() - 1;
    }
    if (dir == LEFT){
        return pos.second == 0;
    }
    if (dir == RIGHT){
        return pos.second == mp[0].size() - 1;
    }
    return false;
}

int distance_h(pair<int, int> a, pair<int, int> b){
    //horizontal
    //return abs(a.second - b.second);
    return abs(a.second - b.second);
}
int distance_v(pair<int, int> a, pair<int, int> b){
    //vertical
    return abs(a.first - b.first);
}

bool isLoop(vector<string> &mp, pair<int, int> pos, unordered_set<string> &blocks){
    direction dir = UP;
    set<pair<pair<int, int>, direction>> visited;
    
    while (true){
        vector<pair<int, int>> next;
        for (auto &x: blocks){
            int i = stoi(x.substr(0, x.find(' ')));
            int j = stoi(x.substr(x.find(' ') + 1));
            switch (dir){
                case UP:
                    if (j == pos.second && i < pos.first){
                        next.push_back({i, j});
                    }
                    break;
                case DOWN:
                    if (j == pos.second && i > pos.first){
                        next.push_back({i, j});
                    }
                    break;
                case LEFT:
                    if (i == pos.first && j < pos.second){
                        next.push_back({i, j});
                    }
                    break;
                case RIGHT:
                    if (i == pos.first && j > pos.second){
                        next.push_back({i, j});
                    }
                    break;
            }
        }
        if (next.size() == 0){
            return false;
        }
        //sort
        if (dir == UP || dir == DOWN){
            sort(next.begin(), next.end(), [&](pair<int, int> a, pair<int, int> b){
                return distance_v(a, pos) < distance_v(b, pos);
            });
        }
        else{
            sort(next.begin(), next.end(), [&](pair<int, int> a, pair<int, int> b){
                return distance_h(a, pos) < distance_h(b, pos);
            });
        }
        pos = next[0];
        switch(dir){
            case UP:
                pos.first++;
                break;
            case DOWN:
                pos.first--;
                break;
            case LEFT:
                pos.second++;
                break;
            case RIGHT:
                pos.second--;
                break;
        }
        dir = (direction)((dir + 1) % 4);
        if (visited.find({pos, dir}) != visited.end()){
            return true;
        }
        visited.insert({pos, dir});
        
    }
    return false;
}
int main(){
    vector<string> mp;
    string line;
    fstream file = fstream("input.txt", ios::in);
    while (getline(file, line)){
        mp.push_back(line);
    }
    pair<int, int> pos;
    pair<int, int> pos_copy;
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == '^'){
                pos = {i, j};
                pos_copy = pos;
                break;
            }
        }
    }
    vector<string> mp_copy = mp;
    direction dir = UP;
    while (!isBorder(mp, pos, dir)){
        pair<int, int> next = {pos.first + directions[dir].first, pos.second + directions[dir].second};
        if (mp[next.first][next.second] == '#'){
            dir = (direction)((dir + 1) % 4);
        }
        else{
            pos = next;
        }
        mp[pos.first][pos.second] = 'X';
    }
    mp[pos.first][pos.second] = 'X';
    //Print
    for (auto &x: mp){
        cout << x << endl;
    }
    int sum = 0;
    //Count x
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == 'X'){
                sum++;
            }
        }
    }
    cout << "Part 1: " << sum << endl;
    mp = mp_copy;
    pos = pos_copy;
    sum = 0;
    unordered_set<string> blocks;
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[i].size(); j++){
            if (mp[i][j] == '#'){
                blocks.insert(to_string(i) + " " + to_string(j));
            }
        }
    }
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[i].size(); j++){
            //if ((mp.size() * i + j) % 1000 == 0) cout << (mp.size() * i + j) << " / " << (mp.size() * mp[i].size()) << endl;
            if (mp[i][j] == '.'){
                blocks.insert(to_string(i) + " " + to_string(j));
                mp[i][j] = '#';
                if (isLoop(mp, pos, blocks)){
                    
                    mp[i][j] = 'X';
                    
                    sum++;
                }
                mp[i][j] = '.';
                blocks.erase(to_string(i) + " " + to_string(j));
            }
        }
    }
    cout << "Part 2: " << sum << endl;

}