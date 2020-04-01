//minden a cresultmatrix nevű modulba lesz wrappelve cresultmatrix.py lesz az eredmény.
%module cresultmatrix


%{
#define SWIG_FILE_WITH_INIT
#include "SoDALibDefs.h"
#include "IIDManager.h"
#include "IBitMatrix.h"
#include "IBitList.h"
#include "CSoDAio.h"
#include "CResultMatrix.h"
#include "CIDManager.h"
#include "CException.h"
#include "CBitWriter.h"
#include "CBitReader.h"
#include "CBitMatrix.h"
#include "CBitList.h"
#include "CBinaryIO.h"
%}
	//SoDALibDefs.h miatt
	%include "std_string.i"
	%include "std_vector.i"
	%include "std_map.i"
	%include "std_set.i"
	%include "std_list.i"
	
	
	//nem egészen igy kell csinálni. 31.3.13 nál a példa templateknél
	//előtte megkeresni az összes templatet, és definiálgatni őket structba
		//majd  ahogy a példába van 31.3.13 és onnan pedig 6.18 példa
	using namespace std;  
		
		31.12.3 Abstract base  classes öröklődések
		ekkor %include pyabc.i //python cuccaiból fog öröklődni ami itt van alatta
		
		%template(IntVector) vector<int>;
		%template(StringVector) vector<String>;
		%template(StringMap) map<IndexType, String>;
		%template(IdxStrMap) map<IndexType, IndexType>;
		%template(ClusterMap) map<string,CClusterDefinition>;
		
	//SoDALibDefs.h idáig


//végén levő conts részekkel nem kel lfoglalkozni
//todoban a plusz stb operátorok %rename része az jó

%rename(__add__) CBitMatrix::operatorPLUSZJEL
viszont!
friend Complex operatorPLUSZ(Complex &, double);
ekkor: %rename(add_complex_double)

bool operator[](IndexType index) const;
CBitMatrix& operator=(const CBitMatrix&);
BitList& operator[](IndexType row) const;
virtual String operator[](const IndexType) const;
irtual IndexType operator[](const String&) const;
 CResultsMatrix& operator=(const CResultsMatrix&);
save loads ????
virtual bool operator[](IndexType index) const = 0;
CSoDAio& operator=(const CSoDAio&);
virtual bool operator==(const IBitList& rhs) const
virtual bool operator!=(const IBitList& rhs) const
virtual IBitList& operator[](IndexType row) const = 0;
virtual bool operator==(const IBitMatrix& rhs) const
virtual bool operator!=(const IBitMatrix& rhs) const
 virtual String operator[](const IndexType) const = 0;
 virtual IndexType operator[](const String&) const = 0;


31.3.12 namespaces valamint előzőleg átirányitott oldalon a namespacek
ha több namespacunk van pl IO::SODA 
akkor %rename(IO_SODA) IO::SoDa
majd
namespace IO{ int spam() } és namespace SODA{( int spam() }
tehát mind2 helyen bekell hivnunk ugynazon metódusokat, igy mind2 tudni fogja azokat


ha olyanom lesz hogy 
void add(int x, int y, int pointerValami) vagy ha bárhol van benne pointer
akkor %include "typemaps.i"  és
void add(int, int, int pointerOUTPUT)
(ha void helyett int van akk is.  az outputot a resultból vette hogy az lesz. de lehet input is ha csak két paraméteres
de ha int helyett objektum van vagy bármi, akk EZ NEM JÓ MEGOLDÁS




Ignored résznél:
"If any base class is undefined, SWIG still generates correct type relationships)

-fvirtual "avoids the regenerationg of wrapper functions for virtual members that are already defined in a base class"
%include "SoDALibDefs.h"
%include "IIDManager.h"
%include "IBitMatrix.h"
%include "IBitList.h"
%include "CSoDAio.h"
%include "CResultMatrix.h"
%include "CIDManager.h"
%include "CException.h"
%include "CBitWriter.h"
%include "CBitReader.h"
%include "CBitMatrix.h"
%include "CBitList.h"
%include "CBinaryIO.h"
%include "sys/types.h"



