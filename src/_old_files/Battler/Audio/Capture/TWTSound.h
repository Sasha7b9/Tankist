#pragma once

#ifdef WIN32

#pragma warning(push, 0)
#include <xaudio2.h>
#pragma warning(pop)

#include "defines.h"
#include "TWTThreads.h"

typedef int16 Sample;

typedef Sample OutputSample;

enum
{
    kOutputBufferFrameCount = 1024
};

class SoundMgr
{
public:
    SoundMgr();
    bool Construct();

private:
    IXAudio2 *xaudioObject;
    IXAudio2MasteringVoice *masteringVoice;
    IXAudio2SourceVoice *sourceVoice;

    struct VoiceCallback : IXAudio2VoiceCallback
    {
        virtual ~VoiceCallback() {}

        SoundMgr *soundMgr;

        void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32);
        void STDMETHODCALLTYPE OnVoiceProcessingPassEnd(void);
        void STDMETHODCALLTYPE OnStreamEnd(void);
        void STDMETHODCALLTYPE OnBufferStart(void *context);
        void STDMETHODCALLTYPE OnBufferEnd(void *context);
        void STDMETHODCALLTYPE OnLoopEnd(void *context);
        void STDMETHODCALLTYPE OnVoiceError(void *context, HRESULT);
    };

    friend struct SoundMgr::VoiceCallback;

    VoiceCallback voiceCallback;

    XAUDIO2_BUFFER sourceBuffer[2];

    OutputSample *playBuffer[2];

    Signal* soundSignal;
};

#endif

