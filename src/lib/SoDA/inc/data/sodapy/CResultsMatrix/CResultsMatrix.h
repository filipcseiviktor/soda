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

#ifndef CRESULTSMATRIX_H
#define CRESULTSMATRIX_H


#include "IBitMatrix.h"
#include "IIDManager.h"
 //#include "CRevision.h" //elméletileg ez nem kell

namespace soda {

/**
 * @brief The CResultsMatrix class stores number of test results.
 */
class CResultsMatrix {
public:

    enum TestResultType { trtNotExecuted=0, trtFailed=2, trtPassed=3 };

    /**
     * @brief Constructor, creates an empty CResultsMatrix object.
     */
    CResultsMatrix();



    /**
     * @brief Destroys a CResultsMatrix object.
     */
    virtual ~CResultsMatrix();

    /**
     * @brief Returns a reference to the revisions.
     * @return Reference to the revisions.
     */
    virtual const CRevision<IndexType>& getRevisions() const;

    /**
     * @brief Returns the revision numbers as an int vector.
     * @return Revision number as an int vector.
     */
    virtual IntVector getRevisionNumbers() const;

    /**
     * @brief Returns the number of test cases.
     * @return Number of test cases.
     */
    virtual const IndexType getNumOfTestcases() const;

    /**
     * @brief Returns the number of revisions.
     * @return Number of revisions.
     */
    virtual const IndexType getNumOfRevisions() const;


    /**
     * @brief Returns the result of the specified test.
     * @param revision  Revision number.
     * @param testcaseName  Test case name.
     * @return Result of the specified test.
     */
    virtual TestResultType getResult(const int revision, const String& testcaseName) const;


    /**
     * @brief Returns true if the specified test is in the execution bitmatrix.
     * @param revision  Revision number.
     * @param testcaseName  Test case name.
     * @return True if the specified test is in the execution bitmatrix.
     */
    virtual bool isExecuted(const int revision, const String& testcaseName) const;

    /**
     * @brief Returns true if the specified test is in the execution and passed bitmatrix.
     * @param revision  Revision number.
     * @param testcaseName  Test case name.
     * @return True if the specified test is in the execution passed bitmatrix.
     */
    virtual bool isPassed(const int revision, const String& testcaseName) const;

    /**
     * @brief Set the result of a specified test.
     * @param revision  Revision number.
     * @param testcaseName  Test case name.
     * @param result  Result of the test.
     */
    virtual void setResult(const int revision, const String& testcaseName, const TestResultType result);

    /**
     * @brief Add or set the result of a specified test.
     * @param revision  Revision number.
     * @param testcaseName  Test case name.
     * @param result  Result of the test.
     */
    virtual void addOrSetResult(const int revision, const String& testcaseName, const TestResultType result);

    /**
     * @brief Resizes the bit matrixes for size of IIDManager and CRevision.
     */
    virtual void refitMatrixSize();

    /**
     * @brief Adds a new revision to the CRevision list if it's not in it.
     * WARNING: This method does not allocate new memory for the matrix!
     *                    Use refitMatrixSize()!
     */
    virtual void addRevisionNumber(const int);

    /**
     * @brief Adds a specified test case name to the IIDManager if it's not in it.
     *        WARNING: This method does not allocate new rows!
     *                    Use refitMatrixSize()!
     */
    virtual void addTestcaseName(const String&);


    /**
     * @brief Writes the content of a CResultsMatrix to a specified file.
     * @param filename  Specified file.
     */
    virtual void save(const String& filename) const;

    /**


    /**
     * @brief Loads the content of a CResultsMatrix from a specified file.
     * @param filename  Specified file.
     */
    virtual void load(const String& filename);

private:

    /**
     * @brief Stores id,test case name pairs in an IIDManager.
     */
    IIDManager* m_testcases;

    /**
     * @brief Stores revision data.
     */
    CRevision<IndexType>* m_revisions;

    /**
     * @brief Stores the execution results in a bitmatrix.
     */
    IBitMatrix* m_exec;

    /**
     * @brief Stores the passed results in a bitmatrix
     */
    IBitMatrix* m_pass;

    /**
     * @brief If true than the constructor creates test cases IIDManager.
     */
    bool m_createTestcases;

    /**
     * @brief If true than the constructor creates revision object.
     */
    bool m_createRevisions;

    /**
     * @brief If true than the constructor creates the execution bitmatrix.
     */
    bool m_createExecutionBitMatrix;

    /**
     * @brief If true than the constructor creates the passed bitmatrix.
     */
    bool m_createPassedBitMatrix;

private:

    /**
     * @brief NIY copy constructor.
     */
    CResultsMatrix(const CResultsMatrix&);

    /**
     * @brief NIY operator =.
     * @return Reference to a CResultsMatrix object.
     */
    CResultsMatrix& operator=(const CResultsMatrix&);
};

} // namespace soda

#endif /* CRESULTSMATRIX_H */
