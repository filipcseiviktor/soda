/*
 * Copyright (C): 2013-2014 Department of Software Engineering, University of Szeged
 *
 * Authors: David Tengeri <dtengeri@inf.u-szeged.hu>
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

#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "CTraceLogger.h"
#include "exception/CException.h"

namespace soda {

CTraceLogger::CTraceLogger(int socket, CTraceData *data) :
    m_socket(socket),
    m_data(data)
{
}

CTraceLogger::~CTraceLogger()
{
}

void CTraceLogger::run()
{
    bool isOpen = true;
    while (isOpen) {
        char type;
        /* read returns zero, the client closed the connection. */
        if (read(m_socket, &type, sizeof (type)) == 0) {
            return;
        }
        switch (type) {
        case CTraceLogger::INSTRUMENT_TEST_MSG:
            handleTestMessage();
            break;
        case INSTRUMENT_FUNCTION_ENTER_MSG:
            handleFunctionEnterMessage();
            break;
        case INSTRUMENT_FUNCTION_EXIT_MSG:
            handleFunctionExitMessage();
            break;
        case INSTRUMENT_CLOSE_MSG:
            close(m_socket);
            isOpen = false;
            (std::cout << " done." << std::endl).flush();
            break;
        default:
            break;
        }
    }
}

void CTraceLogger::handleTestMessage()
{
    ssize_t len;
    size_t length;
    char* text;
    m_testcaseName = "";
    // Read the length of the test name.
    len = read(m_socket, &length, sizeof (length));
    if (len < 0) {
        return;
    }
    text = new char[length];
    // Read the test name.
    len = read(m_socket, text, length);
    if (len < 0) {
        return;
    }

    m_testcaseName = String(text);

    (std::cout << "Processing test: " << m_testcaseName << " ... ").flush();

    delete text;
}


String CTraceLogger::handleFunctionMessage()
{
    ssize_t len;
    size_t length;
    int address;
    char* text;
    String function = "";

    // Read the length of the binary path.
    len = read(m_socket, &length, sizeof (length));
    if (len < 0) {
        return function;
    }

    text = new char[length];
    // Read the test name.
    len = read(m_socket, text, length);
    if (len < 0) {
        return function;
    }

    // Read the address.
    len = read(m_socket, &address, sizeof(address));
    if (len < 0) {
        return function;
    }

    String binaryPath = String(text);

    try {
        function = m_data->getFunctionName(binaryPath, address);
    } catch (CException &e) {
        String output = translateAddressToFunction(binaryPath, address);
        function = output.substr(0, output.find(" at "));
        m_data->addFunctionName(binaryPath, address, function);
    }

    /* Free the buffer. */
    delete text;

    return function;
}


void CTraceLogger::handleFunctionEnterMessage()
{
    if (m_testcaseName.length() == 0) {
        return;
    }

    String function = handleFunctionMessage();
    if (!function.length()) {
        return;
    }
    m_data->setCoverage(m_testcaseName, function);
}

void CTraceLogger::handleFunctionExitMessage()
{
    // Do nothing now.
}

String CTraceLogger::translateAddressToFunction(const String &binaryPath, const int address)
{
    std::ostringstream command;
    if (access(binaryPath.c_str(), F_OK) == 0) {
        command << "addr2line -C -f -p -e " << binaryPath << " 0x" << std::hex << address;
    } else {
        command << "addr2line -C -f -p -e " << m_data->getBaseDir() << "/" << binaryPath << " 0x" << std::hex << address;
    }
    FILE *pf;
    pf = popen(command.str().c_str(), "r");
    if (!pf) {
        //TODO throw exception
    }
    String output = "";
    char *buf = new char[3072];
    if (fgets(buf, 3072, pf) != NULL) {
        output = String(buf);
    }

    delete buf;
    pclose(pf);

    return output;
}

int CTraceLogger::getSocket()
{
    return m_socket;
}

}