
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

/*CResultsMatrix*/
	%rename(__eq__cresultsmatrix) soda::CResultsMatrix::CResultsMatrix& operator=(const CResultsMatrix&);

/*CIDManager*/
	%extend soda::CIDManager{
		String __getitem__(const IndexType) const{
			return $self[IndexType];
			}
		}

	%extend soda::CIDManager{
		IndexType __getitem__(String&) const{
		return (*$self)[String];
		}
	}
	
/*IIDManager*/
	%extend soda::IIDManager{
		String __getitem__(const IndexType) const{
			return $self[IndexType];
			}
		}

	%extend soda::IIDManager{
		IndexType __getitem__(String&) const{
		return (*$self)[String];
		}
	}

/*CBitMatrix*/
	%rename(__eq__cbitmatrix) soda::CBitMatrix::CBitMatrix& operator=(const CBitMatrix&);


	
/* Parse the header file to generate wrappers */
%include "CResultsMatrix.h" 
%include "CBitMatrix.h" 
%include "SoDALibDefs.h" 
%include "IIDManager.h" 
%include  "IBitList.h" 
%include "CIDManager.h"
%include "IBitMatrix.h"