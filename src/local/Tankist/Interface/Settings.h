#pragma once


using namespace Pi;


class GameWindow : public Window, public ListElement<GameWindow>
{
protected:

	GameWindow(pchar panelName);

public:

	virtual ~GameWindow();
};


class GraphicsSettingsWindow : public GameWindow, public Completable<GraphicsSettingsWindow>, public Singleton<GraphicsSettingsWindow>
{
private:

	PushButtonWidget *okayButton = nullptr;        ///< "OK" //-V122
	PushButtonWidget *cancelButton = nullptr;      ///< "Cancel" //-V122
	PushButtonWidget *applyButton = nullptr;       ///< "Apply" //-V122

	ListWidget       *resolutionList = nullptr;    ///< "Display resolution" //-V122
	CheckWidget      *fullscreenBox = nullptr;     ///< "Full screen" //-V122
	PopupMenuWidget  *refreshSyncMenu = nullptr;   ///< "Sync to display" //-V122
	PopupMenuWidget  *multisamplingMenu = nullptr; ///< "Antialiasing" //-V122
	SliderWidget     *brightnessSlider = nullptr;  ///< "Brightness" ползунок //-V122
	TextWidget       *brightnessText = nullptr;    ///< "Brightness" текст //-V122

	PopupMenuWidget  *lightDetailMenu = nullptr;   ///< "Dynamic light detail" //-V122
	PopupMenuWidget  *textureDetailMenu = nullptr; ///< "Texture detail" //-V122
	SliderWidget     *anisotropySlider = nullptr;  ///< "Anisotropic filtering level" ползунок //-V122
	TextWidget       *anisotropyText = nullptr;    ///< "Anisotropic filtering level" текст //-V122

	CheckWidget      *parallaxBox = nullptr;       ///< "Enable parallax mapping" //-V122
	CheckWidget      *horizonBox = nullptr;        ///< "Enable horizon mapping" //-V122
	CheckWidget      *ambientBumpBox = nullptr;    ///< "Enable ambient bump mapping" //-V122
	CheckWidget      *terrainBumpBox = nullptr;    ///< "Enable terrain bump mapping" //-V122
	CheckWidget      *terrainDetailBox = nullptr;  ///< "Use high-detail terrain textures" //-V122
				     
	CheckWidget      *structureBox = nullptr;      ///< "Enable advanced effects" //-V122
	CheckWidget      *motionBlurBox = nullptr;     ///< "Enable motion blur" //-V122
	CheckWidget      *distortionBox = nullptr;     ///< "Enable distortion" //-V122
	CheckWidget      *glowBloomBox = nullptr;      ///< "Enable glow bloom" //-V122
	CheckWidget      *occlusionBox = nullptr;      ///< "Enable ambient occlusion (SSAO)" //-V122

	float            originalBrightness = 1.0F;

	GraphicsSettingsWindow();

	float GetBrightnessMultiplier() const;
	bool ChangeDisplayMode();

public:

	~GraphicsSettingsWindow();

	static void Open();

	void Preprocess() override;
	void HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) override;
};
