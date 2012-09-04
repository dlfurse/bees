#include "BFileStreamer.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>

const double BFileStreamer::sConversionToVolts = 1. / 512.;

BFileStreamer::BFileStreamer() :
    fFileName( "" ),
    fSegmentSize( 0 ),
    fStepSize( 0 ),
    fOutputOne( NULL ),
    fOutputTwo( NULL ),
    fMonarch( NULL )
{
}
BFileStreamer::~BFileStreamer()
{
    if( fMonarch != NULL )
    {
        fMonarch->Close();
        delete fMonarch;
        fMonarch = NULL;
    }
}

void BFileStreamer::SetFileName( const string& aFileName )
{
    fFileName = aFileName;
    return;
}
void BFileStreamer::SetSegment( const size_t& aSegmentSize )
{
    fSegmentSize = aSegmentSize;
    return;
}
void BFileStreamer::SetStep( const size_t& aStepSize )
{
    fStepSize = aStepSize;
    return;
}
void BFileStreamer::SetOutputOne( double* aBuffer )
{
    fOutputOne = aBuffer;
    return;
}
void BFileStreamer::SetOutputTwo( double* aBuffer )
{
    fOutputTwo = aBuffer;
    return;
}

bool BFileStreamer::Initialize()
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
    fMonarchRecord = fMonarch->GetRecord();
    fRecordSize = fMonarchHeader->GetRecordSize();
    fRecordRead = fRecordSize;
    fRecordOne = new char[fRecordSize];
    fRecordTwo = new char[fRecordSize];

    return true;
}
bool BFileStreamer::Execute()
{
    if( fRecordRead == fRecordSize )
    {
        cout << "reading new record..." << endl;

        fRecordRead = 0;
        fRecordPointerOne = fRecordOne;
        fRecordPointerTwo = fRecordTwo;

        if( fMonarch->ReadRecord() == false )
        {
            return false;
        }
        memcpy( fRecordOne, fMonarchRecord->fDataPtr, fRecordSize );

        if( fMonarch->ReadRecord() == false )
        {
            return false;
        }
        memcpy( fRecordTwo, fMonarchRecord->fDataPtr, fRecordSize );

        size_t tIndex;

        fOutputPointerOne = fOutputOne;
        fOutputPointerTwo = fOutputTwo;
        for( tIndex = 0; tIndex < fSegmentSize; tIndex++ )
        {
            *fOutputPointerOne = sConversionToVolts * ( double )( *fRecordPointerOne );
            fOutputPointerOne++;
            fRecordPointerOne++;

            *fOutputPointerTwo = sConversionToVolts * ( double )( *fRecordPointerTwo );
            fOutputPointerTwo++;
            fRecordPointerTwo++;
        }
    }
    else
    {
        fRecordRead = fRecordRead + fStepSize;

        size_t tIndex;

        fOutputPointerOne = fOutputOne;
        fOutputPointerTwo = fOutputTwo;
        for( tIndex = 0; tIndex < fSegmentSize - fStepSize; tIndex++ )
        {
            *fOutputPointerOne = *(fOutputPointerOne + fStepSize);
            fOutputPointerOne++;

            *fOutputPointerTwo = *(fOutputPointerTwo + fStepSize);
            fOutputPointerTwo++;
        }
        for( tIndex = fSegmentSize - fStepSize; tIndex < fSegmentSize; tIndex++ )
        {
            *fOutputPointerOne = sConversionToVolts * ( double )( *fRecordPointerOne );
            fOutputPointerOne++;
            fRecordPointerOne++;

            *fOutputPointerTwo = sConversionToVolts * ( double )( *fRecordPointerTwo );
            fOutputPointerTwo++;
            fRecordPointerTwo++;
        }
    }

    return true;
}
