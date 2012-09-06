#ifndef BTONEGENERATOR_HH_
#define BTONEGENERATOR_HH_

#include <cstddef>

class BToneGenerator
{
    public:
        BToneGenerator();
        virtual ~BToneGenerator();

        void SetAmplitude( const double& aValue );
        void SetFrequency( const double& aValue );

        void SetSize( const size_t& aSize );
        void SetPeriod( const double& aPeriod );
        void SetOutputOne( double* anArray );
        void SetOutputTwo( double* anArray );

        bool Initialize();
        bool Execute();

    private:
        double fAmplitude;
        double fFrequency;

        size_t fSize;
        double fPeriod;
        double* fOutputOne;
        double* fOutputTwo;

        static const double sPi;
};

#endif
