#include "BComponent.hh"

BComponent::BComponent() :
    fName( "(anonymous)" ),
    fInputs(),
    fOutputs(),
    fExecuteCount( 0 ),
    fResetCount( 0 )
{
}
BComponent::~BComponent()
{
}


void BComponent::ConnectInput( BComponent* aFilter )
{
    fInputs.push_back( aFilter );
    return;
}
void BComponent::ConnectOutput( BComponent* aFilter )
{
    fOutputs.push_back( aFilter );
    return;
}
void BComponent::SignalExecute()
{
    fExecuteCount++;
    if( fExecuteCount == fInputs.size() )
    {
        Execute();
        for( size_t tIndex = 0; tIndex < fOutputs.size(); tIndex++ )
        {
            fOutputs[tIndex]->SignalExecute();
        }
        fExecuteCount = 0;
    }
    return;
}
void BComponent::SignalReset()
{
    fResetCount++;
    if( fResetCount == fInputs.size() )
    {
        Reset();
        for( size_t tIndex = 0; tIndex < fOutputs.size(); tIndex++ )
        {
            fOutputs[tIndex]->SignalReset();
        }
        fResetCount = 0;
    }
    return;
}
