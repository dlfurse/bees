#include "BData.hh"

#include <cstring>

BData::BData() :
    fSize( 0 ),
    fData( NULL )
{
}

BData::~BData()
{
}



void BData::Initialize()
{
    fData = new BComplex[ fSize ];
    return;
}
void BData::Execute()
{
    return;
}
void BData::Reset()
{
    memset( fData, 0, fSize * sizeof( BComplex ) );
    return;
}
void BData::Finalize()
{
    delete[] fData;
    return;
}

