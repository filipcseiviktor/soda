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

/*CCoverageMatrix */ 
	%rename(__eq__ccoveragematrix) soda::CCoverageMatrix::CCoverageMatrix& operator=(const CCoverageMatrix&);

/* CBitList */
	%extend soda::CBitList{
		bool __getitem__(IndexType index) const{
			return (*$self)[index];
		}
	}
	%rename(__eq__cbitlist) CBitList::CBitList& operator=(const CBitList&);

/*CBitMatrix*/
	%rename(__eq__cbitmatrix) soda::CBitMatrix::CBitMatrix& operator=(const CBitMatrix&);
	
	
/*long long miatt*/
#ifdef SWIGWORDSIZE64
%define PRIMITIVE_TYPEMAP(NEW_TYPE, TYPE)
%clear NEW_TYPE;
%apply TYPE { NEW_TYPE };
%enddef // PRIMITIVE_TYPEMAP
PRIMITIVE_TYPEMAP(long int, long long);
PRIMITIVE_TYPEMAP(unsigned long int, long long);
#undef PRIMITIVE_TYPEMAP
#endif

/* Parse the header file to generate wrappers */
%include "SoDALibDefs.h"
%include "IIDManager.h"
%include "IBitMatrix.h"
%include "IBitList.h"
%include "CCoverageMatrix.h"
%include "CIDManager.h"
%include "CBitMatrix.h"