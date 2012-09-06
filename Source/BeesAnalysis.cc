#include "BFileReader.hh"
#include "BFourierTransform.hh"

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

#include <boost/property_tree/json_parser.hpp>
using namespace boost::property_tree::json_parser;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout;
using std::endl;

int main( const int tArgC, const char** tArgV )
{
    if( tArgC < 2 )
    {
        cout << "usage: " << endl;
        cout << "  ./BeesAnalysis <json configuration file name>" << endl;
        return -1;
    }

    // read json configuration file

    ifstream tPropertyFile;
    tPropertyFile.open( tArgV[1] );
    if( tPropertyFile.is_open() == false )
    {
        cout << "[error] could not open configuration file <" << tArgV[1] << ">" << endl;
        return -1;
    }

    ptree tPropertyTree;
    read_json( tPropertyFile, tPropertyTree );

    // initialize file reader

    string tFile = tPropertyTree.get< string >( "file" );

    cout << "  *file: " << tFile << endl;
    cout << endl;

    BFileReader tFileReader;
    tFileReader.SetFileName( tFile );
    if( tFileReader.Initialize() == false )
    {
        cout << "[error] could not initialize the file reader" << endl;
        return -1;
    }
    size_t tSize = tFileReader.GetSize();
    double tPeriod = tFileReader.GetPeriod();
    double* tChannelOne = tFileReader.ChannelOne();
    double* tChannelTwo = tFileReader.ChannelTwo();

    // create and initialize fourier transformer

    size_t tLength = tPropertyTree.get< size_t >( "fourier.length" );

    cout << "  *fourier length: " << tLength << endl;

    BFourierTransform tFourierTransform;
    tFourierTransform.SetLength( tLength );
    tFourierTransform.SetSize( tSize );
    tFourierTransform.SetPeriod( tPeriod );
    tFourierTransform.SetInputOne( tChannelOne );
    tFourierTransform.SetInputTwo( tChannelTwo );

    if( tFourierTransform.Initialize() == false )
    {
        cout << "[error] could not initialize fourier transformer" << endl;
    }

    // go go go

    unsigned int tCount = 0;
    while( true )
    {
        if( tFileReader.Execute() == false )
        {
            cout << "last step <" << tCount << ">" << endl;
            break;
        }
        tCount++;

        tFourierTransform.Execute();

        cout << "completed step <" << tCount << ">" << endl;
    }

    // flush

    ofstream tStream("./Bees.pwr");
    double* tOutputOne = tFourierTransform.OutputOne();
    double* tOutputTwo = tFourierTransform.OutputTwo();
    double tNormalization = 2.0 * ( 1. / (double)(tCount*floor((double)(tSize)/(double)(tLength))) ) * ( 1. / (double)( tLength * tLength ) ) * ( 1. / 50. );
    size_t tIndex;
    for( tIndex = 0; tIndex < tLength / 2; tIndex++ )
    {
        tStream << tIndex * (1./(tLength * tPeriod)) << " " << tNormalization * tOutputOne[tIndex] << "\n";
    }
//    tStream << "\n\n";
//    for( tIndex = 0; tIndex < tSize; tIndex++ )
//    {
//        tStream << tIndex * (1./(tSize * tPeriod)) << " " << tOutputTwo[tIndex] << "\n";
//    }
    tStream.close();

    return 0;
}
