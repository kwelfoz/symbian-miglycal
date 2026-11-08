#include "Miglycal.h"

TUid CMiglycalApplication::AppDllUid() const
    {
    return KMiglycalAppUid;
    }

CApaDocument* CMiglycalApplication::CreateDocumentL()
    {
    return CMiglycalDocument::NewL(*this);
    }
