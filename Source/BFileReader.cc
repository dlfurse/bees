#include "BFileReader.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>

const double BFileReader::sConversionToVolts = 1. / 512.;

BFileReader::BFileReader() :
    fFileName( "" ),
    fSegmentSize( 0 ),
    fStepSize( 0 ),
    fMonarch( NULL ),
    fMonarchHeader( NULL ),
    fRecordSize( 0 ),
    fMonarchRecordOne( NULL ),
    fRecordPointerOne( NULL ),
    fMonarchRecordTwo( NULL ),
    fRecordPointerTwo( NULL ),
    fOutputOne( NULL ),
    fOutputPointerOne( NULL ),
    fOutputTwo( NULL ),
    fOutputPointerTwo( NULL ),
    fRecordRead( 0 )
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

BFileReader* BFileReader::Construct( const ptree& /*aPropertyTree*/ )
{
    BFileReader* tFileReader = new BFileReader();
    return tFileReader;
}

void BFileReader::SetFileName( const string& aFileName )
{
    fFileName = aFileName;
    return;
}
void BFileReader::SetSegment( const size_t& aSegmentSize )
{
    fSegmentSize = aSegmentSize;
    return;
}
void BFileReader::SetStep( const size_t& aStepSize )
{
    fStepSize = aStepSize;
    return;
}
void BFileReader::SetOutputOne( double* aBuffer )
{
    fOutputOne = aBuffer;
    return;
}
void BFileReader::SetOutputTwo( double* aBuffer )
{
    fOutputTwo = aBuffer;
    return;
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
    fRecordSize = fMonarchHeader->GetRecordSize();
    fRecordRead = fRecordSize;

    fMonarchRecordOne = fMonarch->GetRecordOne();
    fMonarchRecordTwo = fMonarch->GetRecordTwo();

    return true;
}
bool BFileReader::Execute()
{
    size_t tIndex;

    if( fRecordRead == fRecordSize )
    {
        cout << "reading new record..." << endl;

        fRecordPointerOne = fMonarchRecordOne->fDataPtr;
        fRecordPointerTwo = fMonarchRecordTwo->fDataPtr;
        fOutputPointerOne = fOutputOne;
        fOutputPointerTwo = fOutputTwo;
        for( tIndex = 0; tIndex < fSegmentSize; tIndex++ )
        {
            *fOutputPointerOne = sConversionToVolts * (double) (*fRecordPointerOne);
            fOutputPointerOne++;
            fRecordPointerOne++;

            *fOutputPointerTwo = sConversionToVolts * (double) (*fRecordPointerTwo);
            fOutputPointerTwo++;
            fRecordPointerTwo++;
        }

        fRecordRead = fSegmentSize;
    }
    else
    {
        //shift the current segment by the step size

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
            *fOutputPointerOne = sConversionToVolts * (double) (*fRecordPointerOne);
            fOutputPointerOne++;
            fRecordPointerOne++;

            *fOutputPointerTwo = sConversionToVolts * (double) (*fRecordPointerTwo);
            fOutputPointerTwo++;
            fRecordPointerTwo++;
        }

        fRecordRead = fRecordRead + fStepSize;
    }

    return true;
}
