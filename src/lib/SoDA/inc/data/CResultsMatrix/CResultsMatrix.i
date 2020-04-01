%module cresultsmatrix //minden a cresultsmatrix nevű modulba lesz wrappelve cresultsmatrix.py lesz az eredmény.

%import "sys/types.h" //SoDALibDefs.h-ban van

%{
#define SWIG_FILE_WITH_INIT
#include "SoDALibDefs.h"
#include "IIDManager.h"
#include "IBitMatrix.h"
#include "IBitList.h"
#include "CSoDAio.h"
#include "CResultsMatrix.h"
#include "CIDManager.h"
#include "CException.h"
#include "CBitWriter.h"
#include "CBitReader.h"
#include "CBitMatrix.h"
#include "CBitList.h"
#include "CBinaryIO.h"

%}

	//SoDALibDefs.h innentől
	
	%include <stdint.i>	//u_int64 miatt	
	%include "std_string.i" //engedélyezi az std::stringet-t
	%include "std_vector.i" //engedélyezi az std::vector-t
	%include "std_map.i"	//std::map
	%include "std_set.i"	//std::set
	%include "std_list.i"	//std::list
	

		//typedef nevek a SWIG számára
		//https://www.swig.org/Doc2.0/Library.html#Library_std_string
		// 8.4.2 a példa
		
		namespace soda{
		using namespace std;
		%template(IntVector) vector<int>;
		%template(StringVector) vector<String>;
		%template(StringMap) map<IndexType, String>;
		%template(IdxStrMap) map<IndexType, IndexType>;
		%template(ClusterMap) map<string,CClusterDefinition>;
		}

		
		%apply unsigned long long { unsigned u_int64_t };
		
		
		//typedefek a SoDALibDefs-ből a SWIG-nek, hogy értelmezni tudja
		typedef unsigned long long u_int64_t;
		typedef u_int64_t IndexType;
		typedef unsigned int RevNumType;
		typedef CBitList BitList;
		typedef std::string String;
		typedef std::vector<IndexType> IntVector;
		typedef std::vector<String> StringVector;
		typedef std::map<IndexType, String> StringMap;
		typedef std::map<String, IndexType> IdxStrMap;
		typedef std::map<IndexType, IndexType> IdxIdxMap;
		typedef std::map<std::string, CClusterDefinition> ClusterMap;
		
	//SoDALibDefs.h idáig

//a CResultsMatrix-hoz tartozó összes header fájlból az összes operator overloading kigyűjtve, Python másképp kezeli
//ezért át kell nevezni őket
//operator[] alapértelmezetten ilyen nincs pythonba, ezért ha szükségünk van rá a HEADER fájlokba az operator[] köré be kell illeszteni a #ifndef SWIG és #endif párost
//egyébként használjuk az %ignore-t. ha elhagyható
//https://stackoverflow.com/questions/55647750/swig-warning-suppresion-of-operator
// __eq__  operator=  // __getitem__ operator[] // __ne__ operator!= //python oldalán a többi elnevezés


//CBitList
%rename (__eq__cbitlist) soda::CBitList::operator=(const soda::CBitList::CBitlist&);
%rename (__getitem__cbitlist) soda::CBitList::operator[](soda::CBitList::IndexType index);


//CBitMatrix
%rename (__eq__cbitmatrix) soda::CBitMatrix::operator=(const soda::CBitMatrix::CBitMatrix&);
%rename (__getitem__cbitmatrix) soda::CBitMatrix::operator[](soda::CBitMatrix::IndexType row);

//CIDManager
%rename (__getitem__cidmanager) soda::CIDManager::operator[](const soda::CIDManager::IndexType);


//CResultsMatrix
%rename(__eq__cresultsmatrix) soda::CResultsMatrix::operator=(const soda::CResultsMatrix::CResultsMatrix&);


//CSoDAio
%rename(__eq__csodaio) soda::io::CSoDAio::operator=(const soda::io::CSoDAio::CSoDAio&);


//IBitList
%rename (__getitem__ibitlist) soda::IBitList::operator[](soda::IBitList::IndexType index);
%rename (__eq__ibitlist) soda::IBitList::opreator==(const soda::IBitLists::IBitList& rhs);
%rename (__ne__ibitlist) soda::IBitList::operator!=(const soda::IBitLists::IBitList& rhs);

//IBitMatrix
%rename (__eq__ibitmatrix) soda::IBitMatrix::opreator==(const soda::IBitMatrix::IBitMatrix& rhs);
%rename (__ne__ibitmatrix) soda::IBitMatrix::opreator!=(const soda::IBitMatrix::IBitMatrix& rhs);


// http://www.swig.org/Doc1.3/SWIG.html
//"Copy the appropriate declarations into the interface file, or use SWIG's %include directive to process an entire C source/header file.

%include "SoDALibDefs.h"
%include "IIDManager.h"
%include "IBitMatrix.h"
%include "IBitList.h"
%include "CSoDAio.h"
%include "CCResultsMatrix.h"
%include "CIDManager.h"
%include "CException.h"
%include "CBitWriter.h"
%include "CBitReader.h"
%include "CBitMatrix.h"
%include "CBitList.h"
%include "CBinaryIO.h"
%include "sys/types.h"



