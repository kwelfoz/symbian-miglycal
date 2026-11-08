#include "Miglycal.h"

CMiglycalDocument* CMiglycalDocument::NewL(CEikApplication& aApp)
    {
    CMiglycalDocument* self = new(ELeave) CMiglycalDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CMiglycalDocument::CMiglycalDocument(CEikApplication& aApp)
    : CAknDocument(aApp)
    {
    }

void CMiglycalDocument::ConstructL()
    {
    }

CMiglycalDocument::~CMiglycalDocument()
    {
    }

CEikAppUi* CMiglycalDocument::CreateAppUiL()
    {
    return new(ELeave) CMiglycalAppUi;
    }
