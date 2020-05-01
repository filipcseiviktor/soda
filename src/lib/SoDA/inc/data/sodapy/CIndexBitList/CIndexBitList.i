%module cindexbitlist
%{
#define SWIG_FILE_WITH_INIT
#include "SoDALibDefs.h"
#include "CBinaryIO.h"
#include "CBitReader.h"
#include "CBitWriter.h"
#include "CSoDAio.h
#include "CIndexBitList.h"
#include "IBitList.h"
#include "IIterators.h"
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


/*CIndexBitList*/
	%rename(__eq__cindexbitlist) soda::CIndexBitList::CIndexBitList& operator=(const CIndexBitList&);

	%extend soda::CIndexBitList{
		bool __getitem__(IndexType pos) const{
			return (*$self)[pos];
		}
	};

/* IBitList */
	%extend soda::IBitList{
		bool __getitem__(IndexType index) const{
			return (*$self)[index];
		}
	}

/* CSoDAio */ 
	%rename(__eq__csodaio) soda::io::CSoDAio::CSoDAio& operator=(const CSoDAio&);

/* IIterators
	%ignore operator++; //nem letezik ++ operator
	%rename(__eq__ibitlistiterator) soda::IBitListIterator::operator==(IBitListIterator&);
	%rename(__ne__ibitlistiterator) soda::IBitListIterator::operator!=(IBitListIterator&);
	%rename(__add__ibitlistiterator) soda::IBitListIterator::operator*();
	%rename(__eq__ibitmatrixiterator) soda::IBitMatrixIterator::operator==(IBitMatrixIterator&);
	%rename(__ne__ibitmatrixiterator) soda::IBitMatrixIterator::operator!=(IBitMatrixIterator&);
	%rename(__add__ibitmatrixiterator) soda::IBitMatrixIterator::operator*();


/* Parse the header file to generate wrappers */
%include "SoDALibDefs.h"
%include "CBinaryIO.h"
%include "CBitReader.h"
%include "CBitWriter.h"
%include "CSoDAio.h
%include "CIndexBitList.h"
%include "IBitList.h"
%include "IIterators.h"