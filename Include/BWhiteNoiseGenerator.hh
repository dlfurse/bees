#ifndef BWHITENOISEGENERATOR_HH_
#define BWHITENOISEGENERATOR_HH_

#include <boost/random/mersenne_twister.hpp>
using boost::mt19937;

#include <boost/random/normal_distribution.hpp>
using boost::random::normal_distribution;

#include <boost/random/variate_generator.hpp>
using boost::random::variate_generator;

class BWhiteNoiseGenerator
{
    public:
        BWhiteNoiseGenerator();
        virtual ~BWhiteNoiseGenerator();

        void SetAmplitude( const double& aValue );

        void SetSize( const size_t& aSize );
        void SetPeriod( const double& aPeriod );
        void SetOutputOne( double* anArray );
        void SetOutputTwo( double* anArray );

        bool Initialize();
        bool Execute();

    private:
        double fAmplitude;

        size_t fSize;
        double fPeriod;
        double* fOutputOne;
        double* fOutputTwo;

        mt19937 fTwistor;
        normal_distribution< double >* fDistribution;
        variate_generator< mt19937&, normal_distribution< double > >* fGenerator;
};

#endif
