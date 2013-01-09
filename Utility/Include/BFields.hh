#ifndef BFIELDS_HH_
#define BFIELDS_HH_

#define B_GET( xTYPE, xVARIABLE )\
    public:\
        const xTYPE& Get##xVARIABLE() const\
        {\
            return f##xVARIABLE;\
        }\
    protected:\
        xTYPE f##xVARIABLE;

#define B_SET( xTYPE, xVARIABLE )\
    public:\
        void Set##xVARIABLE( const xTYPE& aVariable )\
        {\
            f##xVARIABLE = aVariable;\
            return;\
        }\
    protected:\
        xTYPE f##xVARIABLE;

#define B_SET_GET( xTYPE, xVARIABLE )\
    public:\
        void Set##xVARIABLE( const xTYPE& aVariable )\
        {\
            f##xVARIABLE = aVariable;\
            return;\
        }\
        const xTYPE& Get##xVARIABLE() const\
        {\
            return f##xVARIABLE;\
        }\
    protected:\
        xTYPE f##xVARIABLE;

#endif
