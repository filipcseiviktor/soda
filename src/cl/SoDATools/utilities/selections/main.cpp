/*
 * Copyright (C): 2013-2014 Department of Software Engineering, University of Szeged
 *
 * Authors: David Havas <havasd@inf.u-szeged.hu>
 *
 * This file is part of SoDA.
 *
 *  SoDA is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SoDA is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SoDA.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_FILESYSTEM_VERSION 3

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

#include "data/CSelectionData.h"

#include "CSelectionsPluginManager.h"
#include "CComputeSelectionMetrics.h"
#include "plugins/prioritization/IPrioritizationPlugin.h"

using namespace soda;
using namespace std;
using namespace boost::program_options;
using namespace boost::filesystem;

int processArgs(options_description desc, int ac, char* av[]);
void printPluginNames(const std::string &type, const std::vector<std::string> &plugins);

CSelectionData selectionData;
CSelectionsPluginManager pluginManager;

int main(int argc, char* argv[]) {
    cout << "selections (SoDA tool)" << endl;
    options_description desc("Allowed options");
    desc.add_options()
        ("help,h",                           "produce help message")
        ("coverage-data,c", value<String>(), "input file containing coverage matrix")
        ("changes-data,x",  value<String>(), "input file containing change matrix")
        ("results-data,r",  value<String>(), "input file containing test execution results")
        ("type,t",          value<String>(), "type of the algorithm. Could be: prioritization")
        ("mode,m",          value<String>(), "the algorithm mode")
        ("list,l",                           "lists the avaiable algorithm modes")
        ("sizes,s",         value<String>(), "coma separated list of integers representing selection set sizes")
        ("print-details",                    "")
        ("progress-level",  value<int>(),    "progress indicator level")
    ;

    if(argc < 2) {
        cerr << "ERROR: There are no arguments!" << endl << desc << endl;
        return 1;
    }

    return processArgs(desc, argc,argv);
}

void printPluginNames(const std::string &type, const std::vector<std::string> &plugins)
{
    std::cout << "The available read modes for reading type: " << type << std::endl;
    for (size_t i = 0; i < plugins.size(); i++) {
        std::cout << "  * " << plugins[i] << std::endl;
    }
}

int processArgs(options_description desc, int ac, char* av[])
{
    try {
        positional_options_description p;
        variables_map vm;
        store(command_line_parser(ac, av).options(desc).positional(p).run(), vm);
        notify(vm);

        if (!vm.count("type")) {
            std::cerr << "[ERROR] Type is missing." << std::endl << desc;
            return 1;
        }

        if (vm.count("coverage-data") && vm.count("changes-data") && vm.count("results-data")) {
            (cerr << "[INFO] loading coverage from " << vm["coverage-data"].as<String>() << " ...").flush();
            selectionData.loadCoverage(vm["coverage-data"].as<String>());
            (cerr << " done\n[INFO] loading changes from " << vm["changes-data"].as<String>() << " ...").flush();
            selectionData.loadChangeset(vm["changes-data"].as<String>());
            (cerr << " done\n[INFO] loading results from " << vm["results-data"].as<String>() << " ...").flush();
            selectionData.loadResults(vm["results-data"].as<String>());
            (cerr << " done" << endl).flush();
        } else {
            std::cerr << "[ERROR] Missing input files." << std::endl;
            return 1;
        }

        IntVector sizelist;
        if (vm.count("sizes")) {
            boost::char_separator<char> sep(",");
            boost::tokenizer< boost::char_separator<char> > tokens(vm["sizes"].as<String>(), sep);
            BOOST_FOREACH (const string& t, tokens) {
                sizelist.push_back(boost::lexical_cast<int>(t));
            }
        }

        IntVector revisionlist = selectionData.getResults()->getRevisionNumbers();

        String type = vm["type"].as<std::string>();

        if (type == "prioritization") {
            IPrioritizationPlugin *plugin = NULL;
            pluginManager.loadPrioritizationPlugins();

            if (vm.count("list")) {
                printPluginNames("prioritization", pluginManager.getPrioritizationPluginNames());
                return 0;
            }

            if (vm.count("mode")) {
                String mode = vm["mode"].as<std::string>();
                try {
                    plugin = pluginManager.getPrioritizationPlugin(mode);
                    plugin->init(&selectionData);
                } catch (std::out_of_range &e) {
                    std::cerr << "[ERROR] Unknown algorithm mode. " << std::endl;
                    printPluginNames("prioritization", pluginManager.getPrioritizationPluginNames());
                    return 1;
                }
            }

            CComputeSelectionMetrics *selectionStat = new CComputeSelectionMetrics(&selectionData, plugin, &revisionlist, &sizelist, ((vm.count("progress-level")) ? (vm["progress-level"].as<int>()) : 0));

            (cerr << "[INFO] Measurements on " << revisionlist.size() << " revisions ...").flush();

            selectionStat->runMeasurement();

            (cerr << " done." << endl).flush();

            if (vm.count("print-details")) {
                selectionStat->printDetailedData();
            } else {
                selectionStat->printData();
            }

            delete selectionStat;
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Exception of unknown type while processsing command line arguments!" << std::endl;
        return 1;
    }
    return 0;
}
