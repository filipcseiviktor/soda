/*
 * Copyright (C): 2013-2014 Department of Software Engineering, University of Szeged
 *
 * Authors: Tamás Gergely <gertom@inf.u-szeged.hu>
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

#ifndef GENERALIGNOREPRIORIZATIONALGORITHM_H
#define GENERALIGNOREPRIORIZATIONALGORITHM_H

#include "../IPriorizationAlgorithmPlugin.h"
#include "data/CCoverageMatrix.h"

namespace soda {

/**
 * @brief Prioritization algorithm that is based on coverage information.
 *          - testcase covering more functions has higher coverage
 */
class GeneralIgnorePriorizationAlgorithmPlugin : public IPrioritizationAlgorithmPlugin
{
private:
    typedef struct {
        IndexType testcaseId;
        IndexType priorityValue;
    } qelement;
    friend bool operator<(qelement d1, qelement d2);

public:
    /**
     * @brief Creates a new instance.
     * @param [in] coverageMatrix The matrix we are working on.
     */
    GeneralIgnorePriorizationAlgorithmPlugin(CCoverageMatrix* coverageMatrix);

    ~GeneralIgnorePriorizationAlgorithmPlugin();

    /**
     * @brief Returns the name of the plugin.
     * @return
     */
    virtual String getName() = 0;

    /**
     * @brief Returns the description of the plugin.
     * @return
     */
    virtual String getDescription() = 0;

    /**
     * @brief Gets the first n prioritized testcases.
     * @param selected The result vector.
     * @param size The number of testcases we want to select.
     */
    void fillSelection(IntVector& selected, size_t size);

    /**
     * @brief Revision data is not used by this algorithm.
     */
    void reset(RevNumType) { return; }

private:
    CCoverageMatrix*       m_coverageMatrix;
    size_t                 m_nofElementsReady;
    IntVector*             m_elementsReady;
    std::vector<qelement>* m_priorityQueue;
};

} /* namespace soda */

#endif /* CPRIORITIZATIONGENERALIGNORE_H_ */
