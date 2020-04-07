//minden a ccoveragematrix nevű modulba lesz wrappelve ccoveragematrix.py lesz az eredmény.
%module ccoveragematrix
%import "sys/types.h" //SoDALibDefs.h-ban van

%{
#define SWIG_FILE_WITH_INIT
#include "CCoverageMatrix.h" //minen kell belőle, cpp-miatt a következők kellenek:
#include "CBitMatrix.h" //new BitMatrix()
#include "CBitList.h" //size()
#include "SoDALibDefs.h" //vektorok és miegyebek
#include "IIDManager.h" //getIDList(), containsValue(), add(), size() miatt cpp-ben
#include  "IBitList.h" //push_back() miatt
#include "CIDManager.h" //new CBitMatrix(), .size() miatt
#include "IBitMatrix.h" //get(), set(), resize(), getNumOfRows(), getNumOfCols() miatt
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



//CCoverageMatrix
%rename(__eq__ccoveragematrix) soda::CCoverageMatrix::operator=(const soda::CCoverageMatrix::CCoverageMatrix&);




%include "SoDALibDefs.h"
%include "IIDManager.h"
%include "IBitMatrix.h"
%include "IBitList.h"
%include "CCoverageMatrix.h"
%include "CIDManager.h"
%include "CBitMatrix.h"




