#ifndef BFILEREADER_HH_
#define BFILEREADER_HH_

#include "Monarch.hpp"

#include <string>
using std::string;

class BFileReader
{
    public:
        BFileReader();
        virtual ~BFileReader();

        void SetFileName( const string& aFileName );

        bool Initialize();
        bool Execute();

        const size_t& GetSize();
        const double& GetPeriod();

        double* ChannelOne();
        double* ChannelTwo();

    private:
        string fFileName;
        size_t fSize;
        double fPeriod;

        const Monarch* fMonarch;
        const MonarchHeader* fMonarchHeader;
        const MonarchRecord* fMonarchRecordOne;
        const MonarchRecord* fMonarchRecordTwo;

        double* fChannelOne;
        double* fChannelTwo;
};

#endif
