#include <bits/stdc++.h>
using namespace std;


vector<char> _state {'X', 'M', 'A', 'S'};
bool isHorizontal(vector<pair<int, int>> &v){
    for (int i = 0; i < v.size() - 1; i++){
        if (v[i].first != v[i + 1].first) return false;
    }
    return true;
}

bool isVertical(vector<pair<int, int>> &v){
    for (int i = 0; i < v.size() - 1; i++){
        if (v[i].second != v[i + 1].second) return false;
    }
    return true;
}

bool isDiagonal(vector<pair<int, int>> &v, bool startfromtop = false){
    // find / diagonal
    int x = v[0].first;
    int y = v[0].second;
    for (int i = 1; i < v.size(); i++){
        if (startfromtop){
            x--;
            y++;
        }
        else{
            x++;
            y--;
        }
        if (v[i].first != x || v[i].second != y) return false;
    }
    return true;
}

bool isDiagonal2(vector<pair<int, int>> &v, bool startfromtop = false){
    // find \ diagonal
    int x = v[0].first;
    int y = v[0].second;
    for (int i = 1; i < v.size(); i++){
        if (startfromtop){
            x--;
            y--;
        }
        else{
            x++;
            y++;
        }
        if (v[i].first != x || v[i].second != y) return false;
    }
    return true;
}


int main(){
    fstream file = fstream("input.txt", ios::in);
    vector<string> mp;
    string line;
    while(getline(file, line)){
        //cout << line << endl;
        mp.push_back(line);
    }
    file.close();
    stack<tuple<int, int, int, vector<pair<int, int>>>> s;
    int ans = 0;
    for (int i = 0; i < mp.size(); i++){
        for (int j = 0; j < mp[0].size(); j++){
            if (mp[i][j] == 'X'){
                s.push({i, j, 1, vector<pair<int, int>>{{i, j}}});
            }
        }
    }
    while(!s.empty()){
        auto [i, j, d, p] = s.top();
        s.pop();
        if (d == _state.size()){
            bool flag = isHorizontal(p) || isVertical(p) || isDiagonal(p, false) || isDiagonal(p, true) || isDiagonal2(p, false) || isDiagonal2(p, true);
            if (flag){
                ans++;
            }
            continue;
        }
        for (int di = -1; di <= 1; di++){
            for (int dj = -1; dj <= 1; dj++){
                if (di == 0 && dj == 0) continue;
                int ni = i + di;
                int nj = j + dj;
                if (ni < 0 || ni >= mp.size() || nj < 0 || nj >= mp[0].size()) continue;
                if (mp[ni][nj] == _state[d]){
                    vector<pair<int, int>> temp = p;
                    temp.push_back({ni, nj});
                    s.push({ni, nj, d + 1, temp});
                }
            }
        }
    }
    cout << "Part 1: " << ans << endl;

    ans = 0;
    for (int i = 1; i < mp.size() - 1; i++){
        for (int j = 1; j < mp[0].size() - 1; j++){
            if (mp[i][j] == 'A'){
                char top_left = mp[i - 1][j - 1];
                char top_right = mp[i - 1][j + 1];
                char bottom_left = mp[i + 1][j - 1];
                char bottom_right = mp[i + 1][j + 1];
                bool f1 = (top_left == 'M' && bottom_right == 'S') || (top_left == 'S' && bottom_right == 'M');
                bool f2 = (bottom_left == 'M' && top_right == 'S') || (bottom_left == 'S' && top_right == 'M');
                if (f1 && f2){
                    //cout << i << " " << j << endl;
                    ans++;
                }
            }
        }
    }
    cout << "Part 2: " << ans << endl;


}