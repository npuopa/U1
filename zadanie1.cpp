#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

bool comp(const pair<string, vector<string> >& a, const pair<string, vector<string> >& b) {
    return a.second.size() > b.second.size();
}

int main()
{
    ifstream in("U1.txt");
    int p, s;
    in >> p >> s;

    string line;
    getline(in, line);
    getline(in, line);
    vector<string> pro;
    istringstream iss(line);
    string pros;
    while (getline(iss, pros, ' ')) {
        pro.push_back(pros);
    }

    vector<pair<string, vector<float> > > cont;
    while (getline(in, line)) {
        iss.clear();
        iss.str(line);
        string name;
        iss >> name;
        pair<string, vector<float> > temp;
        temp.first = name;
        float price;
        while (iss >> price) {
            temp.second.push_back(price);
        }
        cont.push_back(temp);
    }

    in.close();

    map<string, vector<string> > map;
    float res = 0;
    for (int i = 0; i < p; ++i) {
        float min_p = numeric_limits<float>::max();
        for (int j = 0; j < cont.size(); ++j) {
            min_p = min(min_p, cont[j].second[i]);
        }
        res += min_p;
        for (int j = 0; j < cont.size(); ++j) {
            if (cont[j].second[i] == min_p) {
                map[cont[j].first].push_back(pro[i]);
            }
        }
    }

    ofstream out;
    out.open("U1rez.txt");
    out << res << endl;
    if (res <= s) {
        vector<pair<string, vector<string> > > out_vec(map.begin(), map.end());
        sort(out_vec.begin(), out_vec.end(), comp);
        vector<pair<string, vector<string> > >::iterator it;
        for (it = out_vec.begin(); it != out_vec.end(); ++it) {
            out << it->first << " ";
            for (int i = 0; i < it->second.size(); ++i) {
                out << it->second[i] << " ";
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
