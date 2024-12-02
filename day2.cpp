#include <bits/stdc++.h>
using namespace std;


bool isAscending(vector<int> &v){
    int c = 0;
    for(int i = 0; i < v.size() - 1; i++){
        if(v[i] > v[i + 1]) return false;
    }
    return true;
}
int isDescending(vector<int> &v){
    int c = 0;
    for(int i = 0; i < v.size() - 1; i++){
        if(v[i] < v[i + 1]) return false;
    }
    return true;
}

int isAdjCheck(vector<int> &v){
    int c = 0;
    for(int i = 0; i < v.size() - 1; i++){
        int diff = abs(v[i + 1] - v[i]);
        if (diff < 1 || diff > 3) return false;
    }
    return true;
}


int main(){
    fstream file;
    file.open("input.txt", ios::in);
    string line;
    vector<vector<int>> v;
    while (getline(file, line)){
        //cout << line << endl;
        vector<int> temp;
        stringstream ss(line);
        int x;
        while(ss >> x){
            temp.push_back(x);
        }
        v.push_back(temp);
    }
    file.close();
    int c = 0;
    for (auto &x : v){
        //cout << isAscending(x) << " " << isDescending(x) << " " << isAdjCheck(x) << endl;
        c += (isAscending(x) || isDescending(x)) && isAdjCheck(x);
    }
    cout << "Part 1: " << c << endl;
    c = 0;
    for (auto &x : v){
        if ((isAscending(x) || isDescending(x)) && isAdjCheck(x)){
            c++;
            continue;
        }
        for (int i = 0; i < x.size(); i++){
            //Remove element at index i
            int temp = x[i];
            x.erase(x.begin() + i);
            if ((isAscending(x) || isDescending(x)) && isAdjCheck(x)){
                c++;
                
                x.insert(x.begin() + i, temp);
                break;
            }
            x.insert(x.begin() + i, temp);
        }
    }
    cout << "Part 2: " << c << endl;
    return 0;
    
}