#include<regex>
#include <bits/stdc++.h>
using namespace std;

//Regex: mul\((\d+,\d+)\)
//Regex2: (don't\(\)|do\(\)|mul\((\d+,\d+)\))

int main(){
    string full_comm = "";
    string temp;
    string line;
    fstream file = fstream("input.txt", ios::in);
    while(getline(file, line)){
        if (line.back() == '\n') line.pop_back();
        full_comm += line;
    }
    //cout << full_comm << endl;
    regex r("mul\\((\\d+,\\d+)\\)");
    smatch m;
    long long sum = 0;
    temp = full_comm;
    while(regex_search(full_comm, m, r)){
        string temp = m[1];
        long long a = stoll(temp.substr(0, temp.find(',')));
        long long b = stoll(temp.substr(temp.find(',') + 1));
        sum += a * b;
        full_comm = m.suffix().str();
    }
    cout << "Part 1: " << sum << endl;
    full_comm = temp;
    regex r2("(don't\\(\\)|do\\(\\)|mul\\((\\d+,\\d+)\\))");
    smatch m2;
    sum = 0;
    bool flag = true;
    while(regex_search(full_comm, m2, r2)){
        //cout << m2[1] << endl;
        if (m2[1] == "don't()"){
            flag = false;
        }
        else if (m2[1] == "do()"){
            flag = true;
        }
        else{
            if (flag){
                string temp = m2[2];
                long long a = stoll(temp.substr(0, temp.find(',')));
                long long b = stoll(temp.substr(temp.find(',') + 1));
                sum += a * b;
            }
        }
        full_comm = m2.suffix().str();
    }
    cout << "Part 2: " << sum << endl;
}