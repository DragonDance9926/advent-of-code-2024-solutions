#include <bits/stdc++.h>
using namespace std;



vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dfs (vector<string> &map, vector<vector<bool>> &visited, int x, int y, int px, int py, bool p2 = false){
    //cout << x << " " << y << endl;
    if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size() || visited[x][y]){
        return 0;
    }
    if (map[x][y] == '.'){
        return 0;
    }
    
    if ((px >= 0) && map[x][y] - map[px][py] != 1){
        return 0;
    }
    if (map[x][y] == '9'){
        if (!p2){
            visited[x][y] = true;
        }
        
        //cout << "Found 9 at " << x << " " << y << endl;
        return 1;
    }
    int res = 0;
    for (auto &[dx, dy]:dirs){
        visited[x][y] = true;
        res += dfs(map, visited, x + dx, y + dy, x, y, p2);
        visited[x][y] = false;
    }
    return res;

}


int main(){
    fstream file = fstream("input.txt", ios::in);
    string line;
    vector<string> map;
    while (getline(file, line)){
        map.push_back(line);
    }
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    int res = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[0].size(); j++){
            if (map[i][j] == '0'){
                int tmp = dfs(map, visited, i, j, -1, -1);
                //make all visited false
                for (int i = 0; i < visited.size(); i++){
                    for (int j = 0; j < visited[0].size(); j++){
                        visited[i][j] = false;
                    }
                }
                //cout << "tmp: " << tmp << endl;
                res += tmp;
            }
        }
    }
    cout << "Part 1: " << res << endl;
    res = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[0].size(); j++){
            if (map[i][j] == '0'){
                int tmp = dfs(map, visited, i, j, -1, -1,true);
                //make all visited false
                for (int i = 0; i < visited.size(); i++){
                    for (int j = 0; j < visited[0].size(); j++){
                        visited[i][j] = false;
                    }
                }
                //cout << "tmp: " << tmp << endl;
                res += tmp;
            }
        }
    }
    cout << "Part 2: " << res << endl;
}