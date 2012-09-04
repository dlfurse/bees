#include "BFileReader.hh"

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
    size_t tAnalyticAssociateWindow = tPropertyTree.get< size_t >( "analytic_associate_window" );
    size_t tWignerVilleWindow = tPropertyTree.get< size_t >( "wigner_ville_window" );
    size_t tStep = tPropertyTree.get< size_t >( "step" );
    size_t tSegment = tAnalyticAssociateWindow + tWignerVilleWindow;

    cout << "  *input file: " << tInputName << endl;
    cout << "  *analytic associate window: " << tAnalyticAssociateWindow << endl;
    cout << "  *wigner-ville window: " << tWignerVilleWindow << endl;
    cout << "  *step: " << tStep << endl;
    cout << "  *segment: " << tSegment << endl;

    // create and initialize file streamer

    BFileReader tFileStreamer;
    tFileStreamer.SetFileName( tInputName );
    if( tFileStreamer.Initialize() == false )
    {
        cout << "[error] could not initialize file streamer" << endl;
    }

    // go go go

    unsigned int tCount = 0;
    while( true )
    {
        tCount++;
        if( tFileStreamer.Execute() == false )
        {
            cout << "completed step <" << tCount << ">" << endl;
            break;
        }
        if ( tCount % 100 == 0 )
        {
            cout << "completed step <" << tCount << ">" << endl;
        }
    }

    return 0;
}
