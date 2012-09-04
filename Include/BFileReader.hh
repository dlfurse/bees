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

        double* GetOutputOne();
        double* GetOutputTwo();

    private:
        string fFileName;
        size_t fRecordSize;

        const Monarch* fMonarch;
        const MonarchHeader* fMonarchHeader;

        const MonarchRecord* fMonarchRecordOne;
        const char* fRecordPointerOne;

        const MonarchRecord* fMonarchRecordTwo;
        const char* fRecordPointerTwo;

        double* fOutputOne;
        double* fOutputPointerOne;

        double* fOutputTwo;
        double* fOutputPointerTwo;

        size_t fRecordRead;

        static const double sConversionToVolts;
};

#endif
