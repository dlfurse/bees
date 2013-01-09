#include "BFileReader.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>

BFileReader::BFileReader() :
    fFileName( "" ),
    fAcquisitionFrequency( 0. ),
    fMonarch( NULL ),
    fMonarchHeader( NULL ),
    fMonarchRecordOne( NULL ),
    fMonarchRecordTwo( NULL )
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
}

void BFileReader::Initialize()
{
    if( fOutputs[1]->GetSize() != fOutputs[2]->GetSize() )
    {
        throw
    }

    fMonarch = Monarch::OpenForReading( fFileName );
    if( fMonarch == NULL )
    {
        cout << "[error] could not open egg file <" << fFileName << ">" << endl;
        return;
    }

    fMonarchHeader = fMonarch->GetHeader();
    if( fMonarch->ReadHeader() == false )
    {
        cout << "[error] could not read header from egg file <" << fFileName << ">" << endl;
        return;
    }
    fSize = fMonarchHeader->GetRecordSize();
    fPeriod = 1. / fMonarchHeader->GetAcqRate();

    fMonarchRecordOne = fMonarch->GetRecordOne();
    fMonarchRecordTwo = fMonarch->GetRecordTwo();

    return;
}
void BFileReader::Execute()
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
