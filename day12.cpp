#include <bits/stdc++.h>
using namespace std;

void dfs(vector<string> &map, vector<vector<int>> &groups, int x, int y, char c, int g, unordered_map<int, int> &areas){
    if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size() || map[x][y] != c || groups[x][y] != 0){
        return;
    }
    groups[x][y] = g;
    areas[g]++;
    dfs(map, groups, x+1, y, c, g, areas);
    dfs(map, groups, x-1, y, c, g, areas);
    dfs(map, groups, x, y+1, c, g, areas);
    dfs(map, groups, x, y-1, c, g, areas);
}

int main(){
    fstream file = fstream("input.txt", ios::in);
    string line;
    vector<string> v;
    while (getline(file, line)){
        v.push_back(line);
    }
    file.close();
    unordered_map<char, vector<int>> m;
    //add a border of white space
    vector<vector<int>> groups (v.size(), vector<int>(v[0].size(), 0));
    unordered_map<int, int> areas;
    int g = 1;
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v[i].size(); j++){
            if (groups[i][j] == 0){
                m[v[i][j]].push_back(g);
                dfs(v, groups, i, j, v[i][j], g, areas);
                g++;
            }
        }
    }
    unordered_map<int, int> perimeters;
    for (int i = 0; i < groups.size(); i++){
        for (int j = 0; j < groups[0].size(); j++){
            if (groups[i][j] != 0){
                perimeters[groups[i][j]] += 4;
                if (i > 0 && groups[i-1][j] != 0 && groups[i-1][j] == groups[i][j]){
                    perimeters[groups[i][j]] -= 2;
                }
                if (j > 0 && groups[i][j-1] != 0 && groups[i][j-1] == groups[i][j]){
                    perimeters[groups[i][j]] -= 2;
                }
            }
        }
    }
    int res = 0;
    for (auto &x : perimeters){
        //cout << x.first << " " << x.second <<" " << areas[x.first] << endl;
        res += x.second * areas[x.first];
    }
    cout << "Part 1: " << res << endl;
    res = 0;
    perimeters.clear();
    vector<vector<bool>> visited (groups.size(), vector<bool>(groups[0].size(), false));
    for (int i = 0; i < groups.size(); i++){
        for (int j = 0; j < groups[0].size(); j++){
            //check adjacent cells
            bool left = j > 0 && groups[i][j-1] == groups[i][j];
            bool right = j < groups[0].size()-1 && groups[i][j+1] == groups[i][j];
            bool up = i > 0 && groups[i-1][j] == groups[i][j];
            bool down = i < groups.size()-1 && groups[i+1][j] == groups[i][j];
            int p = left + right + up + down;
            switch (p){
                case 0:
                    perimeters[groups[i][j]] += 4;
                    break;
                case 1:
                    perimeters[groups[i][j]] += 2;
                    break;
                case 2:
                    if ((left && right) || (up && down)){
                        perimeters[groups[i][j]] += 0;
                    }
                    else{
                        perimeters[groups[i][j]] += 2;
                        
                    }
                    break;
                case 3:
                    perimeters[groups[i][j]] += 2;
                    break;
                case 4:
                    perimeters[groups[i][j]] += 4;
                    break;
                default:
                    break;
            }
            if (left && up){
                if (i > 0 && j > 0 && groups[i-1][j-1] == groups[i][j]){
                    perimeters[groups[i][j]]--;
                }
            }
            if (left && down){
                if (i < groups.size()-1 && j > 0 && groups[i+1][j-1] == groups[i][j]){
                    perimeters[groups[i][j]]--;
                }

            }
            if (right && up){
                if (i > 0 && j < groups[0].size()-1 && groups[i-1][j+1] == groups[i][j]){
                    perimeters[groups[i][j]]--;
                }

            }
            if (right && down){
                if (i < groups.size()-1 && j < groups[0].size()-1 && groups[i+1][j+1] == groups[i][j]){
                    perimeters[groups[i][j]]--;
                }
            }
        }
    }
    for (auto &x : perimeters){
        //cout << x.first << " " << x.second <<" " << areas[x.first] << endl;
        res += x.second * areas[x.first];
    }
    cout << "Part 2: " << res << endl;
    return 0;
}