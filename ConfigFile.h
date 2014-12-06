#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <string>
using std::string;
#include <fstream>
using std::fstream;
#include <map>
using std::map;
#include <vector>
using std::vector;

#include "lib/string_utils.h"


class ConfigFile {
    public:
        ConfigFile(string filename): file(filename.c_str()) {}

        bool proc();    // process the configuration file, returns if the file
                        // was processed properly

        double getDouble(string key);

    private:
        ifstream file;
        map<string, string> attrs;
};


bool ConfigFile::proc() {
    string line;
    while (getline(file, line)) {
        line = trim(line);
        vector<string> kv = split(line, ':');
        if (kv.size() != 2) {
            return false;
        }
        attrs[trim(kv[0])] = trim(kv[1]);
    }
    return true;
}

double ConfigFile::getDouble(string key) {
    return stoi(attrs[key]);
}

#endif
