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
%rename(__getitem__cidmanager_string) CIDManager::operator[](const CIDManager::IndexType);
%rename(__getitem__cidmanager_indextype) CIDManager::operator[](const CIDManager::String&);

//IIDManager
%rename(__getitem__iidmanager_string) IIDManager::operator[](const IIDManager::IndexType);
%rename(__getitem__iidmanager_indextype) IIDManager::operator[](const IIDManager::String&);

//IBitList
%rename(__getitem__ibitlist) IBitList::operator[](IBitList::IndexType IBitList::index);

//CRevision
%rename(__eq__crevision) CRevision::operator=(const CRevision CRevision&);

//CIndexBitList
%rename(__eq__cindexbitlist) CIndexBitList::operator=(const CIndexBitList CIndexBitList&);



%include "SoDALibDefs.h"
%include "CBinaryIO.h"
%include "CChangeset.h"
%include "CIDManager.h"
%include "CIndexBitList.h"
%include "CRevision.h"
%include "IBitList.h"
%include "IIDManager.h"