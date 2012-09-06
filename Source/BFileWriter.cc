#include "BFileWriter.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
#include <cmath>

BFileWriter::BFileWriter() :
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
BFileWriter::~BFileWriter()
{
    if( fMonarch != NULL )
    {
        fMonarch->Close();
        delete fMonarch;
        fMonarch = NULL;
    }

    if( fChannelOne != NULL )
    {
        delete[] fChannelOne;
        fChannelOne = NULL;
    }
    if( fChannelTwo != NULL )
    {
        delete[] fChannelTwo;
        fChannelTwo = NULL;
    }
}

void BFileWriter::SetFileName( const string& aFileName )
{
    fFileName = aFileName;
    return;
}
void BFileWriter::SetSize( const size_t& aSize )
{
    fSize = aSize;
    return;
}
void BFileWriter::SetPeriod( const double& aPeriod )
{
    fPeriod = aPeriod;
    return;
}

double* BFileWriter::ChannelOne()
{
    return fChannelOne;
}
double* BFileWriter::ChannelTwo()
{
    return fChannelTwo;
}

bool BFileWriter::Initialize()
{
    fMonarch = Monarch::OpenForWriting( fFileName );
    if( fMonarch == NULL )
    {
        cout << "[error] could not open egg file <" << fFileName << ">" << endl;
        return false;
    }

    fMonarchHeader = fMonarch->GetHeader();
    fMonarchHeader->SetAcqTime( 0 );
    fMonarchHeader->SetAcqMode( sTwoChannel );
    fMonarchHeader->SetRecordSize( fSize );
    fMonarchHeader->SetAcqRate( 1.e-6 / fPeriod );
    if( fMonarch->WriteHeader() == false )
    {
        cout << "[error] could not write header to egg file <" << fFileName << ">" << endl;
        return false;
    }

    fMonarchRecordOne = fMonarch->GetRecordOne();
    fMonarchRecordOne->fCId = 1;

    fMonarchRecordTwo = fMonarch->GetRecordTwo();
    fMonarchRecordTwo->fCId = 2;

    fChannelOne = new double[fSize];
    fChannelTwo = new double[fSize];

    memset( fChannelOne, 0, sizeof(double) * fSize );
    memset( fChannelTwo, 0, sizeof(double) * fSize );

    return true;
}
bool BFileWriter::Execute()
{
    register DataType* tRecordOne = fMonarchRecordOne->fDataPtr;
    register DataType* tRecordTwo = fMonarchRecordTwo->fDataPtr;
    register double* tChannelOne = fChannelOne;
    register double* tChannelTwo = fChannelTwo;

    register double tSlope = 510.;
    register double tOffset = .25;

    for( size_t tIndex = 0; tIndex < fSize; tIndex++ )
    {
        tRecordOne[tIndex] = (DataType) (round( tSlope * (tChannelOne[tIndex] + tOffset) ));
        tRecordTwo[tIndex] = (DataType) (round( tSlope * (tChannelTwo[tIndex] + tOffset) ));
    }

    if( fMonarch->WriteRecord() == false )
    {
        return false;
    }

    memset( fChannelOne, 0, sizeof(double) * fSize );
    memset( fChannelTwo, 0, sizeof(double) * fSize );

    return true;
}

