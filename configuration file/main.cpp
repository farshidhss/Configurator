//
//  main.cpp
//  configuration file
//
//  Created by Farshid Hassani Bijarbooneh on 6/18/13.
//  Copyright (c) 2013 Farshid Hassani Bijarbooneh. All rights reserved.
//

#include "configurator.h"

int main(int argc, const char * argv[])
{

    configurator myconf;
    
    // you can add manually or add using the default config file
//    myconf.addConfiguration("debug", "bool", "print constraints", "true");
//    myconf.addConfiguration("debug", "bool", "print variables", "false");
//    myconf.addConfiguration("debug", "bool", "print model", "true");
//    myconf.addConfiguration("visualisation", "bool", "plot 1", "true");
//    myconf.addConfiguration("visualisation", "bool", "plot 2", "true");
//    myconf.addConfiguration("visualisation", "bool", "plot 3", "true");
//    myconf.addConfiguration("arguments", "integer", "threads", "2");
//    myconf.addConfiguration("arguments", "integer", "iterations", "2000");
//    myconf.addConfiguration("arguments", "integer", "upperbound", "2200.998");
    
    cout << "print before loading the config file: " << endl;
    myconf.prettyPrint();
    cout << endl;
    
    // if added manually you can write the config settings to the file to be used later.
//    myconf.writeConfigurations("default.conf");
    
    myconf.readDefaultConfigurations("default_argument.conf", '\t');
    myconf.readDefaultConfigurations("default_debug.conf", '\t');
    myconf.readDefaultConfigurations("default_vis.conf", '\t');
    
    cout << "print after writing and reading the default conf: " << endl;
    myconf.prettyPrint();
    cout << endl;
    
    myconf.readConfigurations("customised.conf", '\t');
    
    cout << "print after reading the customised conf: " << endl;
    myconf.prettyPrint();
    cout << endl;
    
    // direct access for using in other classes:
//    cout << "direct access: " << configurator::options["debug"]["bool"]["print model"].value << endl;
    
    return 0;
}

