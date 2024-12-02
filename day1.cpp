#include <bits/stdc++.h>
using namespace std;

int main(){
    fstream file;
    file.open("input.txt", ios::in);
    vector<int> n1, n2;
    int x1, x2;
    while(file >> x1 >> x2){
        n1.push_back(x1);
        n2.push_back(x2);
        //cout << x1 << " " << x2 << endl;
    }
    file.close();
    sort(n1.begin(), n1.end());
    sort(n2.begin(), n2.end());
    int res = 0;
    for(int i = 0; i < n1.size(); i++){
        res += abs(n1[i] - n2[i]);
        
        //cout << n1[i] << " " << n2[i] << " " << res << endl;
    }
    cout << "Part 1: " << res << endl;
    unordered_map<int, int> m;
    for (auto &x : n2) m[x]++;
    res = 0;
    for (auto &x : n1){
        res += x * m[x];
    }
    cout << "Part 2: " << res << endl;
    return 0;
}