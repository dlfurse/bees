#ifndef BSIGNAL_HH_
#define BSIGNAL_HH_

#include "Monarch.hpp"

#include <string>
using std::string;

class BFileStreamer
{
    public:
        BFileStreamer();
        virtual ~BFileStreamer();

        void SetFileName( const string& aFileName );
        void SetSegment( const size_t& aSegmentSize );
        void SetStep( const size_t& aStepSize );
        void SetOutputOne( double* aBuffer );
        void SetOutputTwo( double* aBuffer );

        bool Initialize();
        bool Execute();

    private:
        string fFileName;
        size_t fSegmentSize;
        size_t fStepSize;
        double* fOutputOne;
        double* fOutputPointerOne;
        double* fOutputTwo;
        double* fOutputPointerTwo;

        const Monarch* fMonarch;
        const MonarchHeader* fMonarchHeader;
        const MonarchRecord* fMonarchRecord;
        size_t fRecordSize;
        size_t fRecordRead;
        char* fRecordOne;
        char* fRecordPointerOne;
        char* fRecordTwo;
        char* fRecordPointerTwo;

        static const double sConversionToVolts;
};

#endif
