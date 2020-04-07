/*
 * Copyright (C): 2013-2014 Department of Software Engineering, University of Szeged
 *
 * Authors: László Langó <lango@inf.u-szeged.hu>
 *          Tamás Gergely <gertom@inf.u-szeged.hu>
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



#include "CResultsMatrix.h"
#include "CBitMatrix.h"
#include "CIDManager.h"

namespace soda {

CResultsMatrix::CResultsMatrix() :
    m_testcases(new CIDManager()),  //new CIDManager()-->CIDManager.h
    m_revisions(new CRevision<IndexType>()),
    m_exec(new CBitMatrix()),  //new CBitMatrix --> CBitMatrix.h
    m_pass(new CBitMatrix()),  //CBitMatrix.h
    m_createTestcases(true),
    m_createRevisions(true),
    m_createExecutionBitMatrix(true),
    m_createPassedBitMatrix(true)
{}

CResultsMatrix::~CResultsMatrix()
{
    if(m_createTestcases)
        delete m_testcases;
    if(m_createRevisions)
        delete m_revisions;
    if(m_createExecutionBitMatrix)
        delete m_exec;
    if(m_createPassedBitMatrix)
        delete m_pass;
}

IntVector CResultsMatrix::getRevisionNumbers() const //CCoverageMatrix.h
{
    return m_revisions->getRevisionNumbers();
}

const CRevision<IndexType>& CResultsMatrix::getRevisions() const //CCoverageMatrix.h
{
    return *m_revisions;
}


const IndexType CResultsMatrix::getNumOfTestcases() const //size()-->IIDManager.h
{
    return m_testcases->size(); 
}

const IndexType CResultsMatrix::getNumOfRevisions() const //size()-->IIDManager.h
{
    return m_revisions->size();
}

CResultsMatrix::TestResultType CResultsMatrix::getResult(const int revision, const String& testcaseName) const //CCoverageMatrix.h
{
    IndexType testcaseID = (*m_testcases)[testcaseName];
    return getResult(revision, testcaseID);
}

CResultsMatrix::TestResultType CResultsMatrix::getResult(const int revision, const IndexType testcaseID) const //CCoverageMatrix.h
{
    return (TestResultType)
          (((*m_exec)[(*m_revisions)[revision]][testcaseID] << 1) |
           ((*m_exec)[(*m_revisions)[revision]][testcaseID] &
            (*m_pass)[(*m_revisions)[revision]][testcaseID]));
}

bool CResultsMatrix::isExecuted(const int revision, const String& testcaseName) const //CCoverageMatrix.h
{
    return (*m_exec)[(*m_revisions)[revision]][(*m_testcases)[testcaseName]];
}

bool CResultsMatrix::isPassed(const int revision, const String& testcaseName) const //CCoverageMatrix.h
{
    return (*m_exec)[(*m_revisions)[revision]][(*m_testcases)[testcaseName]] &&
           (*m_pass)[(*m_revisions)[revision]][(*m_testcases)[testcaseName]];
}

void CResultsMatrix::setResult(const int revision, const String& testcaseName, const CResultsMatrix::TestResultType result) //CCoverageMatrix.h
{
    if(!m_revisions->revisionExists(revision) || !m_testcases->containsValue(testcaseName)) {  //containsValue()-->IIDManager.h
        //throw CException("CResultsMatrix::setRelation()", "Results matrix does not contain item!");
    }
    m_exec->set((*m_revisions)[revision], (*m_testcases)[testcaseName], result != trtNotExecuted );
    m_pass->set((*m_revisions)[revision], (*m_testcases)[testcaseName], result == trtPassed);
}

void CResultsMatrix::setResult(const int revision, const IndexType testcaseID, const CResultsMatrix::TestResultType result)  //CCoverageMatrix.h
{
    if(!m_revisions->revisionExists(revision) || m_testcases->size() <= testcaseID) {   //size()-->IIDManager.h
       // throw CException("CResultsMatrix::setRelation()", "Results matrix does not contain item!");
    }
    m_exec->set((*m_revisions)[revision], testcaseID, result != trtNotExecuted );
    m_pass->set((*m_revisions)[revision], testcaseID, result == trtPassed);
}

void CResultsMatrix::addOrSetResult(const int revision, const String& testcaseName, const CResultsMatrix::TestResultType result)   //CCoverageMatrix.h
{
    if(!m_revisions->revisionExists(revision)) {
        IndexType index = m_exec->getNumOfRows();  //getNumOfRows()-->IBitMatrix.h
        m_exec->resize(m_exec->getNumOfRows()+1, m_exec->getNumOfCols()); //getNumOfCols()-->IBitMatrix.h
        m_pass->resize(m_pass->getNumOfRows()+1, m_pass->getNumOfCols());
        m_revisions->addRevision(revision, index);
    }
    if(!m_testcases->containsValue(testcaseName)) {
        m_exec->resize(m_exec->getNumOfRows(), m_exec->getNumOfCols()+1); //resize()-->IBitMatrix.h
        m_pass->resize(m_pass->getNumOfRows(), m_pass->getNumOfCols()+1);
        m_testcases->add(m_exec->getNumOfCols()-1, testcaseName);
    }
    m_exec->set((*m_revisions)[revision], (*m_testcases)[testcaseName], result != trtNotExecuted );
    m_pass->set((*m_revisions)[revision], (*m_testcases)[testcaseName], result == trtPassed);
}

void CResultsMatrix::refitMatrixSize()  //CCoverageMatrix.h
{
    m_exec->resize(m_revisions->size(), m_testcases->size());
    m_pass->resize(m_revisions->size(), m_testcases->size());
}

void CResultsMatrix::addRevisionNumber(const int revision)  //CCoverageMatrix.h
{
    if(!m_revisions->revisionExists(revision)) {
        IndexType index = m_revisions->size();
        m_revisions->addRevision(revision, index);
    }
}

void CResultsMatrix::addTestcaseName(const String& testcaseName)   //CCoverageMatrix.h
{
    if(!m_testcases->containsValue(testcaseName)) {
        m_testcases->add(testcaseName); //add()-->IIDManager.h  
    }
}


void CResultsMatrix::save(const String& filename) const  //CCoverageMatrix.h
{
    save(filename.c_str());
}

void CResultsMatrix::load(const String& filename)   //CCoverageMatrix.h
{
    load(filename.c_str());
}

} /* namespace soda */
