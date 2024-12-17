#include <bits/stdc++.h>
using namespace std;


string run(vector<unsigned long long> &instructions, unsigned long long regA){
    unsigned long long regB = 0;
    unsigned long long regC = 0;
    string out = "";
    auto combo_op = [&](unsigned long long op){
        switch (op){
            case 0:
            case 1:
            case 2:
            case 3:
                return op;
            case 4:
                return regA;
            case 5:
                return regB;
            case 6:
                return regC;
            default:
                return static_cast<unsigned long long>(-1);
        }
    };
    unsigned long long pc = 0;
    while (pc < instructions.size()){
        unsigned long long op = instructions[pc];
        unsigned long long a = instructions[pc+1];
        switch (op){
            case 0:
                //adv
                regA /= (1 << combo_op(a));
                break;
            case 1:
                //bxl
                regB ^= a;
                break;
            case 2:
                //bst
                regB = combo_op(a) % 8;
                break;
            case 3:
                //jnz
                if (regA != 0){
                    pc = a;
                    continue;
                }
                break;
            case 4:
                //bxc
                regB ^= regC;
                break;
            case 5:
                //out
                out += to_string(combo_op(a) % 8) + ",";
                break;
            case 6:
                //bdv
                regB = regA / (1 << combo_op(a));
                break;
            case 7:
                regC = regA / (1 << combo_op(a));
                break;
            default:
                break;
        }
        pc += 2;
    }
    out.pop_back();
    return out;
}



int main(){
    unsigned long long regA, regB, regC;
    fstream file = fstream("input.txt", ios::in);
    string line;
    //first: rega value, second: regb value, third: regc value
    getline(file, line);
    line = line.substr(line.find(":")+1);
    regA = static_cast<unsigned long long>(stoi(line));
    getline(file, line);
    line = line.substr(line.find(":")+1);
    regB = static_cast<unsigned long long>(stoi(line));
    getline(file, line);
    line = line.substr(line.find(":")+1);
    regC = static_cast<unsigned long long>(stoi(line));
    getline(file, line);
    getline(file, line);
    line = line.substr(line.find(":")+2);
    file.close();
    vector<unsigned long long> instructions;
    stringstream ss(line);
    while(ss.good()){
        string substr;
        getline(ss, substr, ',');
        instructions.push_back(stoi(substr));
    }
    auto combo_op = [&](unsigned long long op){
        switch (op){
            case 0:
            case 1:
            case 2:
            case 3:
                return op;
            case 4:
                return regA;
            case 5:
                return regB;
            case 6:
                return regC;
            default:
                return static_cast<unsigned long long>(-1);
        }
    };
    unsigned long long pc = 0;
    while (pc < instructions.size()){
        unsigned long long op = instructions[pc];
        unsigned long long a = instructions[pc+1];
        switch (op){
            case 0:
                //adv
                regA /= (1 << combo_op(a));
                break;
            case 1:
                //bxl
                regB ^= a;
                break;
            case 2:
                //bst
                regB = combo_op(a) % 8;
                break;
            case 3:
                //jnz
                if (regA != 0){
                    pc = a;
                    continue;
                }
                break;
            case 4:
                //bxc
                regB ^= regC;
                break;
            case 5:
                //out
                cout << combo_op(a) % 8 << ",";
                break;
            case 6:
                //bdv
                regB = regA / (1 << combo_op(a));
                break;
            case 7:
                regC = regA / (1 << combo_op(a));
                break;
            default:
                break;
        }
        pc += 2;
    }
    cout << endl;
    regA = (1ULL << 46);
    while (run(instructions, regA++) != line){
        if (regA % 100000 == 0){
            cout << regA << endl;
        }
    }
    cout << regA-1 << endl;
    
}