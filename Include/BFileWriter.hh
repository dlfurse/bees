#ifndef BFILEWRITER_HH_
#define BFILEWRITER_HH_

#include "Monarch.hpp"

#include <string>
using std::string;

class BFileWriter
{
    public:
        BFileWriter();
        virtual ~BFileWriter();

        void SetFileName( const string& aFileName );

        void SetSize( const size_t& aSize );
        void SetPeriod( const double& aPeriod );

        bool Execute();
        bool Initialize();

        double* ChannelOne();
        double* ChannelTwo();

    private:
        string fFileName;
        size_t fSize;
        double fPeriod;

        Monarch* fMonarch;
        MonarchHeader* fMonarchHeader;
        MonarchRecord* fMonarchRecordOne;
        MonarchRecord* fMonarchRecordTwo;

        double* fChannelOne;
        double* fChannelTwo;

        static const double sConversionFromVolts;
};

#endif
