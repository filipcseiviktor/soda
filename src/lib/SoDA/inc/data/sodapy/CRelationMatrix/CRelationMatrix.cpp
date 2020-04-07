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

//#include "CBinaryIO.h"
#include "CRelationMatrix.h"
#include "CBitMatrix.h"
//#include "CException.h"

namespace soda {

CRelationMatrix::CRelationMatrix() :
    m_relations(new CBitMatrix()), //CBitMatrix.h
    m_idManager(new CIDManager()),  //CIDManager.h
    m_createRelations(true),  
    m_createIdManager(true)
{ }



CRelationMatrix::~CRelationMatrix()
{
    if(m_createRelations)
        delete m_relations;

    if(m_createIdManager)
        delete m_idManager;
}


bool CRelationMatrix::getRelation(const String& codeElement1, const String& codeElement2) const
{
    return m_relations->get(m_idManager->getID(codeElement1), m_idManager->getID(codeElement2));  //get() -->IBitMatrix.h,  getID()-->CIDManager.h
}


std::set<String> CRelationMatrix::getImpactSet(const String& codeElementName)
{
    std::set<String> tmp;  //set --> CBitList.h

    for(IndexType i = 0; i < m_relations->getNumOfCols(); i++){  //getNumOfCols()-->CBitMatrix.h
        if ((*this)[codeElementName][i])
            tmp.insert((*m_idManager)[i]);
    }
    return tmp;
}

CIDManager& CRelationMatrix::getIdManager() const
{
    return *m_idManager;
}

IndexType CRelationMatrix::getSize() const
{
    return m_relations->getNumOfRows();   //getNumOfRows()-->CBitMatrix.h
}

const IBitMatrix& CRelationMatrix::getRelationBitMatrix() const
{
    return *m_relations;
}


std::vector<IndexType> CRelationMatrix::computeImpactSetSizes() const
{
    std::vector<IndexType> impactSizeList(m_relations->getNumOfRows()+1);

    for(IndexType i = 0 ; i < getSize(); i++ ) {
        IndexType sum = 0;
        for(IndexType j = 0 ; j < m_relations->getRow(i).size(); j++) {
            if(m_relations->get(i,j)) {                                     //get() -->CBitMatrix.h
                sum++;
            }
        }
        impactSizeList[m_relations->getNumOfRows() - sum]++;
    }

    return impactSizeList;
}


void CRelationMatrix::save(const String& filename) const
{
    save(filename.c_str());
}

void CRelationMatrix::load(const String& filename)
{
    load(filename.c_str());
}

} // namespace soda
