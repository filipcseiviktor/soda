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

#ifndef CREVISION_H
#define CREVISION_H

//#include "CSoDAio.h"
#include "CBinaryIO.h"  //én szúrtam be, CSoDAio nem kell
#include "SoDALibDefs.h"

namespace soda {

/**
 * @brief The CRevision class is a template class which stores revision number, Type pairs in a map
 *        where Type is a specified data structure. At special data types you might need to override template
 *        implementation of class methods.
 */
template <typename T>
class CRevision {
public:

    /**
     * @brief Constructor, creates an empty CRevision.
     */
    CRevision();  //cpp-hez kell

    /**
     * @brief Destroys a CRevision object.
     */
    ~CRevision();  //cpp-hez kell

    /**
     * @brief Returns true if the given revision number is in the revision map.
     * @param rev  Specified revision number.
     * @return True if the given revision is in the revision map otherwise false.
     */
    bool revisionExists(const RevNumType rev) const; //cpp-hez kell
 
    /**
     * @brief Returns a reference to the value of the specified revision number.
     * @param rev  Specified revision number.
     * @return Reference to the value of the specified revision number.
     */
    T& getRevision(const RevNumType rev);  //cpp-hez kell
   /**
     * @brief Returns the revision numbers stored in the revision map as a vector
     * @return The revision numbers stored in the revision map as a vector.
     */
    IntVector getRevisionNumbers() const;  //cpp-hez kell

    /**
     * @brief Returns the number of elements in the revision map.
     * @return Number of elements in the revision map.
     */
    typename std::map<RevNumType, T>::size_type size() const; //cpp-hez kell


////////////////////////////////////////////////////////////////////////////



    /**
     * @brief Adds a new element to the revision map with a specified revision number and data structure pair.
     * @param revNum  Specified revision number.
     * @param datastructure  Specified data structure.

    void addRevision(const RevNumType revNum, T& datastructure);

    /**
     * @brief Removes the specified revision number from the revision map.
     * @param revNum  Specified revision number.
   
    void removeRevision(const RevNumType revNum);


    /**
     * @brief Returns a reference to the value of the specified revision number.
     * @param rev  Specified revision number.
     * @return Reference to the value of the specified revision number.

    T& operator[](const int rev);

    /**
     * @brief Saves the content of a manager to the out.
     * @param out  Output stream.
     * @param chunk  Type of the data.

    void save(io::CBinaryIO *out, const io::CSoDAio::ChunkID chunk = io::CSoDAio::REVISIONS) const;

    /**
     * @brief Loads the content of a revision map from the in.
     * @param in  Input stream.

    void load(io::CBinaryIO *in) const;     */

private:

    /**
     * @brief Stores revision number, type pairs.
     */
    std::map<RevNumType, T>* m_data;

private:

    /**
     * @brief NIY Copy constructor.
     */
    CRevision(const CRevision&);

    /**
     * @brief NIY operator =.
     * @return Reference to a CRevision object.
     */
    CRevision& operator=(const CRevision&);
};

} // namespace soda

#endif /* CREVISION_H */
