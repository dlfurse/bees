#include "BWhiteNoiseGenerator.hh"

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>

BWhiteNoiseGenerator::BWhiteNoiseGenerator() :
    fAmplitude( 0. ),
    fSize( 0 ),
    fPeriod( 0. ),
    fOutputOne( NULL ),
    fOutputTwo( NULL ),
    fTwistor(),
    fDistribution( NULL ),
    fGenerator( NULL )
{
}

BWhiteNoiseGenerator::~BWhiteNoiseGenerator()
{
    if( fGenerator != NULL )
    {
        delete fGenerator;
        fGenerator = NULL;
    }
    if( fDistribution != NULL )
    {
        delete fDistribution;
        fDistribution = NULL;
    }
}

void BWhiteNoiseGenerator::SetAmplitude( const double& aValue )
{
    fAmplitude = aValue;
    return;
}

void BWhiteNoiseGenerator::SetSize( const size_t& aSize )
{
    fSize = aSize;
    return;
}
void BWhiteNoiseGenerator::SetPeriod( const double& aPeriod )
{
    fPeriod = aPeriod;
    return;
}
void BWhiteNoiseGenerator::SetOutputOne( double* anArray )
{
    fOutputOne = anArray;
    return;
}
void BWhiteNoiseGenerator::SetOutputTwo( double* anArray )
{
    fOutputTwo = anArray;
    return;
}

bool BWhiteNoiseGenerator::Initialize()
{
    fDistribution = new normal_distribution< double >( 0., fAmplitude );
    fGenerator = new variate_generator< mt19937&, normal_distribution< double > >( fTwistor, *fDistribution );

    return true;
}
bool BWhiteNoiseGenerator::Execute()
{
    for( size_t tIndex = 0; tIndex < fSize; tIndex++ )
    {
        fOutputOne[tIndex] += fGenerator->operator ()();
        fOutputTwo[tIndex] += fGenerator->operator ()();
    }
    return true;
}
