%module cchangeset
%{
#define SWIG_FILE_WITH_INIT
#include "SoDALibDefs.h"
#include "CBinaryIO.h"
#include "CChangeset.h"
#include "CIDManager.h"  //new CIDManager(),size(),add()
#include "CIndexBitList.h" //size(),push_back(),begin(),end(),
#include "CRevision.h" //(new CRevision<IBitList*>()),getRevisionNumbers(),size(),getRevision(),revisionExists()
#include "IBitList.h" //(new CRevision<IBitList*>()),size(),at(),push_back(),begin(),end()
#include "IIDManager.h" //size(),add()
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

//IBitList
%rename(__getitem__ibitlist) soda::IBitList::operator[](soda:IBitList::IndexType soda::IBitList::index);

//CRevision
%rename(__eq__crevision) soda::CRevision::operator=(const soda:CRevision CRevision&);

//CIndexBitList
%rename(__eq__cindexbitlist) soda::CIndexBitList::operator=(const soda:CIndexBitList CIndexBitList&);



%include "SoDALibDefs.h"
%include "CBinaryIO.h"
%include "CChangeset.h"
%include "CIDManager.h"
%include "CIndexBitList.h"
%include "CRevision.h"
%include "IBitList.h"
%include "IIDManager.h"