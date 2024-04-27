#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

bool comp(const pair<string, vector<string>>& a, const pair<string, vector<string>>& b) {
    return a.second.size() > b.second.size();
}

int main()
{
    int p = 0, s = 0;
    vector<string> pro;
    vector<pair<string, vector<float>>> cont;

    string line;
    ifstream in("U1.txt");

    getline(in, line);
    istringstream iss(line);
    iss >> p >> s;

    getline(in, line);
    iss = istringstream(line);
    string pros;
    while (getline(iss, pros, ' ')) {
        pro.push_back(pros);
    }

    while (getline(in, line)) {
        iss = istringstream(line);
        string name;
        iss >> name;
        pair<string, vector<float>> temp;
        temp.first = name;
        float price;
        while(iss >> price){
            temp.second.push_back(price);
        }
        cont.push_back(temp);
    }

    in.close();

    unordered_map<string, vector<string>> umap;
    float res = 0;
    for (int i = 0; i < p; ++i) {
        float min_p = numeric_limits<float>::max();
        for (int j = 0; j < cont.size(); ++j) {
            min_p = min(min_p, cont[j].second[i]);
        }
        res += min_p;
        for (int j = 0; j < cont.size(); ++j) {
            if (cont[j].second[i] == min_p) {
                umap[cont[j].first].push_back(pro[i]);
            }
        }
    }

    ofstream out;
    out.open("U1rez.txt");
    out << res << endl;
    if (res <= s) {
        vector<pair<string, vector<string>>> out_vec(umap.begin(), umap.end());
        sort(out_vec.begin(), out_vec.end(), comp);
        for (pair<string, vector<string>> p : out_vec) {
            out << p.first << " ";
            for (string ss : p.second) {
                out << ss << " ";
            }
            out << endl;
        }
    }
    else {
        out << "NO";
    }

    out.close();

    return 0;
}