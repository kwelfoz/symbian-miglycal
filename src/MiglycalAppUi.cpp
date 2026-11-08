#include "Miglycal.h"
#include "Miglycal.hrh"
#include <f32file.h>

CMiglycalAppUi::CMiglycalAppUi()
    : iContainer(NULL), iTracks(NULL), iPlayer(NULL)
    {
    }

void CMiglycalAppUi::ConstructL()
    {
    BaseConstructL();

    iContainer = CMiglycalContainer::NewL(ClientRect(), *this);
    iContainer->SetMopParent(this);
    AddToStackL(iContainer);

    iTracks = new(ELeave) CDesCArrayFlat(16);
    ScanMemoryCardL();
    iContainer->SetTracksL(*iTracks);
    }

CMiglycalAppUi::~CMiglycalAppUi()
    {
    StopAndDestroyPlayer();
    if (iContainer)
        {
        RemoveFromStack(iContainer);
        }
    delete iContainer;
    delete iTracks;
    }

void CMiglycalAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EAknSoftkeyExit:
        case EEikCmdExit:
        case EMiglycalCmdExit:
            Exit();
            break;
        default:
            break;
        }
    }

void CMiglycalAppUi::ScanMemoryCardL()
    {
    iTracks->Reset();
    AddTracksFromDirectoryL(KMiglycalMusicFolder, KMiglycalMp3Extension);
    AddTracksFromDirectoryL(KMiglycalMusicFolder, KMiglycalAacExtension);
    }

void CMiglycalAppUi::AddTracksFromDirectoryL(
    const TDesC& aDirectory, const TDesC& aExtension)
    {
    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);

    TFileName pattern(aDirectory);
    pattern.Append(_L("*"));
    pattern.Append(aExtension);

    CDir* entries = NULL;
    const TInt error = fs.GetDir(pattern, KEntryAttNormal, ESortByName, entries);

    if (error == KErrNone && entries)
        {
        CleanupStack::PushL(entries);
        for (TInt i = 0; i < entries->Count(); ++i)
            {
            TFileName fullName(aDirectory);
            fullName.Append((*entries)[i].iName);
            iTracks->AppendL(fullName);
            }
        CleanupStack::PopAndDestroy(entries);
        }

    CleanupStack::PopAndDestroy(&fs);
    }

void CMiglycalAppUi::PlayTrackL(TInt aIndex)
    {
    if (aIndex < 0 || aIndex >= iTracks->Count())
        {
        return;
        }

    StopAndDestroyPlayer();
    iPlayer = CMdaAudioPlayerUtility::NewFilePlayerL((*iTracks)[aIndex], *this);
    }

void CMiglycalAppUi::StopAndDestroyPlayer()
    {
    if (iPlayer)
        {
        iPlayer->Stop();
        delete iPlayer;
        iPlayer = NULL;
        }
    }

void CMiglycalAppUi::MapcInitComplete(
    TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
    {
    if (aError == KErrNone && iPlayer)
        {
        iPlayer->Play();
        }
    }

void CMiglycalAppUi::MapcPlayComplete(TInt /*aError*/)
    {
    }
