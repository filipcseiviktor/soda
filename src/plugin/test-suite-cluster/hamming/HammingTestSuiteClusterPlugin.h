/*
 * Copyright (C): 2015 Department of Software Engineering, University of Szeged
 *
 * Authors: Bela Vancsics <vancsics@inf.u-szeged.hu>
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

#ifndef HAMMINGTESTSUITECLUSTERPLUGIN_H
#define HAMMINGTESTSUITECLUSTERPLUGIN_H

#include "engine/CKernel.h"
#include "data/CBitMatrix.h"

namespace soda {


class HammingTestSuiteClusterPlugin : public ITestSuiteClusterPlugin
{
public:

    HammingTestSuiteClusterPlugin();
    ~HammingTestSuiteClusterPlugin();

    std::string getName();

    std::string getDescription();

    std::map<String, String> getRequiredParameters();

    void init(rapidjson::Document &doc);

    void execute(CSelectionData &data, std::map<std::string, CClusterDefinition>& clusterList);

    std::vector<int> clustering_row(CSelectionData &data, int size1, int size2 );

    std::vector<int> clustering_cols(CCoverageMatrix* data);

    bool hamming_row(CSelectionData &data, int index1, int index2, int tolerance, int size);

    bool hamming_cols(CCoverageMatrix* data, int index1, int index2, int tolerance, int size);

    void matrixTranspose(CSelectionData &data, CCoverageMatrix* newMatrix, CBitMatrix* bitMatrix, int numTC, int numCE);

    void setClusterList(int numTC, int numCE, std::map<std::string, CClusterDefinition>& clusterList);


private:
    int m_hamm_diff_row;    // row tolerance (%)
    int m_hamm_diff_cols;   // cols tolerance (%)
    int _0cluster_limit;    // 0cluster tolerance
    std::vector<int> row_cluster_index;
    std::vector<int> cols_cluster_index;

};

} /* namespace soda */

#endif /* HAMMINGTESTSUITECLUSTERPLUGIN_H */
