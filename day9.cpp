#include <bits/stdc++.h>
using namespace std;



int main(){
    string line;
    fstream file = fstream("input.txt", ios::in);
    //one line of input
    getline(file, line);
    file.close();
    //Delete \n
    if (line[line.size()-1] == '\n'){
        line.pop_back();
    }
    vector<int> v, v_copy;
    for (int i = 0; i < line.size(); i++){
        int val = line[i] - '0';
        int ind = (i % 2 == 0 ? i / 2:-1);
        for (int j = 0; j < val; j++){
            v.push_back(ind);
        }
    }
    v_copy = v;
    int empty = 0;
    int filled = v.size() -1 ;
    while (empty < filled){
        if (v[empty] != -1){
            empty++;
        }
        else if (v[filled] == -1){
            filled--;
        }
        else{
            swap(v[empty], v[filled]);
            empty++;
            filled--;
        }
    }
    long long res = 0;
    for (int i = 0; i < v.size(); i++){
        if (v[i] == -1){
            continue;
        }
        res += i * v[i];
    }
    cout << "Part 1: " <<res << endl;
    v = v_copy;
    vector<tuple<int, int, int>> pos; //type, cnt, pos
    int id = v[0];
    int cnt = 1;
    for (int i = 1; i < v.size(); i++){
        if (v[i] == id){
            cnt++;
        }
        else{
            pos.push_back({id, cnt, i - cnt});
            id = v[i];
            cnt = 1;
        }
    }
    pos.push_back({id, cnt, v.size() - cnt});
    for (int i = pos.size() - 1; i >= 0; i--){
        auto [id, cnt, pos1] = pos[i]; // file
        if (id == -1){
            continue;
        }
        
        for (int j = 0; j < i; j++){
            auto &[id2, cnt2,pos2] = pos[j]; // empty
            if (id2 == -1 && cnt2 >= cnt){
                while (cnt > 0){
                    v[pos2] = id;
                    v[pos1] = -1;
                    pos1++;
                    pos2++;
                    cnt--;
                    cnt2--;

                }
                break;
            }

        }
    }
    /*
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
    */
    res = 0;
    for (int i = 0; i < v.size(); i++){
        if (v[i] == -1){
            continue;
        }
        res += i * v[i];
    }
    cout << "Part 2: " << res << endl;
}