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

#ifndef CCOVERAGEDATAMANAGER_H
#define CCOVERAGEDATAMANAGER_H

#include "CDataManager.h"

namespace soda {

/**
 * @brief The CCoverageDataManager class contains methods for managing coverage data files.
 */
class CCoverageDataManager : public CDataManager
{
public:

    /**
     * @brief Creates a CCoverageDataManager object with a specified handler.
     * @param handler  CDataHandler object.
     */
    CCoverageDataManager(CDataHandler *handler);

    /**
     * @brief Destroys a CCoverageDataManager object.
     */
    ~CCoverageDataManager();

    /**
     * @brief Loads the content of a coverage data from a specified file.
     * @param filepath  File path.
     * @throw Exception if filepath is not a regular file.
     */
    void load(const String &filepath);

    /**
     * @brief Dumps the coverage matrix to a specified file.
     * @param filepath  File path.
     * @param psize  If true than writes the size of the matrix to the file.
     * @param csep  Column separator.
     * @param rsep  Record separator.
     */
    void dumpData(const String& filepath, bool psize=false, char csep=';', char rsep='\n');

    /**
     * @brief Dumps test case names to a specified file.
     * @param filepath  File path.
     */
    void dumpTestcases(const String &filepath);

    /**
     * @brief Dumps code element names to a specified file.
     * @param filepath  File path.
     */
    void dumpCodeElements(const String &filepath);

    void dumpImage(const String &filepath, int granularity);

    /**
     * @brief Creates an edge list and a node list using the specified filepath as a template.
     *
     *        Node list will contain <id><csep><type><csep><name><rsep> formatted lines, where
     *        <id> is the identifier of an element (unsigned integer), <type> is the type of an
     *        element (test or code), <name> is the name of the test or the code element and
     *        <csep>, <rsep> are the specified column and row separators respectively.
     *
     *        Edge list will contain <src> <dst> formatted lines, where <src> and <dst> are the
     *        ids of test or code elements.
     *
     * @param filepath A template for the file names.
     *        The node and edge lists will be stored in <filepath>.nodes.csv and <filepath>.edges.txt respectively.
     *
     * @param csep A column separator character.
     * @param rsep A row separator character.
     */
    void dumpGraph(const String &filepath, char csep=':', char rsep='\n');

    /**
    * @brief Dumps code element names with test coverage information.
    * @param filepath  File path.
    */
    void dumpCodeElementCoverage(const String &filepath);

    /**
    * @brief Dumps covering tests for the given code element.
    * @param codeElement  The name of code element.
    */
    void dumpCodeElementCoverageFor(const String &codeElement);

    /**
    * @brief Dumps testcases names with code element coverage information.
    * @param filepath  File path.
    */
    void dumpTestCoverage(const String &filepath);

    /**
    * @brief Dumps covering methods for the given test.
    * @param test  The name of test.
    */
    void dumpTestCoverageFor(const String &test);
};

} // namespace soda

#endif /* CCOVERAGEDATAMANAGER_H */
