//
//  configurator.cpp
//  WSNCP_Copula
//
//  Created by Farshid Hassani Bijarbooneh on 6/17/13.
//  Copyright (c) 2013 farshidhassanibijarbooneh. All rights reserved.
//

#include "configurator.h"

map<string, set<string> > configurator::confHierarchy;
//map<string, map<string, string> > configurator::confDataTypes;
map<string, map<string, confVal> > configurator::options;


configurator::configurator(){}

void configurator::readConfigurations(string confFilename, char delim) {
    string currentLine;
    string class_name, data_type, parameter, value, equal;
    vector<string> tokens;
    
	ifstream inputFile;
	inputFile.open(confFilename.c_str());
	if (inputFile.fail()){
		cout << "Config File not found! filename: " << confFilename << endl;
	}
    
    while (inputFile.good()) {
        
        getline(inputFile, currentLine);
        
        if (currentLine.length()<=0) {
            continue;
        }
        if (currentLine[0]==' ' | currentLine[0] == '#') {
            continue;
        }
        
        tokens.clear();
        
        tokens = split(currentLine, delim, tokens);
        
        class_name  = tokens[0];
        data_type   = tokens[1];
        parameter   = tokens[2];
        equal       = tokens[3];
        value       = tokens[4];
        
        if (confHierarchy.find(class_name)!=confHierarchy.end() &&
            confHierarchy[class_name].find(parameter)!=confHierarchy[class_name].end()) {
            addConfiguration(class_name, data_type, parameter, value);
        }
    }
    
	inputFile.close();
}

void configurator::readDefaultConfigurations(string confFilename, char delim) {
    string currentLine;
    string class_name, data_type, parameter, value, equal;
    vector<string> tokens;
    
	ifstream inputFile;
	inputFile.open(confFilename.c_str());
	if (inputFile.fail()){
		cout << "Config File not found! filename: " << confFilename << endl;
	}
    
    while (inputFile.good()) {
        
        getline(inputFile, currentLine);
        
        if (currentLine.length()<=0) {
            continue;
        }
        if (currentLine[0]==' ' | currentLine[0] == '#') {
            continue;
        }
        
        tokens.clear();
        
        tokens = split(currentLine, delim, tokens);
        
        class_name  = tokens[0];
        data_type   = tokens[1];
        parameter   = tokens[2];
        equal       = tokens[3];
        value       = tokens[4];
    
        addConfiguration(class_name, data_type, parameter, value);
    }
    
	inputFile.close();
}

vector<string>& configurator::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> configurator::split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems); return elems;
}

void configurator::writeConfigurations(string confFilename, char delim) {
    ofstream outputfile(confFilename.c_str(), ofstream::trunc);
    
    map<string, set<string> >::iterator map_iterator;
    set<string>::iterator set_iterator;
    
    set<string> current_class;
    string class_name, data_type, parameter, value;
    
    //    outputfile << "# This is the default configuration file: " << endl;
    for (map_iterator = confHierarchy.begin(); map_iterator!=confHierarchy.end(); ++map_iterator) {
        class_name = map_iterator->first;
        current_class = map_iterator->second;
        
        outputfile << "# " << class_name << " :" << endl;
        
        for (set_iterator = current_class.begin(); set_iterator != current_class.end() ; ++set_iterator) {
//            data_type = confDataTypes[class_name][*set_iterator];
            data_type = options[class_name][parameter].dataType;
            parameter = *set_iterator;
            value = options[class_name][parameter].value;
            outputfile  << class_name << delim
                        << data_type << delim
                        << parameter << delim << "=" << delim << value << endl;
        }
        outputfile << endl;
    }
    
    outputfile.close();
    
}

void configurator::addConfiguration(string confClass, string dataType, string parameter, string value){
    options[confClass][parameter].value = value;
    options[confClass][parameter].dataType = dataType ;
    confHierarchy[confClass].insert(parameter);
//    confDataTypes[confClass][parameter] = dataType;
}

void configurator::prettyPrint(){
    map<string, set<string> >::iterator map_iterator;
    set<string>::iterator set_iterator;
    
    set<string> current_class;
    string class_name, data_type, parameter, value;
    
    cout << "Printing hierarchy: " << endl;
    for (map_iterator = confHierarchy.begin(); map_iterator!=confHierarchy.end(); ++map_iterator) {
        class_name = map_iterator->first;
        current_class = map_iterator->second;
        cout << map_iterator->first << " :" << endl;
        for (set_iterator = current_class.begin(); set_iterator != current_class.end() ; ++set_iterator) {
//            data_type = confDataTypes[map_iterator->first][*set_iterator];
            parameter = *set_iterator;
            data_type = options[class_name][parameter].dataType;
            value = options[class_name][parameter].value;
            cout << "\t" << data_type << "\t" << parameter << " = " << value << endl;
        }
    }
    cout << "end pretty print!" << endl;
    
}