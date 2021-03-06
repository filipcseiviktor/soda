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

#ifndef CSHAREDLIBRARYHANDLER_H
#define CSHAREDLIBRARYHANDLER_H

#include <stdexcept>
#include <string>
#include <iostream>

#ifdef _WIN32
	#include <Windows.h>

	typedef HMODULE SharedLibraryHandle;
#else
	#include <dlfcn.h>

	typedef void* SharedLibraryHandle;
#endif


namespace soda {

#ifdef _WIN32
	/**
	* @brief Class to Load shared libraries from the filesystem.
	*/
	class CSharedLibraryHandler {

	public:

		/**
		* @brief Loads a shared library from the given path.
		* @param path The path to the library.
		* @return
		*/
		static SharedLibraryHandle loadLibrary(const std::string &path)
		{
			SharedLibraryHandle sharedLibraryHandle = LoadLibrary(path.c_str());
			if (sharedLibraryHandle == NULL) {
				throw std::runtime_error("Can not load the shared library.\n\t" + path);
			}

			return sharedLibraryHandle;
		}

		/**
		* @brief Unloads a shared library.
		* @param sharedLibraryHandle The handle of the loaded library.
		*/
		static void  unloadLibrary(SharedLibraryHandle sharedLibraryHandle)
		{
			int result = FreeLibrary(sharedLibraryHandle);
			if (result == 0) {
				throw std::runtime_error("Can not unload the shared library.");
			}
		}

		/**
		* @brief Returns a pointer to a function.
		* @param sharedLibraryHandle The handle of the loaded library.
		* @param functionName The name of the function.
		*/
		template<typename TFunctionSignature>
		static TFunctionSignature *getFunctionPointer(SharedLibraryHandle sharedLibraryHandle, const std::string &functionName)
		{
			FARPROC functionPtr = GetProcAddress(sharedLibraryHandle, functionName.c_str());

			if (functionPtr == NULL) {
				throw std::runtime_error("Can not find the function: " + functionName);
			}
			return reinterpret_cast<TFunctionSignature *>(functionPtr);
		}
	};
#else
	/**
	* @brief Class to Load shared libraries from the filesystem.
	*/
	class CSharedLibraryHandler {

	public:

		/**
		* @brief Loads a shared library from the given path.
		* @param path The path to the library.
		* @return
		*/
		static SharedLibraryHandle loadLibrary(const std::string &path)
		{
			SharedLibraryHandle sharedLibraryHandle = dlopen(path.c_str(), RTLD_NOW);
			if (sharedLibraryHandle == NULL) {
				throw std::runtime_error("Can not load the shared library.\n\t" + std::string(dlerror()));
			}

			return sharedLibraryHandle;
		}

		/**
		* @brief Unloads a shared library.
		* @param sharedLibraryHandle The handle of the loaded library.
		*/
		static void  unloadLibrary(SharedLibraryHandle sharedLibraryHandle)
		{
			int result = dlclose(sharedLibraryHandle);
			if (result != 0) {
				throw std::runtime_error("Can not unload the shared library.");
			}
		}

		/**
		* @brief Returns a pointer to a function.
		* @param sharedLibraryHandle The handle of the loaded library.
		* @param functionName The name of the function.
		*/
		template<typename TFunctionSignature>
		static TFunctionSignature *getFunctionPointer(SharedLibraryHandle sharedLibraryHandle, const std::string &functionName)
		{
			dlerror();

			void *functionAddress = dlsym(sharedLibraryHandle, functionName.c_str());

			char *error = dlerror();
			if (error != NULL) {
				throw std::runtime_error("Can not find the function: " + functionName);
			}
			return reinterpret_cast<TFunctionSignature *>(functionAddress);
		}
	};
#endif



}

#endif /* CSHAREDLIBRARYHANDLER_H */
