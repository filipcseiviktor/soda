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

#include <stdexcept>

#include "CCoverageMatrix.h" 
#include "CBitMatrix.h"
#include "CIDManager.h"

namespace soda {


//SODALIBDEFSBŐL MINDEN KELL  (vektorok miatt stb)


CCoverageMatrix::CCoverageMatrix() :
    m_testcases(new CIDManager()), //CCoverageMatrix.h--> IIDManager* m_testcases; //  CIDManager.h-->CIDManager();
    m_codeElements(new CIDManager()), //CCoverageMatrix.h-->IIDManager* m_codeElements;  // CIDManager.h-->CIDManager();
    m_data(new CBitMatrix()), //CCoverageMatrix.h--IBitMatrix* m_data //CBitMatrix.h-->CBitMatrix()
    m_createTestcases(true),//CCoverageMatrix.h
    m_createCodeElements(true),//CCoverageMatrix.h
    m_createBitMatrix(true)  //CCoverageMatrix.h
{ }




CCoverageMatrix::~CCoverageMatrix()  //CCoverage.h
{
    if(m_createTestcases) {
        delete m_testcases;
    }
    if(m_createCodeElements) {
        delete m_codeElements;
    }
    if(m_createBitMatrix) {
        delete m_data;
    }
}


StringVector CCoverageMatrix::getTestcases(const String& codeElementName) const//CCoverage.h
{
    StringVector testcaseList; //SoDALibDefs.h typedef std::vector<String> StringVector;  és minden mást is onnan
    if (!m_codeElements->containsValue(codeElementName)) {  //containsValue-->IIDManager.h
        return testcaseList;
    }

    for(IndexType i = 0; i < getNumOfTestcases(); i++) {  
        if((*m_data)[i][(*m_codeElements)[codeElementName]]) {
            testcaseList.push_back((*m_testcases)[i]);  //push_back-->IBitList.h
        }
    }
    return testcaseList;
}


StringVector CCoverageMatrix::getCodeElements(const String& testcaseName) const  //CCoverage.h
{
    StringVector codeElementsList;
    if (!m_testcases->containsValue(testcaseName)) {  //containsValue-->IIDManager.h
        return codeElementsList;
    }

    for(IndexType i = 0; i < getNumOfCodeElements(); i++) {
        if((*m_data)[(*m_testcases)[testcaseName]][i]) {
            codeElementsList.push_back((*m_codeElements)[i]);  //push_back-->IBitList.h
        }
    }

    return codeElementsList;
}


const IndexType CCoverageMatrix::getNumOfTestcases() const
{
    return m_testcases->getIDList().size();  //getIDLIST() --> IIDManager.h   //.size() -->CBitList.h, IBitList.h, CIDManager.h
}

const IndexType CCoverageMatrix::getNumOfCodeElements() const
{
    return m_codeElements->getIDList().size(); //getIDLIST() --> IIDManager.h    //.size() -->CBitList.h, IBitList.h, CIDManager.h
}




bool CCoverageMatrix::getRelation(const String& testcaseName, const String& codeElementName) const
{
    if (!m_testcases->containsValue(testcaseName) || !m_codeElements->containsValue(codeElementName)) {}
        

    return m_data->get((*m_testcases)[testcaseName], (*m_codeElements)[codeElementName]);  
    //get()--> IBitMatrix.h-->virtual bool get(IndexType row, IndexType col) const = 0;
}

void CCoverageMatrix::setRelation(const String& testcaseName, const String& codeElementName, const bool isCovered)
{
    try {
        m_data->set((*m_testcases)[testcaseName], (*m_codeElements)[codeElementName], isCovered);
        //set()--> IBitMatrix.h--> virtual void set(IndexType row, IndexType col, bool value) = 0;
    } catch () {}
}       

void CCoverageMatrix::addOrSetRelation(const String& testcaseName, const String& codeElementName, const bool isCovered)
{
    if (!m_testcases->containsValue(testcaseName)) {
        m_data->resize(m_data->getNumOfRows()+1, m_data->getNumOfCols()); 
         //resize() -->IBitmatrix.h-->virtual void resize(IndexType newRow, IndexType newCol) = 0;
         //getNumOfRows()-->IBitMatrix.h-->virtual IndexType getNumOfRows() const = 0;
         // getNumOfCols()-->IBitMatrix.h-->virtual IndexType getNumOfCols() const = 0;
        m_testcases->add(m_data->getNumOfRows()-1, testcaseName);
        //add()-->IIDManager.h--> virtual void add(const IndexType, const String&) = 0;

    }

    if (!m_codeElements->containsValue(codeElementName)) {
        m_data->resize(m_data->getNumOfRows(), m_data->getNumOfCols()+1);
        m_codeElements->add(m_data->getNumOfCols()-1, codeElementName);
    }

    m_data->set((*m_testcases)[testcaseName], (*m_codeElements)[codeElementName], isCovered);
}

void CCoverageMatrix::refitMatrixSize()
{
    m_data->resize(m_testcases->size(), m_codeElements->size());
}

void CCoverageMatrix::addTestcaseName(const String& testcaseName)
{
    if (!m_testcases->containsValue(testcaseName)) {
        m_testcases->add(testcaseName);
    }
}

void CCoverageMatrix::addCodeElementName(const String& codeElementName)
{
    if (!m_codeElements->containsValue(codeElementName)) {
        m_codeElements->add(codeElementName);
    }
}


void CCoverageMatrix::save(const String& filename) const
{
    save(filename.c_str());
}

void CCoverageMatrix::load(const String& filename)
{
    load(filename.c_str());
}

} // namespace soda
