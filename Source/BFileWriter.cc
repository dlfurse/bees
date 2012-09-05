#include "BFileWriter.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
#include <cmath>

const double BFileWriter::sConversionFromVolts = 512.;

BFileWriter::BFileWriter() :
    fFileName( "" ),
    fRecordSize( 0 ),
    fMonarch( NULL ),
    fMonarchHeader( NULL ),
    fMonarchRecordOne( NULL ),
    fRecordPointerOne( NULL ),
    fMonarchRecordTwo( NULL ),
    fRecordPointerTwo( NULL ),
    fInputOne( NULL ),
    fInputPointerOne( NULL ),
    fInputTwo( NULL ),
    fInputPointerTwo( NULL )
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

void BFileWriter::SetFileName( const string& aFileName )
{
    fFileName = aFileName;
    return;
}
void BFileWriter::SetRecordSize( const size_t& aSize )
{
    fRecordSize = aSize;
    return;
}
void BFileWriter::SetInputOne( double* anInput )
{
    fInputOne = anInput;
    return;
}
void BFileWriter::SetInputTwo( double* anInput )
{
    fInputTwo = anInput;
    return;
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
    fMonarchHeader->SetRecordSize( fRecordSize );
    fMonarchHeader->SetAcqMode( sTwoChannel );
    fMonarchHeader->SetAcqRate( 500.0 );
    fMonarchHeader->SetAcqTime( 0 );

    if( fMonarch->WriteHeader() == false )
    {
        cout << "[error] could not write header to egg file <" << fFileName << ">" << endl;
        return false;
    }

    fMonarchRecordOne = fMonarch->GetRecordOne();
    fMonarchRecordTwo = fMonarch->GetRecordTwo();

    return true;
}
bool BFileWriter::Execute()
{
    fRecordPointerOne = fMonarchRecordOne->fDataPtr;
    fRecordPointerTwo = fMonarchRecordTwo->fDataPtr;
    fInputPointerOne = fInputOne;
    fInputPointerTwo = fInputTwo;
    for( size_t tIndex = 0; tIndex < fRecordSize; tIndex++ )
    {
        fRecordPointerOne[tIndex] = (char) (round( sConversionFromVolts * fInputPointerOne[tIndex] ));
        fRecordPointerTwo[tIndex] = (char) (round( sConversionFromVolts * fInputPointerTwo[tIndex] ));
    }

    if( fMonarch->WriteRecord() == false )
    {
        return false;
    }

    return true;
}
