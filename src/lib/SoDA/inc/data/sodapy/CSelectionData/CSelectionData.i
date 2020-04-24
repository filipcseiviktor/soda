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

//CCoverageMatrix
%rename(__eq__ccoveragematrix) CCoverageMatrix::operator=(const CCoverageMatrix::CCoverageMatrix&);

//CResultsMatrix
%rename(__eq__cresultsmatrix) CResultsMatrix::operator=(const CResultsMatrix::CResultsMatrix&);
//CSoDAio
%rename(__eq__csodaio) CSoDAio::operator=(const CSoDAio::CSoDAio&);


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