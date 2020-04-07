%module crelationmatrix

%{
#define SWIG_FILE_WITH_INIT
#include "CRelationMatrix.h" //ezek kerülnek megvalósításra a cpp-ben
#include "CBitMatrix.h" getNumOfCols(), getNumOfRows(),
#include "CBitList.h"   //set() miatt, 
#include "SoDALibDefs.h"  //minden kell belőle
#include "CIDManager.h" //new CIDManager(),  getID(),  miatt
#include "IBitMatrix.h"  //get()
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



%include "CRelationMatrix.h"
%include "CBitMatrix.h"
%include "CBitList.h"
%include "SoDALibDefs.h"
%include "CIDManager.h"
%include "IBitMatrix.h"


