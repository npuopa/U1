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

    vector<string> pros;

    for (int i = 0; i < p; ++i){
    	string product;
    	in >> product;
        pros.push_back(product);
    }

    vector<pair<string, vector<float> > > cont;
    vector<float> min_p(p, numeric_limits<float>::max());
    
    while (!in.eof()) {
        string name;
        in >> name;
        vector<float> temp(p);
        for(int i = 0; i < p; ++i){
        	float price;
        	in >> price;
        	temp[i] = price;
        	min_p[i] = min(min_p[i], price);
		}
		cont.push_back({name, temp});
    }

    in.close();

    map<string, vector<string> > map;
    float res = 0;
    for (int i = 0; i < p; ++i) {
        res += min_p[i];
        for (int j = 0; j < cont.size(); ++j) {
            if (cont[j].second[i] == min_p[i]) {
                map[cont[j].first].push_back(pros[i]);
            }
        }
    }

    ofstream out("U1rez.txt");
    out << res << endl;
    if (res <= s) {
        vector<pair<string, vector<string> > > out_vec(map.begin(), map.end());
        sort(out_vec.begin(), out_vec.end(), comp);
        for (int i = 0; i < out_vec.size(); ++i) {
            out << out_vec[i].first << "\t";
            for (int j = 0; j < out_vec[i].second.size(); ++j) {
                out << out_vec[i].second[j] << "\t";
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
