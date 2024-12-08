#include <bits/stdc++.h>
using namespace std;



int main(){
    vector<string> map, map2;
    string line;
    fstream file = fstream("input.txt", ios::in);
    while (getline(file, line)){
        map.push_back(line);
        map2.push_back(line);
    }
    file.close();
    unordered_map<char, vector<pair<int,int>>> groups;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            if (map[i][j] != '.'){
                groups[map[i][j]].push_back({i,j});
            }
        }
    }
    for (auto &[k, v]: groups){
        for (int i = 0; i < v.size(); i++){
            for (int j = i + 1; j < v.size(); j++){
                auto [x1, y1] = v[i];
                auto [x2, y2] = v[j];
                //cout << "Points: " << x1 << " " << y1 << "," << x2 << " " << y2 << endl;
                int dx = x2 - x1;
                int dy = y1 - y2;
                int x1_, y1_, x2_, y2_;
                char case_;
                if (dx < 0){
                    swap(x1, x2);
                    swap(y1, y2);
                    cout << "Swapped" << endl;
                }
                if (dy < 0){
                    // x1 above x2, y1 left of y2
                    // the line of : \\
                    //Create two points
                    //x1 - abs(dx), y1 - abs(dy)
                    //x2 + abs(dx), y2 + abs(dy)
                    x1_ = x1 - abs(dx);
                    y1_ = y1 - abs(dy);
                    x2_ = x2 + abs(dx);
                    y2_ = y2 + abs(dy);
                    
                    //Mark these points with a #
                    if (x1_ >= 0 && x1_ < map.size() && y1_ >= 0 && y1_ < map[x1_].size() ){
                        map[x1_][y1_] = '#';
                    }
                    if (x2_ >= 0 && x2_ < map.size() && y2_ >= 0 && y2_ < map[x2_].size() ){
                        map[x2_][y2_] = '#';
                    }
                    case_ = '1';
                }
                else{
                    // x1 below x2, y1 left of y2
                    // the line of : //
                    //Create two points
                    //x1 + abs(dx), y1 - abs(dy)
                    //x2 - abs(dx), y2 + abs(dy)
                    x1_ = x1 -abs(dx);
                    y1_ = y1 + abs(dy);
                    x2_ = x2 + abs(dx);
                    y2_ = y2 - abs(dy);
                    //Mark these points with a #
                    if (x1_ >= 0 && x1_ < map.size() && y1_ >= 0 && y1_ < map[x1_].size() ){
                        map[x1_][y1_] = '#';
                    }
                    if (x2_ >= 0 && x2_ < map.size() && y2_ >= 0 && y2_ < map[x2_].size() ){
                        map[x2_][y2_] = '#';
                    }
                    case_ = '2';
                }
                //cout << "Point 1: " << x1_ << " " << y1_ << endl;
                //cout << "Point 2: " << x2_ << " " << y2_ << endl;
                //cout << "Case: " << case_ << endl;
            }
        }
    }
    //Print map
    int count = 0;
    for (auto &s : map){
        for (auto &c : s){
            if (c == '#'){
                count++;
            }
        }
    }
    cout << "Part 1: " << count << endl;
    count = 0;
    map = map2;
    for (auto &[k, v]: groups){
        for (int i = 0; i < v.size(); i++){
            for (int j = i + 1; j < v.size(); j++){
                auto [x1, y1] = v[i];
                auto [x2, y2] = v[j];
                //cout << "Points: " << x1 << " " << y1 << "," << x2 << " " << y2 << endl;
                int dx = x2 - x1;
                int dy = y1 - y2;
                int x1_, y1_, x2_, y2_;
                char case_;
                map[x1][y1] = '#';
                map[x2][y2] = '#';
                if (dx < 0){
                    swap(x1, x2);
                    swap(y1, y2);
                    cout << "Swapped" << endl;
                }
                if (dy < 0){
                    // x1 above x2, y1 left of y2
                    // the line of : \\
                    //Create two points
                    //x1 - abs(dx), y1 - abs(dy)
                    //x2 + abs(dx), y2 + abs(dy)
                    x1_ = x1 - abs(dx);
                    y1_ = y1 - abs(dy);
                    x2_ = x2 + abs(dx);
                    y2_ = y2 + abs(dy);
                    
                    //Mark these points with a #
                    while (x1_ >= 0 && x1_ < map.size() && y1_ >= 0 && y1_ < map[x1_].size() ){
                        map[x1_][y1_] = '#';
                        x1_ -= abs(dx);
                        y1_ -= abs(dy);
                    }
                    while (x2_ >= 0 && x2_ < map.size() && y2_ >= 0 && y2_ < map[x2_].size() ){
                        map[x2_][y2_] = '#';
                        x2_ += abs(dx);
                        y2_ += abs(dy);
                    }
                    case_ = '1';
                }
                else{
                    // x1 below x2, y1 left of y2
                    // the line of : //
                    //Create two points
                    //x1 + abs(dx), y1 - abs(dy)
                    //x2 - abs(dx), y2 + abs(dy)
                    x1_ = x1 -abs(dx);
                    y1_ = y1 + abs(dy);
                    x2_ = x2 + abs(dx);
                    y2_ = y2 - abs(dy);
                    //Mark these points with a #
                    while (x1_ >= 0 && x1_ < map.size() && y1_ >= 0 && y1_ < map[x1_].size() ){
                        map[x1_][y1_] = '#';
                        x1_ -= abs(dx);
                        y1_ += abs(dy);
                    }
                    while (x2_ >= 0 && x2_ < map.size() && y2_ >= 0 && y2_ < map[x2_].size() ){
                        map[x2_][y2_] = '#';
                        x2_ += abs(dx);
                        y2_ -= abs(dy);
                    }
                    case_ = '2';
                }
                //cout << "Point 1: " << x1_ << " " << y1_ << endl;
                //cout << "Point 2: " << x2_ << " " << y2_ << endl;
                //cout << "Case: " << case_ << endl;
            }
        }
    }
    //Print map
    for (auto &s : map){
        for (auto &c : s){
            if (c == '#'){
                count++;
            }
        }
    }
    cout << "Part 2: " << count << endl;
    return 0;
}