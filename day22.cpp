#include <bits/stdc++.h>
using namespace std;

#define mod 16777216LL









int main(){
    fstream file;
    file.open("input.txt");
    string line;
    vector<long long> nums;
    while(getline(file, line)){
        nums.push_back(stoll(line));
    }
    file.close();
    map<tuple<int, int,int, int>,long long> mp;
    long long sum = 0;
    for(auto num:nums){
        vector<int> seq;
        seq.push_back(num);
        for(int i = 0; i < 2000; i++){
            num = ((num << 6) ^ num) % mod;
            num = ((num >> 5) ^ num) % mod;
            num = ((num << 11) ^ num) % mod;
            seq.push_back(num);
        }
        sum += num;
        //cout << num << endl;

        /*
        c = [ b % 10 - a % 10 for a, b in zip( s, s[ 1 : ] ) ]
        v = set()
        for i in range( len( c ) - 4 ):
            o = tuple( c[ i : i + 4 ] )
            if o not in v:
                p[ o ] += s[ i + 4 ] % 10
                v.add( o )
         */
        vector<int> c;
        for (int i = 1; i < seq.size(); i++){
            c.push_back(seq[i] % 10 - seq[i - 1] % 10);
        }
        set<tuple<int, int, int, int>> v;
        for(int i = 0; i < c.size() - 4; i++){
            tuple<int, int, int, int> o = make_tuple(c[i], c[i + 1], c[i + 2], c[i + 3]);
            if(v.find(o) == v.end()){
                mp[o] += seq[i + 4] % 10;
                v.insert(o);
            }
        }
    }
    cout << sum << endl;
    sum = 0;
    for(auto [k, v]:mp){
        sum = max(sum, v);
    }
    cout << sum << endl;
    return 0;
}