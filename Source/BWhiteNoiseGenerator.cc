#include "BWhiteNoiseGenerator.hh"

#include <cmath>

BWhiteNoiseGenerator::BWhiteNoiseGenerator() :
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

void BWhiteNoiseGenerator::SetPower( const double& aValue )
{
    fPower = aValue;
    return;
}

void BWhiteNoiseGenerator::SetSize( const size_t& aSize )
{
    fSize = aSize;
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
    fDistribution = new normal_distribution< double >( 0., sqrt( 50.0 * pow( 10., (fPower - 30.) / 10. ) ) );
    fGenerator = new variate_generator< mt19937&, normal_distribution< double > >( fTwistor, *fDistribution );

    return true;
}
bool BWhiteNoiseGenerator::Execute()
{
    for( size_t tIndex = 0; tIndex < fSize; tIndex++ )
    {
        fOutputOne[tIndex] = fGenerator->operator ()();
        fOutputTwo[tIndex] = fGenerator->operator ()();
    }
    return true;
}
