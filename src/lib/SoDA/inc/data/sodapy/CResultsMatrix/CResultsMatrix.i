
%module cresultsmatrix

%{
#define SWIG_FILE_WITH_INIT
#include "CResultsMatrix.h" //minden kell belőle
#include "CBitMatrix.h" //new CBitMatrix()
#include "SoDALibDefs.h" //vektorok és egyebek
#include "IIDManager.h" //size(),add(),containsValue()
#include  "IBitList.h" //set(),get() miatt
#include "CIDManager.h" //new CBitMatrix(), .size() miatt
#include "IBitMatrix.h" //getNumOfCols(),getNumOfRows(),resize() miatt
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
		
		
	
		
	//SoDALibDefs.h idáig



//CResultsMatrix
%rename(__eq__cresultsmatrix) CResultsMatrix::operator=(const CResultsMatrix::CResultsMatrix&);

//CIDManager
%rename (__getitem__indextype_cidmanager) CIDManager::operator[](const CIDManager::String&);

//IIDManager
%rename (__getitem__indextype_iidmanager) IIDManager::operator[](const IIDManager::String&);

//CBitMatrix
%rename(__eq__cbitmatrix) CBitMatrix::operator=(const CBitMatrix::CBitMatrix&);


%include "CResultsMatrix.h" 
%include "CBitMatrix.h" 
%include "SoDALibDefs.h" 
%include "IIDManager.h" 
%include  "IBitList.h" 
%include "CIDManager.h"
%include "IBitMatrix.h" 



