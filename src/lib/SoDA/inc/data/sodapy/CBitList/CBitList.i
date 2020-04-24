%module cbitlist
%{
#define SWIG_FILE_WITH_INIT
#include "SoDALibDefs.h"
#include "CBinaryIO.h"
#include "CBitList.h"
#include "CBitReader.h"
#include "CBitWriter.h"
#include "CSoDAio.h"
#include "IBitList.h"
#include "IIterators.h"
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


//IBitList
%rename(__getitem__ibitlist) IBitList::operator[](IBitList::IndexType IBitList::index);

//CBitList
%rename(__getitem__cbitlist) CBitList::operator[](CBitList::IndexType CBitList::index);

//CSoDAio
%rename(__eq__csodaio) CSoDAio::operator=(const CSoDAio::CSoDAio&);

//IIterators



%include "SoDALibDefs.h"
%include "CBinaryIO.h"
%include "CBitList.h"
%include "CBitReader.h"
%include "CBitWriter.h"
%include "CSoDAio.h"
%include "IBitList.h"
%include "IIterators.h"