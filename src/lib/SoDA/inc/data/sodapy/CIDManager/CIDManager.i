%module cidmanager
%{
#define SWIG_FILE_WITH_INIT
#include "SoDALibDefs.h"
#include "CBinaryIO.h"
#include "CSoDAio.h"
#include "IIDManager.h" 
#include "CIDManager.h"  
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

//operátorok

//CIDManager
%rename(__getitem__cidmanager_string) soda::CIDManager::operator[](const soda::CIDManager::IndexType);
%rename(__getitem__cidmanager_indextype) soda::CIDManager::operator[](const soda::CIDManager::String&);

//IIDManager
%rename(__getitem__iidmanager_string) soda::IIDManager::operator[](const soda::IIDManager::IndexType);
%rename(__getitem__iidmanager_indextype) soda::IIDManager::operator[](const soda::IIDManager::String&);



%include "SoDALibDefs.h"
%include "CBinaryIO.h"
%include "CSoDAio.h"
%include "IIDManager.h"
%include "CIDManager.h"