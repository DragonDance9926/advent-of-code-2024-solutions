#include <bits/stdc++.h>
using namespace std;
#define SIZE 71
#define MIN 1024


int bfs (array<array<int, SIZE>, SIZE> &grid, array<array<bool, SIZE>, SIZE> &visited){
    queue<pair<pair<int, int>, int>> q;
    q.push({{0, 0}, 0});
    while(!q.empty()){
        auto [pos, steps] = q.front();
        q.pop();
        auto [x, y] = pos;
        //cout << x << " " << y << " " << steps << endl;
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || visited[x][y] || grid[x][y] == 1){
            
            continue;
        }
        visited[x][y] = true;
        if (x == SIZE-1 && y == SIZE-1){
            return steps;
        }
        q.push({{x+1, y}, steps+1});
        q.push({{x-1, y}, steps+1});
        q.push({{x, y+1}, steps+1});
        q.push({{x, y-1}, steps+1});
    }
    return -1;
}
int main(){
    string line;
    vector<pair<int ,int>> lines;
    fstream file = fstream("input.txt", ios::in);
    while(getline(file, line)){
        int x = stoi(line.substr(0, line.find(',')));
        int y = stoi(line.substr(line.find(',')+1));
        lines.push_back({x, y});
    }
    file.close();
    array<array<int, SIZE>, SIZE> grid;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            grid[i][j] = 0;
        }
    }
    for (int i = 0; i < MIN; i++){
        auto [x, y] = lines[i];
        grid[x][y] = 1;
    }
    queue<pair<pair<int, int>, int>> q;
    q.push({{0, 0}, 0});
    array<array<bool, SIZE>, SIZE> visited;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            visited[i][j] = false;
        }
    }
    cout << "Part 1:" << bfs(grid, visited) << endl;
    int i = MIN;
    do{
        auto [x, y] = lines[i];
        grid[x][y] = 1;
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                visited[i][j] = false;
            }
        }
        i++;
    }while(bfs(grid, visited) != -1);
    cout << "Part 2:" << lines[i-1].first << "," << lines[i-1].second << endl;
    
    return 0;
}