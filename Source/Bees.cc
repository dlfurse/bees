#include "BFileStreamer.hh"
#include "BAnalyticAssociate.hh"

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

    // create and initialize arrays

    double* tChannelOneVoltage = new double[ tSegment ];
    double* tChannelTwoVoltage = new double[ tSegment ];

    double* tChannelOneAnalyticAssociate = new double[ 2 * tWignerVilleWindow ];
    double* tChannelTwoAnalyticAssociate = new double[ 2 * tWignerVilleWindow ];

    // create and initialize file streamer

    BFileStreamer tFileStreamer;
    tFileStreamer.SetFileName( tInputName );
    tFileStreamer.SetSegment( tSegment );
    tFileStreamer.SetStep( tStep );
    tFileStreamer.SetOutputOne( tChannelOneVoltage );
    tFileStreamer.SetOutputTwo( tChannelTwoVoltage );

    if( tFileStreamer.Initialize() == false )
    {
        cout << "[error] could not initialize file streamer" << endl;
    }

    // create and initialize analytic associate for channel one

    BAnalyticAssociate tAnalyticAssociateOne;
    tAnalyticAssociateOne.SetSegment( tWignerVilleWindow );
    tAnalyticAssociateOne.SetWindow( tAnalyticAssociateWindow );
    tAnalyticAssociateOne.SetInput( tChannelOneVoltage );
    tAnalyticAssociateOne.SetOutput( tChannelOneAnalyticAssociate );

    if( tAnalyticAssociateOne.Initialize() == false )
    {
        cout << "[error] could not initialize analytic associate one" << endl;
    }

    // create and initialize analytic associate for channel two

    BAnalyticAssociate tAnalyticAssociateTwo;
    tAnalyticAssociateTwo.SetSegment( tWignerVilleWindow );
    tAnalyticAssociateTwo.SetWindow( tAnalyticAssociateWindow );
    tAnalyticAssociateTwo.SetInput( tChannelTwoVoltage );
    tAnalyticAssociateTwo.SetOutput( tChannelTwoAnalyticAssociate );

    if( tAnalyticAssociateTwo.Initialize() == false )
    {
        cout << "[error] could not initialize analytic associate two" << endl;
    }

    // go go go

    unsigned int tCount = 0;
    while( tCount != 1000 )
    {
        tCount++;
        if( tFileStreamer.Execute() == false )
        {
            cout << "completed step <" << tCount << ">" << endl;
            break;
        }
        tAnalyticAssociateOne.Execute();
        tAnalyticAssociateTwo.Execute();
        if ( tCount % 1000 == 0 )
        {
            cout << "completed step <" << tCount << ">" << endl;
        }
    }

    // clean up arrays

    delete[] tChannelOneVoltage;
    delete[] tChannelTwoVoltage;

    return 0;
}
