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

#include <cmath>

#include "OchiaiFaultLocalizationTechniquePlugin.h"
#include "util/CTestSuiteScore.h"

namespace soda {

OchiaiFaultLocalizationTechniquePlugin::OchiaiFaultLocalizationTechniquePlugin() :
    m_distribution(new FLDistribution()),
    m_flScore(new FLScore()),
    m_data(NULL),
    clusterList(NULL),
    m_revision(0)
{
}

OchiaiFaultLocalizationTechniquePlugin::~OchiaiFaultLocalizationTechniquePlugin()
{
    delete m_distribution;
}

String OchiaiFaultLocalizationTechniquePlugin::getName()
{
    return "ochiai";
}

String OchiaiFaultLocalizationTechniquePlugin::getDescription()
{
    return "Calculates the ochiai value for each code element.";
}

StringVector OchiaiFaultLocalizationTechniquePlugin::getDependency()
{
    return { "common" };
}

void OchiaiFaultLocalizationTechniquePlugin::init(CSelectionData *data, ClusterMap *clusters, IndexType revision, IntVector failedCodeElements)
{
    m_data = data;
    clusterList = clusters;
    m_revision = revision;
    m_failedCodeElements = failedCodeElements;
}

OchiaiFaultLocalizationTechniquePlugin::FLDistribution& OchiaiFaultLocalizationTechniquePlugin::getDistribution()
{
    return *m_distribution;
}

OchiaiFaultLocalizationTechniquePlugin::FLScore& OchiaiFaultLocalizationTechniquePlugin::getFlScore()
{
    return *m_flScore;
}

void OchiaiFaultLocalizationTechniquePlugin::calculate(rapidjson::Document &res)
{
    for (auto it = clusterList->begin(); it != clusterList->end(); it++) {
        m_distribution->clear();

        auto cluster_name = it->first.c_str();
        auto& cluster_def = it->second;

        auto& codeElementIds = cluster_def.getCodeElements();

        // group for cluster data
        if (!res.HasMember(cluster_name)) {
            res.AddMember(rapidjson::Value(cluster_name, res.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), res.GetAllocator());
        }

        auto& cluster_res = res[cluster_name];

        /*for (IndexType i = 0; i < codeElementIds.size(); i++) {
            IndexType cid = codeElementIds[i];
            auto ceIdStr = std::to_string(cid).c_str();

            if (!cluster_res.HasMember(ceIdStr)) {
                cluster_res.AddMember(rapidjson::Value(ceIdStr, res.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), res.GetAllocator());
            }
        }*/

        #pragma omp parallel for schedule(dynamic)
        for (IndexType i = 0; i < codeElementIds.size(); i++) {
            IndexType cid = codeElementIds[i];
            auto ceIdStr = std::to_string(cid).c_str();

            // holds the metric values for one code element
            if (!cluster_res.HasMember(ceIdStr)) {
                #pragma omp critical(json)
                {
                    cluster_res.AddMember(rapidjson::Value(ceIdStr, res.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), res.GetAllocator());
                }
            }

            auto& ceMetrics = cluster_res[ceIdStr];

            IndexType failedCovered = ceMetrics["ef"].GetUint64();
            IndexType passedCovered = ceMetrics["ep"].GetUint64();
            IndexType failedNotCovered = ceMetrics["nf"].GetUint64();
            IndexType passedNotCovered = ceMetrics["np"].GetUint64();

            double ochiai = 0;
            IndexType nrOfFailedTestcases = failedCovered + failedNotCovered;
            IndexType covered = failedCovered + passedCovered;
            if (nrOfFailedTestcases > 0 && covered > 0) {
                double denominator = std::sqrt(nrOfFailedTestcases * covered);
                if (denominator > 0) {
                    ochiai = (double)failedCovered / denominator;
                }
            }

            ceMetrics.AddMember("ochiai", ochiai, res.GetAllocator());
            //(*m_distribution)[ochiai]++;
        }

        /*for (IndexType i = 0; i < m_failedCodeElements.size(); i++) {
            IndexType cid = m_failedCodeElements[i];
            String ceIdStr = std::to_string(cid);
            double ochiai = res[it->first.c_str()][ceIdStr.c_str()]["ochiai"].GetDouble();

            (*m_flScore)[it->first][cid] = CTestSuiteScore::flScore(it->second, ochiai, *m_distribution);

        }*/
    }
}

extern "C" MSDLL_EXPORT void registerPlugin(CKernel &kernel)
{
    kernel.getFaultLocalizationTechniquePluginManager().addPlugin(new OchiaiFaultLocalizationTechniquePlugin());
}

} /* namespace soda */
