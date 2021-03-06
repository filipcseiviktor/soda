/*
 * Copyright (C): 2013-2014 Department of Software Engineering, University of Szeged
 *
 * Authors: David Tengeri <dtengeri@inf.u-szeged.hu>
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

#include <fstream>

#include "FMeasureMetricPlugin.h"

namespace soda {

FMeasureMetricPlugin::FMeasureMetricPlugin() :
    m_data(NULL),
    m_clusterList(NULL)
{}

FMeasureMetricPlugin::~FMeasureMetricPlugin()
{}

std::string FMeasureMetricPlugin::getName()
{
    return "f-measure";
}

std::string FMeasureMetricPlugin::getDescription()
{
    return "Calculates the F-measure value of the coverage and partition metrics.";
}

void FMeasureMetricPlugin::init(CSelectionData *data, std::map<std::string, CClusterDefinition> *clusterList, IndexType revision)
{
    m_data = data;
    m_clusterList = clusterList;
}

std::vector<std::string> FMeasureMetricPlugin::getDependency()
{
    std::vector<std::string> dependencies;
    dependencies.push_back("coverage");
    dependencies.push_back("partition-metric");
    return dependencies;
}

void FMeasureMetricPlugin::calculate(rapidjson::Document &results)
{
    /*
    std::ofstream fMeasureStream;
    fMeasureStream.open((output + "/f.measure.metric.csv").c_str());
    fMeasureStream << "# cluster;number of testcases in cluster;number of code elements in cluster;fault detection; fault localization; partition metric; f-measure" << std::endl;
    */

    std::map<std::string, CClusterDefinition>::iterator it;
    for (it = m_clusterList->begin(); it != m_clusterList->end(); it++) {

        if (!results.HasMember(it->first.c_str())) {
            rapidjson::Value key;
            key.SetString(it->first.c_str(), results.GetAllocator());
            rapidjson::Value cluster;
            cluster.SetObject();
            results.AddMember(key, cluster, results.GetAllocator());
        }

        double faultDetection = results[it->first.c_str()]["coverage"].GetDouble();
        double partitionMetric = results[it->first.c_str()]["partition-metric"].GetDouble();

        double fMeasure = 0.0;
        if ((faultDetection + partitionMetric) > 0.0) {
            fMeasure = (2 * faultDetection * partitionMetric) / (faultDetection + partitionMetric);
        }

        //IndexType nrOfTestCases = (*m_clusterList)[it->first].getTestCases().size();
        //IndexType nrOfCodeElements = (*m_clusterList)[it->first].getCodeElements().size();

        //fMeasureStream << it->first << ";" << nrOfTestCases << ";" << nrOfCodeElements << ";" << faultDetection << ";" << faultLocalization << ";" << partitionMetric << ";" << fMeasure << std::endl;

        rapidjson::Value::MemberIterator metricIt = results[it->first.c_str()].FindMember("f-measure");
        if (metricIt == results[it->first.c_str()].MemberEnd()) {
            rapidjson::Value v;
            v.SetDouble(fMeasure);
            results[it->first.c_str()].AddMember("f-measure", v, results.GetAllocator());
        } else
            metricIt->value.SetDouble(fMeasure);
    }

    //fMeasureStream.close();
}

extern "C" MSDLL_EXPORT void registerPlugin(CKernel &kernel)
{
    kernel.getTestSuiteMetricPluginManager().addPlugin(new FMeasureMetricPlugin());
}

} /* namespace soda */
