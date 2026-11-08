#include "Miglycal.h"
#include <eikstart.h>

LOCAL_C CApaApplication* NewApplication();

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

LOCAL_C CApaApplication* NewApplication()
    {
    return new CMiglycalApplication;
    }
