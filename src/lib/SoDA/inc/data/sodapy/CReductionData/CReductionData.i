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

//IIDManager
%rename(__get__iidmanager_string) soda::IIDManager::operator[](const soda::IIDManager::IndexType);
%rename(__get__iidmanager_indextype) soda::IIDManager::operator[](const soda::IIDManager::String&);
//CIDManager
%rename(__get__cidmanager_string) soda::CIDManager::operator[](const soda::CIDManager::IndexType);
%rename(__get__cidmanager_indextype) soda::CIDManager::operator[](const soda::CIDManager::String&);
//CCoverageMatrix
%rename(__eq__ccoveragematrix) soda::CCoverageMatrix::operator=(const soda::CCoverageMatrix::CCoverageMatrix&);


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