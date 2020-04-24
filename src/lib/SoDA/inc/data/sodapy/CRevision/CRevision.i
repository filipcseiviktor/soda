%module crevision

%{
#define SWIG_FILE_WITH_INIT
#include "CRevision.h" 
#include "CBinaryIO.h" // writeInt4(), writeULongLong8(), writeUInt4(),....
#include "CSoDAio.h"
#include "SoDALibDefs.h" 
#include  "IBitList.h" //count(),at(),erase(),push_back(),begin(),end(),size(),clear() miatt
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
		
		
		namespace std{
		%template(IntVector) vector<int>;
		%template(StringVector) vector<String>;
		%template(StringMap) map<IndexType, String>;
		%template(IdxStrMap) map<IndexType, IndexType>;
		%template(ClusterMap) map<string,CClusterDefinition>;
		}

		
		%apply unsigned long long { unsigned u_int64_t };
		
	//SoDALibDefs.h idáig
	
	
//operátorok

//CRevision
%rename(__eq__crevision) CRevision::operator=(const CRevision::CRevision&);


%extend CRevision<T> {
    T& __getitem__(int rev) {
        return $self[i];
     }
}


//IBitList
%rename(__getitem__ibitlist) IBitList::operator[](const CRevision::IndexType CRevision::index);

//CSoDAio
%rename(__eq__csodaio) CSoDAio::operator=(const CSoDAio::CSoDAio&);

//operátorok vége

%include "SoDALibDefs.h"
%include "IBitList.h"
%include "CRevision.h"
%include "CBinaryIO.h"
%include "CSoDAio.h"



