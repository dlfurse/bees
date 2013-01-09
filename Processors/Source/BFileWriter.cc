#include "BFileWriter.hh"
#include "BException.hh"

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
    fMonarchRecordInterleaved( NULL )
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
}

void BFileWriter::Initialize()
{
    fMonarch = Monarch::OpenForWriting( fFileName );
    if( fMonarch == NULL )
    {
        throw BException() << "[error] could not open egg file <" << fFileName << ">";
        return;
    }

    fMonarchHeader = fMonarch->GetHeader();
    fMonarchHeader->SetAcqTime( 0 );
    fMonarchHeader->SetAcqMode( sTwoChannel );
    fMonarchHeader->SetRecordSize( 2 * fSize );
    fMonarchHeader->SetAcqRate( 1.e-6 / fPeriod );
    if( fMonarch->WriteHeader() == false )
    {
        throw BException() << "[error] could not write header to egg file <" << fFileName << ">";
        return;
    }

    fMonarchRecordInterleaved = fMonarch->GetRecordInterleaved();

    return;
}
void BFileWriter::Execute()
{
    register DataType* tRecordInterleaved = fMonarchRecordInterleaved->fDataPtr;

    register double tSlope = 510.;
    register double tOffset = .25;

    for( size_t tIndex = 0; tIndex < fSize; tIndex++ )
    {
        (*tRecordInterleaved) = (DataType) (round( tSlope * ((*tChannelOne) + tOffset) ));
        tChannelOne++;
        tRecordInterleaved++;

        (*tRecordInterleaved) = (DataType) (round( tSlope * ((*tChannelTwo) + tOffset) ));
        tChannelTwo++;
        tRecordInterleaved++;
    }

    if( fMonarch->WriteRecord() == false )
    {
        return false;
    }

    memset( fChannelOne, 0, sizeof(double) * fSize );
    memset( fChannelTwo, 0, sizeof(double) * fSize );

    return true;
}

