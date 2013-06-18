//
//  configurator.h
//  WSNCP_Copula
//
//  Created by Farshid Hassani Bijarbooneh on 6/17/13.
//  Copyright (c) 2013 farshidhassanibijarbooneh. All rights reserved.
//

#ifndef __WSNCP_Copula__configurator__
#define __WSNCP_Copula__configurator__

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct confVal {
    string value;
    string dataType;
    int getInt(){return atoi(value.c_str());}
    double getDouble(){return atof(value.c_str());}
    bool getBool(){return value=="true";}
};

class configurator {
    
private:
    static map<string, set<string> > confHierarchy;
    
    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);
    
    
public:
    static map<string, map<string, confVal> > options;
    configurator();
    void readConfigurations(string confFilename, char delim);
    void readDefaultConfigurations(string confFilename, char delim);
    void writeConfigurations(string confFilename, char delim);
    void addConfiguration(string confClass, string dataType, string parameter, string value);
    void prettyPrint();
    
};

#endif /* defined(__WSNCP_Copula__configurator__) */
