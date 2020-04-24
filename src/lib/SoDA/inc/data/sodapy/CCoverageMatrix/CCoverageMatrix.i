%module ccoveragematrix

%{
#define SWIG_FILE_WITH_INIT
#include "CCoverageMatrix.h" 
#include "CBitMatrix.h" //new BitMatrix()
#include "CBitList.h" //size()
#include "SoDALibDefs.h" 
#include "IIDManager.h" //getIDList(), containsValue(), add(), size() 
#include  "IBitList.h" //push_back() 
#include "CIDManager.h" //new CBitMatrix(), .size()
#include "IBitMatrix.h" //get(), set(), resize(), getNumOfRows(), getNumOfCols() 
%}

	//SoDALibDefs.h innentől
	
	%include <stdint.i>	//u_int64 
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

//CBitList
%rename(__eq__cbitlist) soda::CBitList::operator=(const soda::CBitList::CBitList&);

//CBitMatrix
%rename(__eq__cbitmatrix) soda::CBitMatrix::operator=(const soda::CBitMatrix::CBitMatrix&);



%include "SoDALibDefs.h"
%include "IIDManager.h"
%include "IBitMatrix.h"
%include "IBitList.h"
%include "CCoverageMatrix.h"
%include "CIDManager.h"
%include "CBitMatrix.h"




