%module creductiondata
%{
#define SWIG_FILE_WITH_INIT
#include "SoDALibDefs.h"
#include "CBinaryIO.h"
#include "CBitReader.h"
#include "CBitWriter.h"
#include "CReductionData.h"
#include "CSoDAio.h"
#include "CCoverageMatrix.h" //refitMatrixSize(),getCodeElements(),getNumOfTestcases(),getTestcases(),addTestcaseName()
#include "CIDManager.h" //new CIDManager(),size()
#include "IBitList.h"  //size(),
#include "IBitMatrix.h" //save(), begin(), end()
#include "IIDManager.h" //size(),getValue(),m_coverage(new CCoverageMatrix(m_testcases, const_cast<IIDManager *>(&(baseCoverage->getCodeElements()))))
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

/*IBitMatrix*/
	%extend soda::CBitMatrix{
			IBitList& __getitem__(IndexType row){
				return (*$self)[row];
				}
			}
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


/* CCoverageMatrix */ 
	%rename(__eq__ccoveragematrix) soda::CCoverageMatrix::CCoverageMatrix& operator=(const CCoverageMatrix&);

/* CSoDAio */ 
	%rename(__eq__csodaio) soda::io::CSoDAio::CSoDAio& operator=(const CSoDAio&);
	
	/* a cel, hogy a python oldalon a modul importalasa utan pl. ne "creductiondata.RELATION" -kent kelljen hivatkozzunk, hanem lehessen a kovetkezokepp:
		"cbitlist.CHUNKID.RELATION" */
	/* https://stackoverflow.com/questions/50353506/swig-convert-c-enum-to-python-enum */
	%inline %{
		namespace soda{
			namespace io{
				enum ChunkID{
					UNKNOWN_TYPE = 0,
					COVERAGE = 123456,
					RELATION,
					IDMANAGER,
					TCLIST,
					PRLIST,
					REVISIONS,
					BITMATRIX,
					BITLIST,
					EXECUTION,
					PASSED,
					CHANGESET,
					CODEELEMENT_TRACE,
					REVLIST,
					BUGSET
				 };
		}
	}
	%}
/* CBinaryIO */	
	
	%inline %{
				namespace soda{
					namespace io{
						enum eOpenMode {
							omRead,
							omWrite
						};
				}
			}
			%}

	
/* enum-hoz kell*/
%pythoncode %{
from enum import Enum
def enum(prefix):
    tmpD = {k:v for k,v in globals().items() if k.startswith(prefix + '_')}
    for k,v in tmpD.items():
        del globals()[k]
    tmpD = {k[len(prefix)+1:]:v for k,v in tmpD.items()}
    globals()[prefix] = Enum(prefix,tmpD)
%}
	
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
%include "CBinaryIO.h"
%include "CBitReader.h"
%include "CBitWriter.h"
%include "CCoverageMatrix.h"
%include "CIDManager.h"
%include "CReductionData.h"
%include "CSoDAio.h"
%include "IBitList.h"
%include "IBitMatrix.h"
%include "IIDManager.h"
%include "SoDALibDefs.h"