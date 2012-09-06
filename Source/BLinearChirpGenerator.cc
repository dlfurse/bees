#include "BLinearChirpGenerator.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>

const double BLinearChirpGenerator::sPi = 3.1415926535897932384626433832795;

BLinearChirpGenerator::BLinearChirpGenerator() :
    fAmplitude( 0. ),
    fStartFrequency( 0. ),
    fStopFrequency( 0. ),
    fDuration( 0. ),
    fDelay( 0. ),
    fSize( 0 ),
    fPeriod( 0. ),
    fOutputOne( NULL ),
    fOutputTwo( NULL )
{
}

BLinearChirpGenerator::~BLinearChirpGenerator()
{
}

void BLinearChirpGenerator::SetAmplitude( const double& aValue )
{
    fAmplitude = aValue;
    return;
}
void BLinearChirpGenerator::SetStartFrequency( const double& aValue )
{
    fStartFrequency = aValue;
    return;
}
void BLinearChirpGenerator::SetStopFrequency( const double& aValue )
{
    fStopFrequency = aValue;
    return;
}
void BLinearChirpGenerator::SetDuration( const double& aValue )
{
    fDuration = aValue;
    return;
}
void BLinearChirpGenerator::SetDelay( const double& aValue )
{
    fDelay = aValue;
    return;
}

void BLinearChirpGenerator::SetSize( const size_t& aSize )
{
    fSize = aSize;
    return;
}
void BLinearChirpGenerator::SetPeriod( const double& aPeriod )
{
    fPeriod = aPeriod;
    return;
}
void BLinearChirpGenerator::SetOutputOne( double* anArray )
{
    fOutputOne = anArray;
    return;
}
void BLinearChirpGenerator::SetOutputTwo( double* anArray )
{
    fOutputTwo = anArray;
    return;
}

bool BLinearChirpGenerator::Initialize()
{
    fStartBin = floor( fDelay / fPeriod );
    if( fStartBin < 0)
    {
        fStartBin = 0;
    }

    fStopBin = ceil( (fDelay + fDuration) / fPeriod );
    if( fStopBin > fSize - 1 )
    {
        fStopBin = fSize - 1;
    }

    return true;
}
bool BLinearChirpGenerator::Execute()
{
    register size_t tIndex;
    register double tTime = 0.;
    register double tPeriod = fPeriod;
    register double tStart = fStartFrequency;
    register double tSlope = (fStopFrequency - fStartFrequency) / fDuration;
    register double tValue;

    for( tIndex = fStartBin; tIndex <= fStopBin; tIndex++ )
    {
        tValue = fAmplitude * cos( 2.* sPi * (tStart + tSlope * tTime) * tTime );
        fOutputOne[tIndex] += tValue;
        fOutputTwo[tIndex] += tValue;
        tTime += tPeriod;
    }

    return true;
}
