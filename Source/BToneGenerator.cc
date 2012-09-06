#include "BToneGenerator.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>

const double BToneGenerator::sPi = 3.1415926535897932384626433832795;

BToneGenerator::BToneGenerator() :
    fAmplitude( 0. ),
    fFrequency( 0. ),
    fSize( 0 ),
    fPeriod( 0. ),
    fOutputOne( NULL ),
    fOutputTwo( NULL )
{
}

BToneGenerator::~BToneGenerator()
{
}

void BToneGenerator::SetAmplitude( const double& aValue )
{
    fAmplitude = aValue;
    return;
}
void BToneGenerator::SetFrequency( const double& aValue )
{
    fFrequency = aValue;
    return;
}

void BToneGenerator::SetSize( const size_t& aSize )
{
    fSize = aSize;
    return;
}
void BToneGenerator::SetPeriod( const double& aPeriod )
{
    fPeriod = aPeriod;
    return;
}
void BToneGenerator::SetOutputOne( double* anArray )
{
    fOutputOne = anArray;
    return;
}
void BToneGenerator::SetOutputTwo( double* anArray )
{
    fOutputTwo = anArray;
    return;
}

bool BToneGenerator::Initialize()
{
    return true;
}
bool BToneGenerator::Execute()
{
    register size_t tIndex;
    register double tTime = 0.;
    register double tSize = fSize;
    register double tPeriod = fPeriod;
    register double tFrequency = fFrequency;
    register double tValue;

    for( tIndex = 0; tIndex <= tSize; tIndex++ )
    {
        tValue = fAmplitude * cos( 2.* sPi * tFrequency * tTime );
        fOutputOne[tIndex] += tValue;
        fOutputTwo[tIndex] += tValue;
        tTime += tPeriod;
    }

    return true;
}
