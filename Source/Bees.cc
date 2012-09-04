#include "BFileStreamer.hh"

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

#include <boost/property_tree/json_parser.hpp>
using namespace boost::property_tree::json_parser;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;

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
        cout << "  ./Bees <json configuration file name>" << endl;
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

    string tInputName = tPropertyTree.get< string >( "input_file" );
    size_t tSegmentSize = tPropertyTree.get< size_t >( "segment_size" );
    size_t tWindowSize = tPropertyTree.get< size_t >( "window_size" );
    size_t tStepSize = tPropertyTree.get< size_t >( "step_size" );

    cout << "  *input file: " << tInputName << endl;
    cout << "  *segment size: " << tSegmentSize << endl;
    cout << "  *window size: " << tWindowSize << endl;
    cout << "  *step size: " << tStepSize << endl;

    // create and initialize arrays

    double* tChannelOneVoltage = new double[ tSegmentSize ];
    double* tChannelTwoVoltage = new double[ tSegmentSize ];

    // create and initialize file streamer

    BFileStreamer tFileStreamer;
    tFileStreamer.SetFileName( tInputName );
    tFileStreamer.SetSegmentSize( tSegmentSize );
    tFileStreamer.SetStepSize( tStepSize );
    tFileStreamer.SetOutputOne( tChannelOneVoltage );
    tFileStreamer.SetOutputTwo( tChannelTwoVoltage );

    if( tFileStreamer.Initialize() == false )
    {
        cout << "[error] could not initialize file streamer" << endl;
    }

    // go go go

    unsigned int tStep;
    while( true )
    {
        if( tFileStreamer.Execute() == false )
        {
            cout << "completed step <" << tStep << ">" << endl;
            break;
        }
        if ( tStep % 100 == 0 )
        {
            cout << "completed step <" << tStep << ">" << endl;
        }
    }

    // clean up arrays

    delete[] tChannelOneVoltage;
    delete[] tChannelTwoVoltage;

    return 0;
}
