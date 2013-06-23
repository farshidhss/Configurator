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
#include <assert.h>

using namespace std;

struct confVal {
    string value;
    
    int getInt(){return atoi(value.c_str());}
    double getDouble(){return atof(value.c_str());}
    bool getBool(){return value=="1";}
};

class configurator {
    
    struct Value {
        string value;
        
        template<typename T>
        operator T() const 
        {
            std::stringstream ss(value);
            T convertedValue;
            if ( ss >> convertedValue ) return convertedValue;
            else throw std::runtime_error("conversion failed");
        }
    };
    
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
    void addConfiguration(string confClass, string parameter, string value);
    void prettyPrint();
    static void setValue(const string confClass, const string parameter, const string value);
    static Value getValue(const string confClass, const string parameter) ;
    
};

#endif /* defined(__WSNCP_Copula__configurator__) */
