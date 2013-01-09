#ifndef BCOMPONENT_HH_
#define BCOMPONENT_HH_

#include "BFields.hh"

#include <vector>
using std::vector;

#include <string>
using std::string;

class BComponent
{
    public:
        BComponent();
        virtual ~BComponent();

        //identification

        B_SET_GET( string, Name )

        //control

    public:
        void ConnectInput( BComponent* aFilter );
        void ConnectOutput( BComponent* aFilter );
        void SignalExecute();
        void SignalReset();

        virtual void Initialize() = 0;
        virtual void Execute() = 0;
        virtual void Reset() = 0;
        virtual void Finalize() = 0;

    protected:
        vector< BComponent* > fInputs;
        vector< BComponent* > fOutputs;
        size_t fExecuteCount;
        size_t fResetCount;
};

#endif
