#include "sound.h"

#define	SERVICE_UPDATE_PERIOD	(20)

#define	TEST_WAVE_FILE1		"stereo.wav"
#define	TEST_WAVE_FILE2		"stereo.wav"

SOUND::SOUND()
{
	pWaveLoader = NULL;


	ulDataSize = 0;
	ulFrequency = 0;
	ulFormat = 0;

	pData = NULL;	
}

SOUND::~SOUND()
{
	//
	alSourcei(uiSource, AL_BUFFER, 0);

	// Release temporary storage
	free(pData);
	pData = NULL;

	//
	// Close Wave Handle
	pWaveLoader->DeleteWaveFile(WaveID);

	// Clean up buffers and sources
	alDeleteSources( 1, &uiSource );
	alDeleteBuffers( NUMBUFFERS, uiBuffers );

	if (pWaveLoader)
		delete pWaveLoader;

	ALFWShutdownOpenAL();

	ALFWShutdown();	
}

bool SOUND::setFileName(char *a_FileName)
{
		// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(TEST_WAVE_FILE1), uiBuffer))
	{
		ALFWprintf("Failed to load %s\n", ALFWaddMediaPath(TEST_WAVE_FILE1));
	}

	// Generate a Source to playback the Buffer
    alGenSources( 1, &uiSource );

	// Attach Source to Buffer
	alSourcei( uiSource, AL_BUFFER, uiBuffer );

	return true;
}

bool SOUND::init()
{
		// Initialize Framework
	ALFWInit();

	ALFWprintf("OpenAL PlayStatic Test Application\n");

	if (!ALFWInitOpenAL())
	{
		ALFWprintf("Failed to initialize OpenAL\n");
		ALFWShutdown();
		return 0;
	}

	// Generate an AL Buffer
	alGenBuffers( 1, &uiBuffer );


	setFileName(TEST_WAVE_FILE1);
	//play();
	return 0;
}

bool SOUND::play()
{
	bool flg = true;

alSourcePlay( uiSource );


	return flg;
}

bool SOUND::isStopped() const
{
	ALint       iState;
	alGetSourcei( uiSource, AL_SOURCE_STATE, &iState);
	return !(iState==AL_PLAYING);
}