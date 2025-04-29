#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> input() {
    ifstream in("input.txt");
    vector<vector<int>> vec;
    int pos_prob = 0, pos_chess = 0, i = 0;
    string str = "", deal = "";
    while (getline(in, str)) {
        vec.push_back(vector<int>());
        do {
            pos_prob = str.find(" ", pos_chess);
            deal = str.substr(pos_chess, pos_prob - pos_chess);
            vec[i].push_back(atoi(deal.c_str()));
            pos_chess = pos_prob + 1;
        } while (pos_prob != -1);
        i++;
    }
    return vec;
}

void print(vector<vector<int>> vec) {
    for (int i = 0; i < vec.size(); i++, cout << endl){
        cout << i << ": ";
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
    }
}

void del_el(vector<int>& vec, int x) {
    vector<int>::iterator it = remove(vec.begin(), vec.end(), x);
    vec.erase(it, vec.end());
}

void Delete(vector<vector<int>>& vec, int x){
    int temp;
    for (int j = 0; j < vec[x].size(); j++){
        temp = vec[x][j];
        del_el(vec[temp], x);
    }
    vec.erase(vec.begin() + x);
}

void del_edges(vector<vector<int>>& vec, int x, int y) {
    del_el(vec[x], y);
    del_el(vec[y], x);
}

void ins_edges(vector<vector<int>>& vec, int x, int y){
    bool f1{false}, f2{false};
    for (int j = 0; j < vec[x].size(); j++)
        if (vec[x][j] == y) {f1 = true; break;}
    for (int j = 0; j < vec[y].size(); j++)
        if (vec[y][j] == x) {f2 = true; break;}
    if (f1 && f2) {cout << "edge exist"; return; }
    else {
        vec[x].push_back(y); sort(vec[x].begin(), vec[x].end());
        vec[y].push_back(x); sort(vec[y].begin(), vec[y].end());

    }
}

int main() {
    vector<vector<int>> vec;
    vec = input();
    print(vec);
    cout << endl;
}
