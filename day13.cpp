#include <bits/stdc++.h>
#include <regex>
using namespace std;

//regex :
/*
Button A: X([+|-]\d+), Y([+|-]\d+)
*/
/*
Button B: X([+|-]\d+), Y([+|-]\d+)
*/
/*
Prize: X=(\d+), Y=(\d+)
*/

string pair_To_String(pair<long long, long long> p1, pair<long long, long long> p2, pair<long long, long long> p3){
    return "(" + to_string(p1.first) + ", " + to_string(p1.second) + ") (" + to_string(p2.first) + ", " + to_string(p2.second) + ") (" + to_string(p3.first) + ", " + to_string(p3.second) + ")";
}

unordered_map<string, long long> memo;

long long play1 (pair<long long, long long> &buttonA, pair<long long, long long> &buttonB, pair<long long, long long> prize){
    auto [dxA, dyA] = buttonA;
    auto [dxB, dyB] = buttonB;
    auto [xP, yP] = prize;
    //cout << xP << " " << yP << " " << dxA << " " << dyA << " " << dxB << " " << dyB << endl;
    
    if (xP < 0 || yP < 0){
        return -1;
    }
    if (xP == 0 && yP == 0){
        return 0;
    }
    if (memo.find(pair_To_String(buttonA, buttonB, prize)) != memo.end()){
        return memo[pair_To_String(buttonA, buttonB, prize)];
    }
    long long mv1 = play1(buttonA, buttonB, {xP - dxA, yP - dyA});
    long long mv2 = play1(buttonA, buttonB, {xP - dxB, yP - dyB});
    if (mv1 == -1 && mv2 == -1){
        memo[pair_To_String(buttonA, buttonB, prize)] = -1;
        return -1;
    }
    else if (mv1 == -1){
        memo[pair_To_String(buttonA, buttonB, prize)] = mv2 + 1;
        return mv2 + 1;
    }
    else if (mv2 == -1){
        memo[pair_To_String(buttonA, buttonB, prize)] = mv1 + 3;
        return mv1 + 3;
    }
    else{
        memo[pair_To_String(buttonA, buttonB, prize)] = min(mv1 + 3, mv2 + 1);
        return min(mv1 + 3, mv2 + 1);
    }
}


int main(){
    fstream file = fstream("input.txt", ios::in);
    vector<string> lines;
    string line;
    while(getline(file, line)){
        lines.push_back(line);
    }
    file.close();
    vector<pair<long long, long long>> buttonA;
    vector<pair<long long, long long>> buttonB;
    vector<pair<long long, long long>> prize;
    regex buttonARegex("Button A: X([+|-]\\d+), Y([+|-]\\d+)");
    smatch buttonAMatch;
    regex buttonBRegex("Button B: X([+|-]\\d+), Y([+|-]\\d+)");
    smatch buttonBMatch;
    regex prizeRegex("Prize: X=(\\d+), Y=(\\d+)");
    smatch prizeMatch;
    for (long long i = 0; i < lines.size(); i++){
        switch (i % 4){
            case 0:
            //Button A
                
                if (regex_match(lines[i], buttonAMatch, buttonARegex)){
                    buttonA.push_back({stoi(buttonAMatch[1]), stoi(buttonAMatch[2])});
                }
                break;
            case 1:
            //Button B
                
                if (regex_match(lines[i], buttonBMatch, buttonBRegex)){
                    buttonB.push_back({stoi(buttonBMatch[1]), stoi(buttonBMatch[2])});
                }
                break;
            case 2:
            //Prize
                
                if (regex_match(lines[i], prizeMatch, prizeRegex)){
                    prize.push_back({stoi(prizeMatch[1]), stoi(prizeMatch[2])});
                }
                break;
            case 3:
                break;

        }
    }
    long long res = 0;
    for (int i = 0; i < buttonA.size(); i++){
        auto [x1, y1] = buttonA[i];
        auto [x2, y2] = buttonB[i];
        auto [x, y] = prize[i];
        //x1 * A + x2 * B = x
        //y1 * A + y2 * B = y
        //A = (x - x2 * B) / x1
        //A = (y - y2 * B) / y1
        //(x - x2 * B) / x1 = (y - y2 * B) / y1
        //x * y1 - x2 * y1 * B = y * x1 - y2 * x1 * B
        //x * y1 - y * x1 = x2 * y1 * B - y2 * x1 * B
        //B = (x * y1 - y * x1) / (x2 * y1 - y2 * x1)
        long long B = (x * y1 - y * x1) / (x2 * y1 - y2 * x1);
        long long A = (x - x2 * B) / x1;
        //Check if A and B are integers
        bool eq1 = (x == x1 * A + x2 * B);
        bool eq2 = (y == y1 * A + y2 * B);
        if (eq1 && eq2){
            res += 3 * A + B;
        }
    }
    cout << res << endl;
    res = 0;
    for (int i = 0; i < buttonA.size(); i++){
        prize[i].first += 10000000000000;
        prize[i].second += 10000000000000;
        auto [x1, y1] = buttonA[i];
        auto [x2, y2] = buttonB[i];
        auto [x, y] = prize[i];
        long long B = (x * y1 - y * x1) / (x2 * y1 - y2 * x1);
        long long A = (x - x2 * B) / x1;
        //Check if A and B are integers
        bool eq1 = (x == x1 * A + x2 * B);
        bool eq2 = (y == y1 * A + y2 * B);
        if (eq1 && eq2){
            res += 3 * A + B;
        }
    }
    cout << res << endl;

}