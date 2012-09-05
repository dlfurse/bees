#include "BFileReader.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>

const double BFileReader::sConversionToVolts = 1. / 512.;

BFileReader::BFileReader() :
    fFileName( "" ),
    fRecordSize( 0 ),
    fMonarch( NULL ),
    fMonarchHeader( NULL ),
    fMonarchRecordOne( NULL ),
    fRecordPointerOne( NULL ),
    fMonarchRecordTwo( NULL ),
    fRecordPointerTwo( NULL ),
    fOutputOne( NULL ),
    fOutputPointerOne( NULL ),
    fOutputTwo( NULL ),
    fOutputPointerTwo( NULL )
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

    if( fOutputOne != NULL )
    {
        delete fOutputOne;
        fOutputOne = NULL;
    }

    if( fOutputTwo != NULL )
    {
        delete fOutputTwo;
        fOutputTwo = NULL;
    }
}

void BFileReader::SetFileName( const string& aFileName )
{
    fFileName = aFileName;
    return;
}
double* BFileReader::GetOutputOne()
{
    return fOutputOne;
}
double* BFileReader::GetOutputTwo()
{
    return fOutputTwo;
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
    fOutputOne = new double[ fRecordSize ];
    fOutputTwo = new double[ fRecordSize ];

    fMonarchRecordOne = fMonarch->GetRecordOne();
    fMonarchRecordTwo = fMonarch->GetRecordTwo();

    return true;
}
bool BFileReader::Execute()
{
    if( fMonarch->ReadRecord() == false )
    {
        return false;
    }

    register const double tConversion = sConversionToVolts;
    register char* tRecordPointerOne = fMonarchRecordOne->fDataPtr;
    register char* tRecordPointerTwo = fMonarchRecordTwo->fDataPtr;
    register double* tOutputPointerOne = fOutputOne;
    register double* tOutputPointerTwo = fOutputTwo;
    for( size_t tIndex = 0; tIndex < fRecordSize; tIndex++ )
    {
        tOutputPointerOne[tIndex] = tRecordPointerOne[tIndex] * tConversion;
        tOutputPointerTwo[tIndex] = tRecordPointerTwo[tIndex] * tConversion;
    }

    return true;
}
