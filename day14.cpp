#include <bits/stdc++.h>
#include <regex>
using namespace std;
//regex: p=(\d+),(\d+) v=([+|-]?\d+),([+|-]?\d+)


string to_string(pair<int, int> p){
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

int main(){
    fstream file = fstream("input.txt", ios::in);
    vector<pair<pair<int, int>, pair<int, int>>> lines, lines2;
    regex lineRegex("p=(\\d+),(\\d+) v=([+|-]?\\d+),([+|-]?\\d+)");
    smatch lineMatch;
    string line;
    while (getline(file, line)){
        if (regex_match(line, lineMatch, lineRegex)){
            lines.push_back({{stoll(lineMatch[1]), stoll(lineMatch[2])}, {stoll(lineMatch[3]), stoll(lineMatch[4])}}); 
        }
    }
    file.close();
    lines2 = lines;
    int width = 101;
    int height = 103;
    for (int i = 0; i < 100; i++){
        for (auto &[p1, p2] : lines){
            p1.first += p2.first;
            p1.second += p2.second;
            if (p1.first < 0){
                p1.first += width;
            }
            else if (p1.first >= width){
                p1.first %= width;
            }
            if (p1.second < 0){
                p1.second += height;
            }
            else if (p1.second >= height){
                p1.second %= height;
            }

        }
    }
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (auto [p1, p2] : lines){
        if (p1.first == width / 2 || p1.second == height / 2){
            continue;
        }
        //cout << p1.first << " " << p1.second << " " << p2.first << " " << p2.second << endl;
        if (p1.first < width / 2 && p1.second < height / 2){
            q1++;
        }
        else if (p1.first < width / 2 && p1.second > height / 2){
            q2++;
        }
        else if (p1.first > width / 2 && p1.second < height / 2){
            q3++;
        }
        else{
            q4++;
        }
    }
    cout << "Part 1: " <<  q1 * q2 * q3 * q4 << endl;
    lines = lines2;
    int i = 0;
    while(true){
        for (auto &[p1, p2] : lines){
            p1.first += p2.first;
            p1.second += p2.second;
            if (p1.first < 0){
                p1.first += width;
            }
            else if (p1.first >= width){
                p1.first %= width;
            }
            if (p1.second < 0){
                p1.second += height;
            }
            else if (p1.second >= height){
                p1.second %= height;
            }

        }
        unordered_set<string> visited;
        bool flag = true;
        for (auto [p1, p2] : lines){
            if (visited.find(to_string(p1)) != visited.end()){
                flag = false;
                break;
            }
            visited.insert(to_string(p1));
        }
        i++;
        if (flag){
            break;
        }
        

        
    }
    cout << "Part 2: " << i << endl;

    
    return 0;
}