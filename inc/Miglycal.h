#ifndef MIGLYCAL_H
#define MIGLYCAL_H

#include <e32base.h>
#include <aknapp.h>
#include <akndoc.h>
#include <aknappui.h>
#include <coecntrl.h>
#include <aknlists.h>
#include <MdaAudioSamplePlayer.h>

_LIT(KMiglycalAppName, "Miglycal");
_LIT(KMiglycalMusicFolder, "E:\\Music\\");
_LIT(KMiglycalMp3Extension, ".mp3");
_LIT(KMiglycalAacExtension, ".aac");

const TUid KMiglycalAppUid = { 0xE7A51001 };

class CMiglycalContainer;

class CMiglycalApplication : public CAknApplication
    {
public:
    TUid AppDllUid() const;
private:
    CApaDocument* CreateDocumentL();
    };

class CMiglycalDocument : public CAknDocument
    {
public:
    static CMiglycalDocument* NewL(CEikApplication& aApp);
    ~CMiglycalDocument();
private:
    CMiglycalDocument(CEikApplication& aApp);
    void ConstructL();
    CEikAppUi* CreateAppUiL();
    };

class CMiglycalAppUi : public CAknAppUi, public MMdaAudioPlayerCallback
    {
public:
    void ConstructL();
    ~CMiglycalAppUi();

    void HandleCommandL(TInt aCommand);
    void PlayTrackL(TInt aIndex);

    void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
    void MapcPlayComplete(TInt aError);

private:
    void ScanMemoryCardL();
    void AddTracksFromDirectoryL(const TDesC& aDirectory, const TDesC& aExtension);
    void StopAndDestroyPlayer();

private:
    CMiglycalContainer* iContainer;
    CDesCArrayFlat* iTracks;
    CMdaAudioPlayerUtility* iPlayer;
    };

class CMiglycalContainer : public CCoeControl, public MEikListBoxObserver
    {
public:
    static CMiglycalContainer* NewL(const TRect& aRect, CMiglycalAppUi& aAppUi);
    ~CMiglycalContainer();

    void SetTracksL(const CDesCArray& aTracks);
    void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEvent);

private:
    CMiglycalContainer(CMiglycalAppUi& aAppUi);
    void ConstructL(const TRect& aRect);
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    void SizeChanged();
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

private:
    CMiglycalAppUi& iAppUi;
    CAknSingleStyleListBox* iListBox;
    };

#endif
