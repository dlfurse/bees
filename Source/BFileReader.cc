#include "BFileReader.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>

BFileReader::BFileReader() :
    fFileName( "" ),
    fSize( 0 ),
    fPeriod( 0. ),
    fMonarch( NULL ),
    fMonarchHeader( NULL ),
    fMonarchRecordOne( NULL ),
    fMonarchRecordTwo( NULL ),
    fChannelOne( NULL ),
    fChannelTwo( NULL )
{
}
BFileReader::~BFileReader()
{
    if( fMonarch != NULL )
    {
        fMonarch->Close();
        delete fMonarch;
        fMonarch = NULL;
    }

    if( fChannelOne != NULL )
    {
        delete fChannelOne;
        fChannelOne = NULL;
    }

    if( fChannelTwo != NULL )
    {
        delete fChannelTwo;
        fChannelTwo = NULL;
    }
}

void BFileReader::SetFileName( const string& aFileName )
{
    fFileName = aFileName;
    return;
}
const size_t& BFileReader::GetSize()
{
    return fSize;
}
const double& BFileReader::GetPeriod()
{
    return fPeriod;
}

double* BFileReader::ChannelOne()
{
    return fChannelOne;
}
double* BFileReader::ChannelTwo()
{
    return fChannelTwo;
}

bool BFileReader::Initialize()
{
    fMonarch = Monarch::OpenForReading( fFileName );
    if( fMonarch == NULL )
    {
        cout << "[error] could not open egg file <" << fFileName << ">" << endl;
        return false;
    }

    fMonarchHeader = fMonarch->GetHeader();
    if( fMonarch->ReadHeader() == false )
    {
        cout << "[error] could not read header from egg file <" << fFileName << ">" << endl;
        return false;
    }
    fSize = fMonarchHeader->GetRecordSize();
    fPeriod = 1. / fMonarchHeader->GetAcqRate();

    fMonarchRecordOne = fMonarch->GetRecordOne();
    fMonarchRecordTwo = fMonarch->GetRecordTwo();

    fChannelOne = new double[fSize];
    fChannelTwo = new double[fSize];

    return true;
}
bool BFileReader::Execute()
{
    if( fMonarch->ReadRecord() == false )
    {
        return false;
    }

    register const DataType* tRecordOne = fMonarchRecordOne->fDataPtr;
    register const DataType* tRecordTwo = fMonarchRecordTwo->fDataPtr;
    register double* tChannelOne = fChannelOne;
    register double* tChannelTwo = fChannelTwo;

    register double tSlope = 1. / 510.;
    register double tOffset = -.25;

    for( size_t tIndex = 0; tIndex < fSize; tIndex++ )
    {
        tChannelOne[tIndex] = tOffset + (double)(tRecordOne[tIndex]) * tSlope;
        tChannelTwo[tIndex] = tOffset + (double)(tRecordTwo[tIndex]) * tSlope;
    }

    return true;
}
