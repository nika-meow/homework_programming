#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>

using namespace std;
ifstream in;
ofstream out;

struct data1 {
    string name;
    int experience;
};

data1 set_word(string s) {
    data1 person;
    person.name = s.substr(0, s.find(' '));
    person.experience = stoi(s.substr(s.find(' ') + 1, s.size() - 1));
    return person;
}

vector <data1> create() {
    vector <data1> vec;
    in.open("input1.txt");
    int i{0};
    string str;
    while (getline(in, str)){
        vec.push_back(set_word(str));
    }
    return vec;
}

list <data1>* hesh_table(vector <data1> vec, int m) {
    int i{0};
    list <data1>* mas = new list <data1>[m];
    while (i < vec.size()) {
        mas[vec[i].experience % m].push_back(vec[i]);
        i++;
    }
    return mas;
}

void print_hesh(list <data1>* mas, int m) {
    int i{0}, k{0};
    while (i < m) {
        for (auto iter = mas[i].begin(); iter != mas[i].end(); iter++)
            cout << (*iter).name << " " << (*iter).experience << " / ";
        cout << endl;
        i++;
    }
}

int main() {
    vector <data1> vec = create();
    int m;
    cout << "M: "; cin >> m;
    list <data1>* mas = hesh_table(vec, m);
    print_hesh(mas, m);
}
