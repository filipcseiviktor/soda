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

#include "exception/CException.h"
#include "datareader/CReadResults.h"
#include "datamanager/CResultsDataManager.h"
#include "datamanager/CDataHandler.h"
#include <fstream>

namespace sodatools {

CResultsDataManager::CResultsDataManager() : CDataManager()
{}

CResultsDataManager::CResultsDataManager(CDataHandler *handler) :
    CDataManager(handler)
{}

CResultsDataManager::~CResultsDataManager()
{}

void CResultsDataManager::read(const String &filepath)
{
    INFO(getPrintInfo(), "CResultsDataManager::read(\"" << filepath << "\")");

    switch(getReadFormat()) {
        case rfOneTestPerFile:
            CReadResults(getDataHandler()->getResults(true), true, (getDataHandler()->getCoverage() == NULL), getPrintInfo()).readOneTestPerFileResultsFromDirectoryStructure(filepath);
            break;
        default: throw new CException("CResultsDataManager::read", "Input format not specified");
    }
}

void CResultsDataManager::load(const String &filepath)
{
    INFO(getPrintInfo(), "CResultsDataManager::load(\"" << filepath << "\")");
    path p(filepath);
    if (CDataManager::checkPathOk(p) == 1) {
        if (getDataHandler()->getSelection())
            getDataHandler()->getSelection()->loadResults(filepath.c_str());
        else
            getDataHandler()->getResults(true)->load(filepath);
    } else
        throw new CException("CResultsDataManager::load", filepath + " is not a regular file");
}

void CResultsDataManager::save(const String &filepath)
{
    INFO(getPrintInfo(), "CResultsDataManager::save(\"" << filepath << "\")");
    if (getDataHandler()->getSelection())
        getDataHandler()->getSelection()->getResults()->save(filepath);
    else if (getDataHandler()->getResults())
        getDataHandler()->getResults()->save(filepath);
    else
        WARN("There are no results data to be saved.");
}

void CResultsDataManager::dumpTestcases(const String &filepath)
{
    INFO(getPrintInfo(), "CResultsDataManager::dumpTestcases(\"" << filepath << "\")");
    if (getDataHandler()->getResults() || getDataHandler()->getSelection()) {
        ofstream O(filepath.c_str());
        const IIDManager& idm = (getDataHandler()->getSelection() ? getDataHandler()->getSelection()->getResults() : getDataHandler()->getResults())->getTestcases();
        for(IndexType idx = 0; idx < idm.size(); ++idx) {
            O << idx << ':' << idm[idx] << std::endl;
        }
        O.close();
    } else
        WARN("There are no Results data to be dumped.");
}

void CResultsDataManager::dumpRevisions(const String& filepath)
{
    INFO(getPrintInfo(), "CResultsDataManager::dumpRevisions(\"" << filepath << "\")");
    if (getDataHandler()->getResults() || getDataHandler()->getSelection()) {
        ofstream O(filepath.c_str());
        IntVector revList = (getDataHandler()->getSelection() ? getDataHandler()->getSelection()->getResults() : getDataHandler()->getResults())->getRevisionNumbers();
        for(IndexType idx = 0; idx < revList.size(); ++idx) {
            O << idx << ':' << revList[idx] << std::endl;
        }
        O.close();
    } else {
        WARN("There are no Results data to be dumped.");
    }
}

void CResultsDataManager::dumpExecution(const String& filepath, bool psize, char csep, char rsep)
{
    INFO(getPrintInfo(), "CResultsDataManager::dumpExecution(\"" << filepath << "\")");
    if (getDataHandler()->getResults() || getDataHandler()->getSelection()) {
        ofstream O(filepath.c_str());
        const IBitMatrix& m = (getDataHandler()->getSelection() ? getDataHandler()->getSelection()->getResults() : getDataHandler()->getResults())->getExecutionBitMatrix();
        if (psize) {
            O << m.getNumOfRows() << csep << m.getNumOfCols() << rsep;
        }
        for(IndexType rev = 0; rev < m.getNumOfRows(); ++rev) {
            O << m[rev][0];
            for(IndexType tcidx = 1; tcidx < m.getNumOfCols(); ++tcidx) {
                O << csep << (m[rev][tcidx] ? '1' : '0');
            }
            O << rsep;
        }
        O.close();
    } else {
        WARN("There are no Coverage data to be dumped.");
    }
}

void CResultsDataManager::dumpPassFail(const String& filepath, bool psize, char csep, char rsep)
{
    INFO(getPrintInfo(), "CResultsDataManager::dumpPassFail(\"" << filepath << "\")");
    if (getDataHandler()->getResults() || getDataHandler()->getSelection()) {
        ofstream O(filepath.c_str());
        const IBitMatrix& m = (getDataHandler()->getSelection() ? getDataHandler()->getSelection()->getResults() : getDataHandler()->getResults())->getPassedBitMatrix();
        if(psize) {
            O << m.getNumOfRows() << csep << m.getNumOfCols() << rsep;
        }
        for(IndexType rev=0; rev < m.getNumOfRows(); ++rev) {
            O << m[rev][0];
            for(IndexType tcidx=1; tcidx<m.getNumOfCols(); ++tcidx) {
                O << csep << (m[rev][tcidx] ? '1' : '0');
            }
            O << rsep;
        }
        O.close();
    } else
        WARN("There are no Result data to be dumped.");
}

} // namespace sodatools