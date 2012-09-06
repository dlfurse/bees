#ifndef BLINEARCHIRPGENERATOR_HH_
#define BLINEARCHIRPGENERATOR_HH_

#include <cstddef>

class BLinearChirpGenerator
{
    public:
        BLinearChirpGenerator();
        virtual ~BLinearChirpGenerator();

        void SetAmplitude( const double& aValue );
        void SetStartFrequency( const double& aValue );
        void SetStopFrequency( const double& aValue );
        void SetDuration( const double& aValue );
        void SetDelay( const double& aDelay );

        void SetSize( const size_t& aSize );
        void SetPeriod( const double& aPeriod );
        void SetOutputOne( double* anArray );
        void SetOutputTwo( double* anArray );

        bool Initialize();
        bool Execute();

    private:
        double fAmplitude;
        double fStartFrequency;
        double fStopFrequency;
        double fDuration;
        double fDelay;

        size_t fSize;
        double fPeriod;
        double* fOutputOne;
        double* fOutputTwo;

        size_t fStartBin;
        size_t fStopBin;
        
        static const double sPi;
};

#endif
