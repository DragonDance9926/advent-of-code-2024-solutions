#include <bits/stdc++.h>
using namespace std;


unordered_set<string> visited;
int rs = 0;
unordered_set<string> __path;
void dfs (unordered_map<string, vector<string>> &graph, unordered_set<string> &path, string node){
    if (visited.find(node) != visited.end()){
        return;
    }
    
    visited.insert(node);
    path.insert(node);
    if (path.size() > rs){
        rs = path.size();
        __path = path;
    }
    for (auto neighbour: graph[node]){
        //cout << neighbour << endl;
        bool f = true;
        for (auto p: path){
            if (find(graph[neighbour].begin(), graph[neighbour].end(), p) == graph[neighbour].end()){
                f = false;
                break;
            }
        }
        if (f){
            dfs(graph, path, neighbour);
        }
    }
    path.erase(node);
    return;
}




int main(){
    fstream file;
    file.open("input.txt");
    string line;
    vector<pair<string, string>> edges;
    while(getline(file, line)){
        edges.push_back({line.substr(0, line.find('-')), line.substr(line.find('-') + 1)});
    }
    file.close();
    unordered_map<string, vector<string>> graph;
    for(auto edge: edges){
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }
    unordered_set<string> visited;
    vector<tuple<string, string, string>> paths;
    for (auto &[key, val] : graph){
        for (int i = 0; i < val.size(); i++){
            if (visited.find(val[i]) == visited.end()){
                for (int j = i + 1; j < val.size(); j++){
                    if (visited.find(val[j]) == visited.end()){
                        bool c1 = find(graph[val[j]].begin(), graph[val[j]].end(), val[i]) != graph[val[j]].end();
                        bool c2 = find(graph[val[i]].begin(), graph[val[i]].end(), val[j]) != graph[val[i]].end();
                        if (c1 && c2){
                            paths.push_back({key, val[i], val[j]});
                        }
                    }
                }
            }
        }
        visited.insert(key);
    }
    int p = 0;
    for (auto path: paths){
        auto &[a, b, c] = path;
       // cout << a << " " << b << " " << c << endl;
        p += a[0] == 't' || b[0] == 't' || c[0] == 't';
    }
    cout << p << endl;
    for (auto &[key, val] : graph){
        visited.clear();
        unordered_set<string> _path;
        dfs(graph, _path, key);
    }
    vector<string> __p;
    for (auto p: __path){
        __p.push_back(p);
    }
    sort(__p.begin(), __p.end());
    for (auto p: __p){
        cout << p << ",";
    }
    cout << endl;
    return 0;
}