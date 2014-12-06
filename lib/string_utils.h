#ifndef UTILS_H
#define UTILS_H

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


vector<string> split(const string& orig, char delim) {
    vector<string> ret;
    ret.push_back("");
    for (int i = 0; i < orig.size(); ++i) {
        if (orig[i] == delim) {
            ret.push_back("");
        } else {
            ret[ret.size()-1] += orig[i];
        }
    }
    return ret;
}

string join(vector<string> list, char delim) {
    string ret = "";
    for (int i = 0; i < list.size()-1; ++i) {
        ret += list[i] + ',';
    }
    ret += list[list.size()-1];
    return ret;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

#endif