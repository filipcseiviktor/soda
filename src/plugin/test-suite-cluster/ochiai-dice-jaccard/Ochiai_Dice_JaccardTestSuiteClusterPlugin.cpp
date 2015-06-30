/*
 * Copyright (C): 2015 Department of Software Engineering, University of Szeged
 *
 * Authors: Bela Vancsics <vancsics@inf.u-szeged.hu>
 *
 * This file is part of SoDA.
 *
 *  SoDA is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SoDA is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SoDA.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "Ochiai_Dice_JaccardTestSuiteClusterPlugin.h"
#include "cluster.hpp"
#include "data/CBitMatrix.h"
#include "../hamming/HammingTestSuiteClusterPlugin.h"

namespace soda {

Ochiai_Dice_JaccardTestSuiteClusterPlugin::Ochiai_Dice_JaccardTestSuiteClusterPlugin()
{
}

Ochiai_Dice_JaccardTestSuiteClusterPlugin::~Ochiai_Dice_JaccardTestSuiteClusterPlugin()
{
}

std::string Ochiai_Dice_JaccardTestSuiteClusterPlugin::getName()
{
    return "ochiai-dice-jaccard";
}

std::string Ochiai_Dice_JaccardTestSuiteClusterPlugin::getDescription()
{
    return "Descr";
}

std::map<String, String> Ochiai_Dice_JaccardTestSuiteClusterPlugin::getRequiredParameters()
{
    return std::map<String, String>();
}

void Ochiai_Dice_JaccardTestSuiteClusterPlugin::init(rapidjson::Document &doc)
{
    algorithm_index = doc["alg.index"].GetInt();
    limit = doc["limit"].GetDouble();
    cluster_number = doc["cluster-number"].GetInt();
    _0cluster_limit = doc["0cluster(%)"].GetInt();
    testClusterDump = doc["test_clusters_dump"].GetString();
    codeElementsClusterDump = doc["codeelement_clusters_dump"].GetString();
}


void Ochiai_Dice_JaccardTestSuiteClusterPlugin::execute(CSelectionData &data, std::map<std::string, CClusterDefinition>& clusterList)
{

    if( algorithm_index == 0 ) std::cout<<std::endl<<"Running Ochiai..."<<std::endl;
    if( algorithm_index == 1 ) std::cout<<std::endl<<"Running Dice..."<<std::endl;
    if( algorithm_index == 2 ) std::cout<<std::endl<<"Running Jaccard..."<<std::endl;


    int numTC = int(data.getCoverage()->getNumOfTestcases());
    int numCE = int(data.getCoverage()->getNumOfCodeElements());
    std::cout<<"Matrix size: "<<numTC<<" X "<<numCE<<std::endl;


    // TestCase X TestCase matrix calc.
    std::cout<<"... on rows..."<<std::endl;
    clusters(data.getCoverage(), algorithm_index , false);


    // matrix transpose
    CIDManager idManagerTest, idManagerMethod;
    CBitMatrix* bitMatrix = new CBitMatrix();
    CCoverageMatrix* coverageTransposeMatrix = new CCoverageMatrix( &idManagerTest, &idManagerMethod, bitMatrix);
    matrixTranspose(data, coverageTransposeMatrix, bitMatrix, numTC, numCE);


    // CodeElements X CodeElements matrix calc.
    std::cout<<"... on cols..."<<std::endl;
    clusters(coverageTransposeMatrix, algorithm_index , true);



    // k-means alg. on (row) x (row) matrix
    std::cout<<std::endl<<"k-means running on row..."<<std::endl;
    kMeans(data.getCoverage(),false);


    // k-means alg. on (cols) x (cols) matrix
    std::cout<<"... and on cols"<<std::endl;
    kMeans(coverageTransposeMatrix,true);



    std::cout<<std::endl<<"Set clusterlist"<<std::endl;
    setClusterList( numTC, numCE, clusterList);

    // clusters dump
    clusterDump(data.getCoverage(), RowIndexVector, testClusterDump, false );
    clusterDump(data.getCoverage(), ColsIndexVector, codeElementsClusterDump, true);

}




float Ochiai_Dice_JaccardTestSuiteClusterPlugin::results_vs_limit( float results, float limit ){
    if ( limit != -1.0 )
        return results > limit ? 1.0 : 0.0;

    return results;
}


void Ochiai_Dice_JaccardTestSuiteClusterPlugin::kMeans(CCoverageMatrix *matrix, bool dimension){

    Clustering::ClusterId num_clusters = cluster_number;
    Clustering::PointId num_points;
    Clustering::Dimensions num_dimensions;

    if( !dimension ){
        num_points = floatRowVectors[0].size();
        num_dimensions = floatRowVectors[0].size();
    } else {
        num_points = floatColsVectors[0].size();
        num_dimensions = floatColsVectors[0].size();
    }

    int size = matrix->getBitMatrix().getNumOfCols();
    int position = 0;

    if( !dimension ){

        Clustering::PointsSpace ps(num_points, num_dimensions, floatRowVectors );
        Clustering::Clusters clusters(num_clusters, ps);

        clusters.k_means();

        RowIndexVector = clusters.points_to_clusters__;

        for (std::vector<ClusterId>::iterator it = RowIndexVector.begin() ; it != RowIndexVector.end(); ++it){
            if( matrix->getBitMatrix().getRow(IndexType(position)).count() > (size*_0cluster_limit/100) ){
                *it = ClusterId(0); // add to 0cluster
            } else {
                *it = (*it)+1;
            }
            position++;
        }

    } else {

        Clustering::PointsSpace ps(num_points, num_dimensions, floatColsVectors );
        Clustering::Clusters clusters(num_clusters, ps);

        clusters.k_means();

        ColsIndexVector = clusters.points_to_clusters__;

        for (std::vector<ClusterId>::iterator it = ColsIndexVector.begin() ; it != ColsIndexVector.end(); ++it){
            if( matrix->getBitMatrix().getRow(IndexType(position)).count() > (size*_0cluster_limit/100) ){
                *it = ClusterId(0); // add to 0cluster
            } else {
                *it = (*it)+1;
            }
            position++;
        }
    }


}



void Ochiai_Dice_JaccardTestSuiteClusterPlugin::setClusterList(int numTC, int numCE, std::map<std::string, CClusterDefinition>& clusterList){

    CClusterDefinition def;
    std::vector<ClusterId>::iterator maxIndex = std::max_element(RowIndexVector.begin(),RowIndexVector.end());

    for(int a = 0 ; a <= int(*maxIndex)+1 ; a++)
        clusterList[ boost::lexical_cast<std::string>(a) ] = CClusterDefinition();

    for(int i = 0 ; i < numTC ; i++)
        clusterList[ boost::lexical_cast<std::string>( int(RowIndexVector[i])) ].addTestCase(IndexType(i));

    for(int i = 0 ; i < numCE ; i++)
        clusterList[ boost::lexical_cast<std::string>( int(ColsIndexVector[i])) ].addCodeElement(IndexType(i));

}



void Ochiai_Dice_JaccardTestSuiteClusterPlugin::matrixTranspose(CSelectionData &data, CCoverageMatrix* coverageMatrix, CBitMatrix* bitMatrix, int numTC, int numCE){

    for(int i = 0 ; i < numCE ; i++)
        coverageMatrix->addTestcaseName( boost::lexical_cast<std::string>(i) );

    for(int i = 0 ; i < numTC ; i++)
        coverageMatrix->addCodeElementName( boost::lexical_cast<std::string>(i) );

    coverageMatrix->refitMatrixSize();

    for(int i = 0 ; i < numCE ; i++)
        for(int j = 0 ; j < numTC ; j++)
            bitMatrix->set(i,j, data.getCoverage()->getBitMatrix().get(IndexType(j),IndexType(i)));

}



void Ochiai_Dice_JaccardTestSuiteClusterPlugin::clusterDump(CCoverageMatrix* data, std::vector<ClusterId> labelVector, std::string outFile, bool dimension){

    std::vector<ClusterId>::iterator biggest = std::max_element( labelVector.begin(), labelVector.end() );
    int size = labelVector.size();
    std::ofstream outClusters;
    outClusters.open(outFile.c_str());

    for(int a = 0 ; a <= int(*biggest) ; a++){
        outClusters << a << ". cluster elements:\n";
        for ( int index = 0 ; index < size ; index++ ){
            if( !dimension ){
                if( labelVector[index] == a )
                    outClusters << "\t" << data->getTestcases().getValue(IndexType(index)) << "\n" ;
            } else {
                if( labelVector[index] == a )
                    outClusters << "\t" << data->getCodeElements().getValue(IndexType(index)) << "\n" ;
            }
        }
        outClusters<<"\n";
        for(int b = 0 ; b < 10 ; b++) outClusters<<"=======";
        outClusters<<"\n\n";
    }

}


void Ochiai_Dice_JaccardTestSuiteClusterPlugin::clusters(CCoverageMatrix* matrix, int algorithm_index, bool dimension){

    int numTC = int(matrix->getNumOfTestcases());
    int numCE = int(matrix->getNumOfCodeElements());

    if( !dimension ){
        floatRowVectors.resize(numTC, std::vector<float>(numTC));
    } else {
        floatColsVectors.resize(numTC, std::vector<float>(numTC));
    }

    for(int index_1 = 0 ; index_1 < numTC ; index_1++){
        int element_1 = int( matrix->getBitMatrix().getRow(IndexType(index_1)).count() );

        for(int index_2 = 0 ; index_2 < numTC ; index_2++ )
            set_results(matrix, index_1, index_2, element_1, numCE, algorithm_index, dimension);

    }

}

void Ochiai_Dice_JaccardTestSuiteClusterPlugin::set_results(CCoverageMatrix* matrix, int index_1, int index_2, int element_1, int numCE,  int algorithm_index, bool dimension){

    int element_2 = int(matrix->getBitMatrix().getRow(IndexType(index_2)).count());

    float* v_pointer;

    if( !dimension ){
        v_pointer = floatRowVectors[index_1].data();
    } else {
        v_pointer = floatColsVectors[index_1].data();
    }

    float results=0.0;

    if(algorithm_index==0){   // ochiai calc.
        if( element_1*element_2 != 0 )
            results = intersections(matrix, index_1, index_2, numCE) / (std::sqrt( element_1*element_2));

    } else if(algorithm_index==1){    // dice calc.
        if( element_1+element_2 != 0 )
            results = 2*intersections(matrix, index_1, index_2, numCE) / float(element_1+element_2);

    } else if(algorithm_index==2){    // jaccard calc.
        int unions = unionsCalc(matrix, index_1, index_2, numCE);
        if( unions != 0 )
            results = intersections(matrix, index_1, index_2, numCE) / float(unions);

    } else {
        std::cout<<"Error"<<std::endl;
        return;
    }

    *(v_pointer+index_2) = results_vs_limit(results,float(limit)) ;

}



int Ochiai_Dice_JaccardTestSuiteClusterPlugin::intersections(CCoverageMatrix* matrix, int index_1, int index_2, int size){
    int intersections = 0;
    for(int a = 0 ; a < size ; a++)
        intersections += int( matrix->getBitMatrix().get(IndexType(index_1),IndexType(a)) && matrix->getBitMatrix().get(IndexType(index_2),IndexType(a)) );

    return intersections;
}


int Ochiai_Dice_JaccardTestSuiteClusterPlugin::unionsCalc(CCoverageMatrix* matrix, int index_1, int index_2, int size){
    int unions = 0;
    for(int a = 0 ; a < size ; a++)
        unions += int( matrix->getBitMatrix().get(IndexType(index_1),IndexType(a)) || matrix->getBitMatrix().get(IndexType(index_2),IndexType(a)) );

    return unions;
}


extern "C" void registerPlugin(CKernel &kernel)
{
    kernel.getTestSuiteClusterPluginManager().addPlugin(new Ochiai_Dice_JaccardTestSuiteClusterPlugin());
}

} /* namespace soda */

