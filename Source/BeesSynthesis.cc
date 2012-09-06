#include "BFileWriter.hh"
#include "BWhiteNoiseGenerator.hh"
#include "BLinearChirpGenerator.hh"
#include "BToneGenerator.hh"

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

#include <cmath>

int main( const int tArgC, const char** tArgV )
{
    if( tArgC < 2 )
    {
        cout << "usage: " << endl;
        cout << "  ./BeesSynthesis <json configuration file name>" << endl;
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

    // initialize file writer

    string tFile = tPropertyTree.get< string >( "file" );
    unsigned int tCount = tPropertyTree.get< unsigned int >( "count" );
    double tPeriod = 1. / (1.e6 * tPropertyTree.get< double >( "frequency_MHz" ));
    size_t tSize = 1048576 * tPropertyTree.get< size_t >( "size_MB" );

    cout << "  *file: " << tFile << endl;
    cout << "  *count: " << tCount << endl;
    cout << "  *period: " << tPeriod << endl;
    cout << "  *size: " << tSize << endl;
    cout << endl;

    BFileWriter tFileWriter;
    tFileWriter.SetFileName( tFile );
    tFileWriter.SetPeriod( tPeriod );
    tFileWriter.SetSize( tSize );
    if( tFileWriter.Initialize() == false )
    {
        cout << "[error] could not initialize the file writer" << endl;
        return -1;
    }
    register double* tChannelOne = tFileWriter.ChannelOne();
    register double* tChannelTwo = tFileWriter.ChannelTwo();

    // initialize noise generator

    double tNoiseAmplitude = sqrt( 50.0 * pow( 10., (tPropertyTree.get< double >( "noise.power_dBm" ) - 30.) / 10. ) );

    cout << "  *noise amplitude: " << tNoiseAmplitude << endl;
    cout << endl;

    BWhiteNoiseGenerator tWhiteNoiseGenerator;
    tWhiteNoiseGenerator.SetAmplitude( tNoiseAmplitude );
    tWhiteNoiseGenerator.SetSize( tSize );
    tWhiteNoiseGenerator.SetPeriod( tPeriod );
    tWhiteNoiseGenerator.SetOutputOne( tChannelOne );
    tWhiteNoiseGenerator.SetOutputTwo( tChannelTwo );
    if( tWhiteNoiseGenerator.Initialize() == false )
    {
        cout << "[error] could not initialize the noise generator" << endl;
        return -1;
    }

    // initialize chirp generator

    double tChirpAmplitude = sqrt( 2. * 50.0 * pow( 10., (tPropertyTree.get< double >( "chirp.power_dBm" ) - 30.) / 10. ) );
    double tChirpStart = 1.e6 * tPropertyTree.get< double >( "chirp.start_MHz" );
    double tChirpStop = 1.e6 * tPropertyTree.get< double >( "chirp.stop_MHz" );
    double tChirpDuration = 1.e-3 * tPropertyTree.get< double >( "chirp.duration_ms" );
    double tChirpDelay = 1.e-3 * tPropertyTree.get< double >( "chirp.delay_ms" );

    cout << "  *chirp amplitude: " << tChirpAmplitude << endl;
    cout << "  *chirp start: " << tChirpStart << endl;
    cout << "  *chirp stop: " << tChirpStop << endl;
    cout << "  *chirp duration: " << tChirpDuration << endl;
    cout << "  *chirp delay: " << tChirpDelay << endl;
    cout << endl;

    BLinearChirpGenerator tLinearChirpGenerator;
    tLinearChirpGenerator.SetAmplitude( tChirpAmplitude );
    tLinearChirpGenerator.SetStartFrequency( tChirpStart );
    tLinearChirpGenerator.SetStopFrequency( tChirpStop );
    tLinearChirpGenerator.SetDuration( tChirpDuration );
    tLinearChirpGenerator.SetDelay( tChirpDelay );
    tLinearChirpGenerator.SetSize( tSize );
    tLinearChirpGenerator.SetPeriod( tPeriod );
    tLinearChirpGenerator.SetOutputOne( tChannelOne );
    tLinearChirpGenerator.SetOutputTwo( tChannelTwo );
    if( tLinearChirpGenerator.Initialize() == false )
    {
        cout << "[error] could not initialize linear chirp generator" << endl;
        return -1;
    }

    // initialize chirp generator

    double tToneAmplitude = sqrt( 2. * 50.0 * pow( 10., (tPropertyTree.get< double >( "tone.power_dBm" ) - 30.) / 10. ) );
    double tToneFrequency = 1.e6 * tPropertyTree.get< double >( "tone.frequency_MHz" );

    cout << "  *tone amplitude: " << tToneAmplitude << endl;
    cout << "  *tone frequency: " << tToneFrequency << endl;
    cout << endl;

    BToneGenerator tToneGenerator;
    tToneGenerator.SetAmplitude( tToneAmplitude );
    tToneGenerator.SetFrequency( tToneFrequency );
    tToneGenerator.SetSize( tSize );
    tToneGenerator.SetPeriod( tPeriod );
    tToneGenerator.SetOutputOne( tChannelOne );
    tToneGenerator.SetOutputTwo( tChannelTwo );
    if( tToneGenerator.Initialize() == false )
    {
        cout << "[error] could not initialize tone generator" << endl;
        return -1;
    }

    // go go go

    cout << "synthesizing <" << tCount << "> records..." << endl;
    cout.flush();
    unsigned int tIndex = 0;
    while( tIndex < tCount )
    {
        tWhiteNoiseGenerator.Execute();
        tLinearChirpGenerator.Execute();
        tToneGenerator.Execute();
        tFileWriter.Execute();

        tIndex++;
    }
    cout << "...done with <" << tCount << "> records" << endl;

    return 0;
}
