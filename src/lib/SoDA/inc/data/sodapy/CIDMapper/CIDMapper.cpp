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
//#include <boost/lexical_cast.hpp>

#include "CBinaryIO.h"
#include "CIDMapper.h"
//#include "CException.h"

namespace soda {

CIDMapper::CIDMapper(IIDManager * globalIdManager) : m_globalIdManager(globalIdManager)
{
    m_globalToLocal.clear();
    m_localToGlobal.clear();
}

CIDMapper::~CIDMapper()
{}

bool CIDMapper::containsValue(const String &value) const  //containsValue() --> CIDMapper.h,  IIDManager.h
{
    if (!m_globalIdManager->containsValue(value)) {
        return false;
    }

    IndexType globalIdx = m_globalIdManager->getID(value);
    if (m_globalToLocal.find(globalIdx) == m_globalToLocal.end()) {
        return false;
    }

    return true;
}

IndexType CIDMapper::getID(const String& value) const   //getID() -->CIDMapper.h , IIDManager.h
{
    if (!m_globalIdManager->containsValue(value)) {
        throw std::out_of_range("Value is not present in the Mapper.");
    }

    IndexType globalIdx = m_globalIdManager->getID(value);

    maptype::const_iterator it = m_globalToLocal.find(globalIdx);
    if(it != m_globalToLocal.end()) {
        return it->second;
    }
    throw std::out_of_range("Value is not present in the Mapper.");
}

String CIDMapper::getValue(const IndexType id) const   //getValue() -->CIDMapper.h, IIDManager.h
{
    return m_globalIdManager->getValue(m_localToGlobal.at(id));
}

IntVector CIDMapper::getIDList() const   //getIDList() --> CIDManager.h , IIDManager.h
{
    IntVector tmp;

    for(maptype::const_iterator it = m_localToGlobal.begin() ; it != m_localToGlobal.end(); it++ ) {
        tmp.push_back(it->first);
    }

    return tmp;
}

StringVector CIDMapper::getValueList() const  //getValueList() --> CIDManager.h , IIDManager.h
{
{
    StringVector tmp;
    for(maptype::const_iterator it = m_localToGlobal.begin() ; it != m_localToGlobal.end(); it++ ) {
        tmp.push_back(m_globalIdManager->getValue(it->second));
    }
    return tmp;
}


IndexType CIDMapper::operator[](const String& codeElementName) const
{
    return getID(codeElementName);
}

IndexType CIDMapper::getLastIndex() const
{
    if (m_localToGlobal.empty()) {
        throw std::length_error("The manager is empty.");
    }
    return m_localToGlobal.rbegin()->first;
}

IndexType CIDMapper::size() const
{
    return m_localToGlobal.size();
}


void CIDMapper::add(const String& value)
{
    IndexType id = 0;
    try {
        id = getLastIndex();
        id++;
    } catch (std::length_error &) {}

    add(id, value);
}


void CIDMapper::remove(const String& value)
{
    if (!m_globalIdManager->containsValue(value)) {
        return;
    }

    IndexType globalIdx = m_globalIdManager->getID(value);
    maptype::iterator it = m_globalToLocal.find(globalIdx);
    if(it != m_globalToLocal.end()) {
        m_localToGlobal.erase(it->second);
        m_globalToLocal.erase(it);
    }
}

void CIDMapper::clear()   //clear()--> IIDManager.h, CIDMapper.h
{
    m_globalToLocal.clear();  
    m_localToGlobal.clear();
}

void CIDMapper::save(io::CBinaryIO *out, const io::CSoDAio::ChunkID chunk) const
{
    unsigned long long int length = sizeof(IndexType);

    for(maptype::const_iterator it = m_localToGlobal.begin() ; it != m_localToGlobal.end(); it++ ) {
        length += m_globalIdManager->getValue(it->second).length();
    }
    length += m_localToGlobal.size() * (1 + sizeof(IndexType));

    //write ChunkID
    out->writeUInt4(chunk);

    //write length
    out->writeULongLong8(length);

    //write the number of elements
    IndexType size = m_localToGlobal.size();
    out->writeLongLong8(size);

    //write elements
    for(maptype::const_iterator it = m_localToGlobal.begin() ; it != m_localToGlobal.end(); it++ ) {
        out->writeLongLong8(it->first);
        out->writeString(m_globalIdManager->getValue(it->second));
    }
}

void CIDMapper::load(io::CBinaryIO *in)
{
    m_localToGlobal.clear();
    m_globalToLocal.clear();
    IndexType size = in->readLongLong8();

    for (IndexType i = 0; i < size; ++i) {
        IndexType index = in->readLongLong8();
        String value = in->readString();
        add(index, value);
    }
}

} /* namespace soda */
