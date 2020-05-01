%module cselectiondata
%{
#define SWIG_FILE_WITH_INIT
#include "CBinaryIO.h"  //load(),
#include "CBitReader.h" //load()
#include "CBitWriter.h" //load()
#include "CBugset.h"  //new CBugset()
#include "CChangeset.h"  //addCodeElementName(),refitSize(),new CChangeset()
#include "CCoverageMatrix.h" //new CCoverageMatrix(),addCodeElementName(),addTestcaseName(),refitMatrixSize()
#include "CIDManager.h"//size(),new CIDManager()
#include "CIDMapper.h"  //size(),new CIDMapper()
#include "CResultsMatrix.h" //new CResultsMatrix(),addTestcaseName(),refitMatrixSize()
#include "CSelectionData.h"
#include "CSoDAio.h" //load()
#include "IBitList.h" //load()
#include "IBitMatrix.h" //load()
#include "IIDManager.h"
#include "SoDALibDefs.h"
%}

%include "std_string.i" /* The std_string.i library provides typemaps for converting C++ std::string objects to and from Python strings */
%include "std_vector.i" // Provide support for the C++ vector class in the STL
%include "std_map.i"	
%include "std_set.i"	
%include "std_list.i"	
%include "stdint.i"   // Include types such as uint32_t, uint8_t, etc.
%include "typemaps.i" // Include types such as uint32_t, uint8_t, etc.

		/*SoDALibDefs.h https://www.swig.org/Doc2.0/Library.html#Library_std_string 8.4.2 */
		

		/* TEMPLATE: Instantiate a Python class called e.g IntVector which wraps a C++ vector<int> STL container */
	namespace soda{
		namespace std{
		%apply unsigned long long *INPUT { u_int64_t }
		
		%template(IndexType) u_int64_t;
		%template(RevNumType) unsigned int;
		%template(BitList) CBitList;
		%template(String) string;
		%template(IntVector) vector<int>;
		%template(StringVector) vector<String>;
		%template(StringMap) map<IndexType, String>;
		%template(IdxStrMap) map<String, IndexType>;
		%template(IdxIdxMap) map<IndexType, IndexType>;
		%template(ClusterMap) map<string,CClusterDefinition>;
		}
	}
	
		/*SoDALibDefs.h idáig */

	
/*
Operators overloaded with their C++ equivalent
__add__,__sub__,__mul__,__div__,__mod__	+,-,*,/,%
__iadd__,__isub__,__imul__,__idiv__,__imod__	+=,-=,*=,/=,%=
__eq__,__ne__,__lt__,__le__,__gt__,__ge__ ==,!=,<,<=,>,>=
__not__,__neg__	unary !, unary -
__and__,__or__,__xor__	logical and,logical or,logical xor
__rshift__,__lshift__ >>,<<
__getitem__,__setitem__ for operator[]							//operator[]-oknal feluldefinialni , mivel pythonba nincs [] operator
*/

/* ha nem kell valahol az operator overloading
%ignore operator+;
%ignore operator-;
%ignore operator*;
%ignore operator+=;
%ignore operator-=;
%ignore operator*=;
%ignore operator==;
%ignore operator!=;
%ignore operator!;
%ignore operator[];
%ignore operator=;
*/

/* IBitList */
	%extend soda::IBitList{
		bool __getitem__(IndexType index) const{
			return (*$self)[index];
		}
	}
	
/*CBugset*/
	%extend soda::CBugset{
	CodeElementReports& __getitem__(const String& revisionNumber) const{
		return (*$self)[revisionNumber];
		}
	}
	
/*IBitMatrix*/
	%extend soda::IBitMatrix{
	IBitList& __getitem__(IndexType row) const{
		return (*$self)[row];
		}
	}
	
/*CCoverageMatrix */ 
	%rename(__eq__ccoveragematrix) soda::CCoverageMatrix::CCoverageMatrix& operator=(const CCoverageMatrix&);

/*CResultsMatrix*/
	%rename(__eq__cresultsmatrix) soda::CResultsMatrix::CResultsMatrix& operator=(const CResultsMatrix&);

/*CSoDAio */ 
	%rename(__eq__csodaio) soda::io::CSoDAio::CSoDAio& operator=(const CSoDAio&);

	

/* Parse the header file to generate wrappers */
%include "CBinaryIO.h"
%include "CBitReader.h"
%include "CBitWriter.h"
%include "CBugset.h"
%include "CChangeset.h"
%include "CCoverageMatrix.h"
%include "CIDManager.h"
%include "CIDMapper.h"
%include "CResultsMatrix.h"
%include "CSelectionData.h"
%include "CSoDAio.h"
%include "IBitList.h"
%include "IBitMatrix.h"
%include "IIDManager.h"
%include "SoDALibDefs.h"