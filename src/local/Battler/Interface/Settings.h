#pragma once


using namespace Pi;


namespace Pi
{
    namespace WidgetType
    {
        const S Input = 'inpt';
    }
}


class InputWidget final : public RenderableWidget
{
private:

    enum
    {
        kInputBoxHilited = 1 << 0,
        kInputBoxConfigActive = 1 << 1
    };

    struct InputVertex
    {
        Point2D        position;
        ColorRGBA    color;
    };

    const ListWidget *controlList; //-V122

    Action *inputAction; //-V122
    InputControl *inputControl; //-V122

    ColorRGBA                    dynamicBackgroundColor;

    VertexBuffer                vertexBuffer;
    static SharedVertexBuffer    indexBuffer;

    PulsateMutator                pulsateMutator;
    TextWidget                    textWidget;

public:

    InputWidget(const ListWidget *list, Action *action);
    ~InputWidget();

    Action *GetInputAction() const
    {
        return (inputAction);
    }

    InputControl *GetInputControl() const
    {
        return (inputControl);
    }

    void SetDynamicWidgetColor(const ColorRGBA &color, WidgetColorType::S type = WidgetColorType::Default) override;

    void Preprocess() override;
    void Build() override;
    void HandleMouseEvent(const PanelMouseEventData *eventData) override;

    void SetInputControl(InputControl *control, float value = 0.0F);

    void BeginConfig();
    void EndConfig();
};


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

	PushButtonWidget *okayButton = nullptr;         ///< "OK" //-V122
	PushButtonWidget *cancelButton = nullptr;       ///< "Cancel" //-V122
	PushButtonWidget *applyButton = nullptr;        ///< "Apply" //-V122

	ListWidget      *resolutionList = nullptr;      ///< "Display resolution" //-V122
	CheckWidget     *fullscreenBox = nullptr;       ///< "Full screen" //-V122
	PopupMenuWidget *refreshSyncMenu = nullptr;     ///< "Sync to display" //-V122
	PopupMenuWidget *multisamplingMenu = nullptr;   ///< "Antialiasing" //-V122
	SliderWidget    *brightnessSlider = nullptr;    ///< "Brightness" ползунок //-V122
	TextWidget      *brightnessText = nullptr;      ///< "Brightness" текст //-V122

	PopupMenuWidget *lightDetailMenu = nullptr;     ///< "Dynamic light detail" //-V122
	PopupMenuWidget *textureDetailMenu = nullptr;   ///< "Texture detail" //-V122
	SliderWidget    *anisotropySlider = nullptr;    ///< "Anisotropic filtering level" ползунок //-V122
	TextWidget      *anisotropyText = nullptr;      ///< "Anisotropic filtering level" текст //-V122

	CheckWidget     *parallaxBox = nullptr;         ///< "Enable parallax mapping" //-V122
	CheckWidget     *horizonBox = nullptr;          ///< "Enable horizon mapping" //-V122
	CheckWidget     *ambientBumpBox = nullptr;      ///< "Enable ambient bump mapping" //-V122
	CheckWidget     *terrainBumpBox = nullptr;      ///< "Enable terrain bump mapping" //-V122
	CheckWidget     *terrainDetailBox = nullptr;    ///< "Use high-detail terrain textures" //-V122

	CheckWidget     *structureBox = nullptr;        ///< "Enable advanced effects" //-V122
	CheckWidget     *motionBlurBox = nullptr;       ///< "Enable motion blur" //-V122
	CheckWidget     *distortionBox = nullptr;       ///< "Enable distortion" //-V122
	CheckWidget     *glowBloomBox = nullptr;        ///< "Enable glow bloom" //-V122
	CheckWidget     *occlusionBox = nullptr;        ///< "Enable ambient occlusion (SSAO)" //-V122

	float           originalBrightness = 1.0F;

	GraphicsSettingsWindow();

	float GetBrightnessMultiplier() const;
	bool ChangeDisplayMode();

public:

	~GraphicsSettingsWindow();

	static void Open();

	void Preprocess() override;
	void HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) override;
};


class ControlSettingsWindow : public GameWindow, public Completable<ControlSettingsWindow>, public Singleton<ControlSettingsWindow>
{
private:

    InputWidget      *configWidget = nullptr; //-V122

    PushButtonWidget *okayButton = nullptr; //-V122
    PushButtonWidget *cancelButton = nullptr; //-V122

    ListWidget       *controlList = nullptr; //-V122
                     
    SliderWidget     *mouseSlider = nullptr; //-V122
    TextWidget       *mouseText = nullptr; //-V122
    CheckWidget      *invertMouseBox = nullptr; //-V122
    CheckWidget      *smoothMouseBox = nullptr; //-V122
                     
    SliderWidget     *controllerSlider = nullptr; //-V122
    TextWidget       *controllerText = nullptr; //-V122
    CheckWidget      *invertXAxisBox = nullptr; //-V122
    CheckWidget      *invertYAxisBox = nullptr; //-V122

    static void ConfigProc(InputControl *control, float value, void *cookie);

public:

    ControlSettingsWindow();
    ~ControlSettingsWindow();

    void SetConfigWidget(InputWidget *widget)
    {
        configWidget = widget;
    }

    static void Open();

    void Preprocess() override;

    bool HandleKeyboardEvent(const KeyboardEventData *eventData) override;
    void HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) override;

    void SelectControl(const InputWidget *inputWidget);
    void ClearDuplicateControls(const InputControl *control, const InputWidget *inputWidget);
};


class MenuWindow : public GameWindow, public Completable<MenuWindow>, public Singleton<MenuWindow>
{
public:
	static void Open();

	void Preprocess() override;
	void HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) override;
	bool HandleKeyboardEvent(const KeyboardEventData *eventData) override;
private:
    MenuWindow();

	PushButtonWidget *btnGraphicsSettings = nullptr; //-V122
	PushButtonWidget *btnControlsSettings = nullptr; //-V122
	PushButtonWidget *btnExit = nullptr; //-V122
	PushButtonWidget *btnCancel = nullptr; //-V122
};
