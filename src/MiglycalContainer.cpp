#include "Miglycal.h"
#include <eikclb.h>
#include <eiktxlbx.h>
#include <eiklbobs.h>
#include <f32file.h>

CMiglycalContainer* CMiglycalContainer::NewL(
    const TRect& aRect, CMiglycalAppUi& aAppUi)
    {
    CMiglycalContainer* self = new(ELeave) CMiglycalContainer(aAppUi);
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CMiglycalContainer::CMiglycalContainer(CMiglycalAppUi& aAppUi)
    : iAppUi(aAppUi), iListBox(NULL)
    {
    }

void CMiglycalContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    iListBox = new(ELeave) CAknSingleStyleListBox;
    iListBox->SetContainerWindowL(*this);
    iListBox->ConstructL(this, EAknListBoxSelectionList);
    iListBox->SetListBoxObserver(this);
    iListBox->CreateScrollBarFrameL(ETrue);
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);

    SetRect(aRect);
    ActivateL();
    }

CMiglycalContainer::~CMiglycalContainer()
    {
    delete iListBox;
    }

void CMiglycalContainer::SetTracksL(const CDesCArray& aTracks)
    {
    CDesCArray* items = new(ELeave) CDesCArrayFlat(8);
    CleanupStack::PushL(items);

    for (TInt i = 0; i < aTracks.Count(); ++i)
        {
        TParsePtrC parse(aTracks[i]);
        items->AppendL(parse.Name());
        }

    CTextListBoxModel* model = iListBox->Model();
    model->SetItemTextArray(items);
    model->SetOwnershipType(ELbmOwnsItemArray);
    iListBox->HandleItemAdditionL();
    CleanupStack::Pop(items);
    }

void CMiglycalContainer::HandleListBoxEventL(
    CEikListBox* aListBox, TListBoxEvent aEvent)
    {
    if (aListBox == iListBox &&
        (aEvent == EEventEnterKeyPressed || aEvent == EEventItemClicked))
        {
        const TInt index = iListBox->CurrentItemIndex();
        if (index >= 0)
            {
            iAppUi.PlayTrackL(index);
            }
        }
    }

TInt CMiglycalContainer::CountComponentControls() const
    {
    return 1;
    }

CCoeControl* CMiglycalContainer::ComponentControl(TInt aIndex) const
    {
    return (aIndex == 0) ? iListBox : NULL;
    }

void CMiglycalContainer::SizeChanged()
    {
    if (iListBox)
        {
        iListBox->SetRect(Rect());
        }
    }

TKeyResponse CMiglycalContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (iListBox)
        {
        return iListBox->OfferKeyEventL(aKeyEvent, aType);
        }
    return EKeyWasNotConsumed;
    }
