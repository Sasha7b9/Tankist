#include "stdafx.h"


GraphicsSettingsWindow *TheGraphicsSettingsWindow = nullptr;
ControlSettingsWindow *TheControlSettingsWindow = nullptr;


SharedVertexBuffer InputWidget::indexBuffer(VertexBuffer::Flag::Index | VertexBuffer::Flag::Static);


InputWidget::InputWidget(const ListWidget *list, Action *action) :
    RenderableWidget(WidgetType::Input, RenderType::IndexedTriangles, Vector2D(136.0F, 16.0F)),
    vertexBuffer(VertexBuffer::Flag::Attribute | VertexBuffer::Flag::Dynamic),
    pulsateMutator(ColorRGBA(0.5F, 0.5F, 0.5F, 1.0F), kPulsateWaveSine, 0.001F),
    textWidget(Vector2D(136.0F, 14.0F), nullptr, "font/Gui")
{
    controlList = list;

    inputAction = action;
    inputControl = TheInputMgr->GetActionControl(action);
    if(inputControl)
    {
        textWidget.SetText(inputControl->GetControlName());
    }

    textWidget.SetTextAlignment(TextAlignment::Center);
    textWidget.SetWidgetPosition(Point3D(0.0F, 2.0F, 0.0F));
    textWidget.Disable();
    AppendSubnode(&textWidget);

    SetWidgetUsage(WidgetUsage::TrackInhibit);
    SetDefaultColorType(WidgetColorType::Background);
    RenderableWidget::SetWidgetColor(ColorRGBA(0.875F, 0.875F, 0.875F, 1.0F));

    pulsateMutator.SetMutatorState(kMutatorDisabled);
    AddMutator(&pulsateMutator);

    if(indexBuffer.Retain() == 1)
    {
        static const Triangle inputTriangle[10] =
        {
            {{ 0,  1,  2}}, {{ 0,  2,  3}}, {{ 8,  9,  4}}, {{ 4,  9,  5}},
            {{ 9, 10,  5}}, {{ 5, 10,  6}}, {{10, 11,  6}}, {{ 6, 11,  7}},
            {{11,  8,  7}}, {{ 7,  8,  4}}
        };

        indexBuffer.Establish(sizeof(Triangle) * 10, inputTriangle);
    }
}

InputWidget::~InputWidget()
{
    indexBuffer.Release();
}

void InputWidget::SetDynamicWidgetColor(const ColorRGBA &color, WidgetColorType::S type)
{
    if((type == WidgetColorType::Default) || (type == WidgetColorType::Background))
    {
        dynamicBackgroundColor = color;
        SetBuildFlag();
    }
}

void InputWidget::Preprocess()
{
    RenderableWidget::Preprocess();

    SetWidgetState(GetWidgetState() & ~WidgetState::Disabled);

    dynamicBackgroundColor = GetWidgetColor();

    SetVertexCount(12);
    SetVertexBuffer(VertexBufferIndex::AttributeArray, &vertexBuffer, sizeof(InputVertex));
    SetVertexAttributeArray(ArrayIndex::Position, 0, 2);
    SetVertexAttributeArray(ArrayIndex::Color, sizeof(Point2D), 4); //-V112
    vertexBuffer.Establish(sizeof(InputVertex) * 12);

    SetPrimitiveCount(10);
    SetVertexBuffer(VertexBufferIndex::IndexArray, &indexBuffer);
}

void InputWidget::Build()
{
    volatile InputVertex *restrict vertex = vertexBuffer.BeginUpdate<InputVertex>(); //-V2571

    float w = GetWidgetSize().x;
    float h = GetWidgetSize().y;

    vertex[0].position.Set(0.0F, 0.0F); //-V2563
    vertex[0].color = dynamicBackgroundColor; //-V2563
    vertex[1].position.Set(0.0F, h); //-V2563
    vertex[1].color = dynamicBackgroundColor; //-V2563
    vertex[2].position.Set(w, h); //-V2563
    vertex[2].color = dynamicBackgroundColor; //-V2563
    vertex[3].position.Set(w, 0.0F); //-V2563
    vertex[3].color = dynamicBackgroundColor; //-V2563

    vertex[4].position.Set(0.0F, 0.0F); //-V2563
    vertex[4].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563
    vertex[5].position.Set(0.0F, h); //-V2563
    vertex[5].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563
    vertex[6].position.Set(w, h); //-V2563
    vertex[6].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563
    vertex[7].position.Set(w, 0.0F); //-V2563
    vertex[7].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563

    vertex[8].position.Set(-1.0F, -1.0F); //-V2563
    vertex[8].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563
    vertex[9].position.Set(-1.0F, h + 1.0F); //-V2563
    vertex[9].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563
    vertex[10].position.Set(w + 1.0F, h + 1.0F); //-V2563
    vertex[10].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563
    vertex[11].position.Set(w + 1.0F, -1.0F); //-V2563
    vertex[11].color.Set(0.25F, 0.25F, 0.25F, 1.0F); //-V2563

    vertexBuffer.EndUpdate();
}

void InputWidget::HandleMouseEvent(const PanelMouseEventData *eventData)
{
    if(eventData->eventType == EventMouse::Down)
    {
        TheControlSettingsWindow->SelectControl(this);
        BeginConfig();
    }
}

void InputWidget::SetInputControl(InputControl *control, float)
{
    if(control)
    {
        EndConfig();

        Action *action = control->GetControlAction();
        if((action == nullptr) || ((action->GetActionFlags() & kActionImmutable) != 0))
        {
            inputControl = control;
            textWidget.SetText(control->GetControlName());

            TheControlSettingsWindow->ClearDuplicateControls(control, this);
        }
    }
    else
    {
        inputControl = nullptr;
        textWidget.SetText(nullptr);
    }
}

void InputWidget::BeginConfig()
{
    TheControlSettingsWindow->SetConfigWidget(this);
    TheInputMgr->SetInputMode(InputMode::Configuration);
    TheInterfaceMgr->HideCursor();

    pulsateMutator.SetMutatorState(0);
}

void InputWidget::EndConfig()
{
    pulsateMutator.Reset();
    pulsateMutator.SetMutatorState(kMutatorDisabled);
    SetDynamicWidgetColor(GetWidgetColor());

    TheInputMgr->SetInputMode(InputMode::Inactive);
    TheInterfaceMgr->ShowCursor();
}


GameWindow::GameWindow(pchar panelName) : Window(panelName)
{
}


GameWindow::~GameWindow()
{
}


GraphicsSettingsWindow::GraphicsSettingsWindow() :
	GameWindow("game/Graphics"),
	Singleton<GraphicsSettingsWindow>(TheGraphicsSettingsWindow)
{
}


GraphicsSettingsWindow::~GraphicsSettingsWindow()
{
}


void GraphicsSettingsWindow::Open()
{
	if (TheGraphicsSettingsWindow)
	{
		TheInterfaceMgr->SetActiveWindow(TheGraphicsSettingsWindow);
	}
	else
	{
		TheInterfaceMgr->AddWidget(new GraphicsSettingsWindow); //-V2511
	}
}


void GraphicsSettingsWindow::Preprocess()
{
	GameWindow::Preprocess();

	okayButton = static_cast<PushButtonWidget *>(FindWidget("OK"));
	cancelButton = static_cast<PushButtonWidget *>(FindWidget("Cancel"));
	applyButton = static_cast<PushButtonWidget *>(FindWidget("Apply"));

	resolutionList = static_cast<ListWidget *>(FindWidget("Resolution"));
	fullscreenBox = static_cast<CheckWidget *>(FindWidget("Full"));
	refreshSyncMenu = static_cast<PopupMenuWidget *>(FindWidget("Sync"));
	multisamplingMenu = static_cast<PopupMenuWidget *>(FindWidget("AA"));
	brightnessSlider = static_cast<SliderWidget *>(FindWidget("Bright"));
	brightnessText = static_cast<TextWidget *>(FindWidget("BrightText"));

	lightDetailMenu = static_cast<PopupMenuWidget *>(FindWidget("LightLOD"));
	textureDetailMenu = static_cast<PopupMenuWidget *>(FindWidget("TextureLOD"));
	anisotropySlider = static_cast<SliderWidget *>(FindWidget("Aniso"));
	anisotropyText = static_cast<TextWidget *>(FindWidget("AnisoText"));

	parallaxBox = static_cast<CheckWidget *>(FindWidget("Parallax"));
	horizonBox = static_cast<CheckWidget *>(FindWidget("Horizon"));
	ambientBumpBox = static_cast<CheckWidget *>(FindWidget("AmbientBump"));
	terrainBumpBox = static_cast<CheckWidget *>(FindWidget("TerrainBump"));
	terrainDetailBox = static_cast<CheckWidget *>(FindWidget("TerrainLOD"));

	structureBox = static_cast<CheckWidget *>(FindWidget("Structure"));
	motionBlurBox = static_cast<CheckWidget *>(FindWidget("Motion"));
	distortionBox = static_cast<CheckWidget *>(FindWidget("Distortion"));
	glowBloomBox = static_cast<CheckWidget *>(FindWidget("Glow"));
	occlusionBox = static_cast<CheckWidget *>(FindWidget("SSAO"));

	int index = 0;
	int displayWidth = TheDisplayMgr->GetDisplayWidth();
	int displayHeight = TheDisplayMgr->GetDisplayHeight();

	const DisplayMode *mode = TheDisplayMgr->GetCurrentDisplay()->GetFirstDisplayMode();
	while (mode)
	{
		int w = mode->GetDisplayWidth();
		int h = mode->GetDisplayHeight();

		String<31> string(w);
		string += " \xC3\x97 ";        // U+00D7
		string += h;
		resolutionList->AppendListItem(string);

		if ((w == displayWidth) && (h == displayHeight))
		{
			resolutionList->SelectListItem(index);
		}

		index++;
		mode = mode->Next();
	}

	uint flags = TheDisplayMgr->GetDisplayFlags();
	if (flags & kDisplayFullscreen)
	{
		fullscreenBox->SetValue(1);
	}

	if (flags & kDisplayRefreshSync)
	{
		if (flags & kDisplaySyncTear)
		{
			refreshSyncMenu->SetSelection(2);
		}
		else
		{
			refreshSyncMenu->SetSelection(1);
		}
	}
	else
	{
		refreshSyncMenu->SetSelection(0);
	}

	int displaySamples = TheDisplayMgr->GetDisplaySamples();
	if (displaySamples == 2)
	{
		multisamplingMenu->SetSelection(1);
	}
	else if (displaySamples == 4) //-V112
	{
		multisamplingMenu->SetSelection(2);
	}
	else if (displaySamples == 8)
	{
		multisamplingMenu->SetSelection(3);
	}
	else
	{
		multisamplingMenu->SetSelection(0);
	}

	float brightness = TheGraphicsMgr->GetBrightnessMultiplier();
	originalBrightness = brightness;

	int value = (int)((brightness - 1.0F) * 50.0F); //-V2533
	brightnessSlider->SetValue(value);
	brightnessText->SetText(String<7>(value));

	lightDetailMenu->SetSelection(TheWorldMgr->GetLightDetailLevel());
	textureDetailMenu->SetSelection(2 - TheGraphicsMgr->GetTextureDetailLevel());

	int anisotropy = TheGraphicsMgr->GetTextureFilterAnisotropy();
	anisotropySlider->SetValue(anisotropy - 1);
	anisotropyText->SetText(String<7>(anisotropy));

	flags = TheGraphicsMgr->GetRenderOptionFlags();

	if (flags & kRenderOptionParallaxMapping)
	{
		parallaxBox->SetValue(1);
	}

	if (flags & kRenderOptionHorizonMapping)
	{
		horizonBox->SetValue(1);
	}

	if (flags & kRenderOptionAmbientBumps)
	{
		ambientBumpBox->SetValue(1);
	}

	if (flags & kRenderOptionTerrainBumps)
	{
		terrainBumpBox->SetValue(1);
	}

	if (flags & kRenderOptionStructureEffects)
	{
		structureBox->SetValue(1);
	}

	if (flags & kRenderOptionMotionBlur)
	{
		motionBlurBox->SetValue(1);
	}

	if (flags & kRenderOptionDistortion)
	{
		distortionBox->SetValue(1);
	}

	if (flags & kRenderOptionGlowBloom)
	{
		glowBloomBox->SetValue(1);
	}

	if (flags & kRenderOptionAmbientOcclusion)
	{
		occlusionBox->SetValue(1);
	}

	if (TheGraphicsMgr->GetPaletteDetailLevel() == 0)
	{
		terrainDetailBox->SetValue(1);
	}

	SetFocusWidget(resolutionList);
}


void GraphicsSettingsWindow::HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) //-V2558
{
	EventWidget::S eventType = eventData->eventType;

	if (eventType == EventWidget::Activate)
	{
		if (widget == okayButton)
		{
			ChangeDisplayMode();
			ConfigDataDescription::WriteEngineConfig(TheEngine->GetConfigFileName());

			CallCompletionProc();
			Close();
		}
		else if (widget == applyButton)
		{
			ChangeDisplayMode();
			ConfigDataDescription::WriteEngineConfig(TheEngine->GetConfigFileName());
		}
		else if (widget == cancelButton)
		{
			TheGraphicsMgr->SetBrightnessMultiplier(originalBrightness);
			CallCompletionProc();
			Close();
		}
		else if (widget == resolutionList) //-V2516
		{
			ChangeDisplayMode();
			ConfigDataDescription::WriteEngineConfig(TheEngine->GetConfigFileName());
		}
	}
	else if (eventType == EventWidget::Change) //-V2516
	{
		if (widget == brightnessSlider)
		{
			brightnessText->SetText(String<7>(brightnessSlider->GetValue()));
			TheGraphicsMgr->SetBrightnessMultiplier(GetBrightnessMultiplier());
		}
		else if (widget == anisotropySlider) //-V2516
		{
			anisotropyText->SetText(String<7>(anisotropySlider->GetValue() + 1));
		}
	}
}


inline float GraphicsSettingsWindow::GetBrightnessMultiplier() const
{
	return ((float)brightnessSlider->GetValue() * 0.02F + 1.0F); //-V2533
}


bool GraphicsSettingsWindow::ChangeDisplayMode() //-V2506
{
	uint renderOptionFlags = TheGraphicsMgr->GetRenderOptionFlags();

	TheEngine->GetVariable("lightDetailLevel")->SetIntegerValue(lightDetailMenu->GetSelection()); //-V522
	TheEngine->GetVariable("textureDetailLevel")->SetIntegerValue(2 - textureDetailMenu->GetSelection()); //-V522
	TheEngine->GetVariable("paletteDetailLevel")->SetIntegerValue(1 - terrainDetailBox->GetValue()); //-V522
	TheEngine->GetVariable("textureAnisotropy")->SetIntegerValue(anisotropySlider->GetValue() + 1); //-V522
	TheEngine->GetVariable("renderParallaxMapping")->SetIntegerValue(parallaxBox->GetValue()); //-V522
	TheEngine->GetVariable("renderHorizonMapping")->SetIntegerValue(horizonBox->GetValue()); //-V522
	TheEngine->GetVariable("renderAmbientBumps")->SetIntegerValue(ambientBumpBox->GetValue()); //-V522
	TheEngine->GetVariable("renderTerrainBumps")->SetIntegerValue(terrainBumpBox->GetValue()); //-V522
	TheEngine->GetVariable("renderStructureEffects")->SetIntegerValue(structureBox->GetValue()); //-V522
	TheEngine->GetVariable("renderAmbientOcclusion")->SetIntegerValue(occlusionBox->GetValue()); //-V522
	TheEngine->GetVariable("postBrightness")->SetFloatValue(GetBrightnessMultiplier()); //-V522
	TheEngine->GetVariable("postMotionBlur")->SetIntegerValue(motionBlurBox->GetValue()); //-V522
	TheEngine->GetVariable("postDistortion")->SetIntegerValue(distortionBox->GetValue()); //-V522
	TheEngine->GetVariable("postGlowBloom")->SetIntegerValue(glowBloomBox->GetValue()); //-V522

	int width = TheDisplayMgr->GetDisplayWidth();
	int height = TheDisplayMgr->GetDisplayHeight();

	const Widget *listItem = resolutionList->GetFirstSelectedListItem();
	if (listItem)
	{
		const DisplayMode *mode = TheDisplayMgr->GetCurrentDisplay()->GetDisplayMode(listItem->GetNodeIndex());
		width = mode->GetDisplayWidth();
		height = mode->GetDisplayHeight();
	}

	uint flags = (fullscreenBox->GetValue() != 0) ? kDisplayFullscreen : 0;

	int selection = refreshSyncMenu->GetSelection();
	if (selection >= 1)
	{
		flags |= kDisplayRefreshSync;
		if (selection == 2)
		{
			flags |= kDisplaySyncTear;
		}
	}

	int samples = 1;
	selection = multisamplingMenu->GetSelection();
	if (selection == 1)
	{
		samples = 2;
	}
	else if (selection == 2)
	{
		samples = 4; //-V112
	}
	else if (selection == 3) //-V2516
	{
		samples = 8;
	}

	if ((width != TheDisplayMgr->GetDisplayWidth()) || (height != TheDisplayMgr->GetDisplayHeight()) || (samples != TheDisplayMgr->GetDisplaySamples()) || (flags != TheDisplayMgr->GetDisplayFlags()))
	{
		TheDisplayMgr->SetDisplayMode(width, height, samples, flags);

		int displayWidth = TheDisplayMgr->GetDisplayWidth();
		int displayHeight = TheDisplayMgr->GetDisplayHeight();
		if ((displayWidth != width) || (displayHeight != height))
		{
			int index = 0;
			const Display *display = TheDisplayMgr->GetCurrentDisplay();
			const DisplayMode *mode = display->GetFirstDisplayMode();
			while (mode)
			{
				int w = mode->GetDisplayWidth();
				int h = mode->GetDisplayHeight();
				if ((w == displayWidth) && (h == displayHeight))
				{
					resolutionList->SelectListItem(index);
					break;
				}

				index++;
				mode = mode->Next();
			}
		}

		TheEngine->GetVariable("displayWidth")->SetIntegerValue(width); //-V522
		TheEngine->GetVariable("displayHeight")->SetIntegerValue(height); //-V522
		TheEngine->GetVariable("displaySamples")->SetIntegerValue(samples); //-V522
		TheEngine->GetVariable("displayFull")->SetIntegerValue((flags & kDisplayFullscreen) != 0); //-V522
		TheEngine->GetVariable("displaySync")->SetIntegerValue((flags & kDisplayRefreshSync) != 0); //-V522
		TheEngine->GetVariable("displayTear")->SetIntegerValue((flags & kDisplaySyncTear) != 0); //-V522

		return (true);
	}
	else if (((TheGraphicsMgr->GetRenderOptionFlags() ^ renderOptionFlags) & (kRenderOptionStructureEffects | kRenderOptionMotionBlur | kRenderOptionDistortion | kRenderOptionGlowBloom | kRenderOptionAmbientOcclusion)) != 0) //-V2516
	{
		GraphicsMgr::Delete();
		GraphicsMgr::New();
	}

	return (false);
}


MenuWindow::MenuWindow() :
	GameWindow("game/Menu"),
	Singleton<MenuWindow>(TheMenuWindow)
{

}


void MenuWindow::Preprocess()
{
	GameWindow::Preprocess();

	btnGraphicsSettings = static_cast<PushButtonWidget *>(FindWidget("Graphics"));
	btnControlsSettings = static_cast<PushButtonWidget *>(FindWidget("Controls"));
	btnExit = static_cast<PushButtonWidget *>(FindWidget("Exit"));
	btnCancel = static_cast<PushButtonWidget *>(FindWidget("Cancel"));
}


void MenuWindow::HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) //-V2558
{
	EventWidget::S eventType = eventData->eventType;

	if(eventType == EventWidget::Activate)
	{
		if(widget == btnExit)
		{
		}
		else if(widget == btnGraphicsSettings)
		{
			GraphicsSettingsWindow::Open();
		}
		else if(widget == btnControlsSettings)
		{
			ControlSettingsWindow::Open();
		}
		else if(widget == btnCancel) //-V2516
		{
			CallCompletionProc();
			Close();
		}
	}
}


void MenuWindow::Open()
{
    if(TheMenuWindow)
    {
        TheInterfaceMgr->SetActiveWindow(TheMenuWindow);
    }
    else
    {
        TheInterfaceMgr->AddWidget(new MenuWindow); //-V2511
		TheInterfaceMgr->SetActiveWindow(TheMenuWindow);
    }
}


bool MenuWindow::HandleKeyboardEvent(const KeyboardEventData *eventData) //-V2506
{
	EventKeyboard::S eventType = eventData->eventType;

	if(eventType == EventKeyboard::KeyDown)
	{
		KeyCode::E keyCode = eventData->keyCode;

		if(keyCode == KeyCode::Escape)
		{
			TheInterfaceMgr->RemoveWidget(TheMenuWindow);
			return true;
		}
	}

	return Window::HandleKeyboardEvent(eventData);
}


void ControlSettingsWindow::Open()
{
    if(TheControlSettingsWindow)
    {
        TheInterfaceMgr->SetActiveWindow(TheControlSettingsWindow);
    }
    else
    {
        TheInterfaceMgr->AddWidget(new ControlSettingsWindow); //-V2511
    }
}


ControlSettingsWindow::ControlSettingsWindow() :
    GameWindow("game/Controls"),
    Singleton<ControlSettingsWindow>(TheControlSettingsWindow)
{
    configWidget = nullptr;
}


ControlSettingsWindow::~ControlSettingsWindow()
{
    TheInputMgr->SetConfigProc(nullptr);
    TheInputMgr->SetInputMode(InputMode::Inactive);
}


void ControlSettingsWindow::ConfigProc(InputControl *control, float value, void *cookie)
{
    ControlSettingsWindow *window = static_cast<ControlSettingsWindow *>(cookie); //-V2571

    InputWidget *widget = window->configWidget;
    if(widget)
    {
        window->configWidget = nullptr;
        widget->SetInputControl(control, value);
    }
}


void ControlSettingsWindow::Preprocess()
{
    GameWindow::Preprocess();

    okayButton = static_cast<PushButtonWidget *>(FindWidget("OK"));
    cancelButton = static_cast<PushButtonWidget *>(FindWidget("Cancel"));

    controlList = static_cast<ListWidget *>(FindWidget("List"));

    mouseSlider = static_cast<SliderWidget *>(FindWidget("Mouse"));
    mouseText = static_cast<TextWidget *>(FindWidget("MouseText"));
    invertMouseBox = static_cast<CheckWidget *>(FindWidget("InvertMouse"));
    smoothMouseBox = static_cast<CheckWidget *>(FindWidget("SmoothMouse"));

    controllerSlider = static_cast<SliderWidget *>(FindWidget("Controller"));
    controllerText = static_cast<TextWidget *>(FindWidget("ControllerText"));
    invertXAxisBox = static_cast<CheckWidget *>(FindWidget("InvertX"));
    invertYAxisBox = static_cast<CheckWidget *>(FindWidget("InvertY"));

    const StringTable actionTable("game/Input");

    Action *action = TheInputMgr->GetFirstAction();
    while(action)
    {
        if((action->GetActionFlags() & kActionPersistent) != 0)
        {
            Widget *group = new Widget; //-V2511

            TextWidget *textWidget = new TextWidget(Vector2D(100.0F, 16.0F), actionTable.GetString(StringID(action->GetActionType())), "font/Normal"); //-V522 //-V2511
            textWidget->SetWidgetPosition(Point3D(0.0F, 5.0F, 0.0F)); //-V522
            textWidget->SetTextAlignment(TextAlignment::Right);
            textWidget->Disable();
            group->AppendSubnode(textWidget); //-V522

            InputWidget *inputWidget = new InputWidget(controlList, action); //-V2511
            inputWidget->SetWidgetPosition(Point3D(112.0F, 3.0F, 0.0F)); //-V522
            group->AppendSubnode(inputWidget);

            controlList->AppendListItem(group);
            group->Enable();
        }

        action = action->Next();
    }

    int sensitivity = TheInputMgr->GetMouseSensitivity();
    mouseSlider->SetValue(sensitivity - 1);
    mouseText->SetText(String<7>(sensitivity));

    uint flags = TheInputMgr->GetMouseFlags();

    if(flags & kMouseInverted)
    {
        invertMouseBox->SetValue(1);
    }

    if(flags & kMouseSmooth)
    {
        smoothMouseBox->SetValue(1);
    }

    controllerSlider->SetValue(sensitivity - 1);
    controllerText->SetText(String<7>(sensitivity));

    TheInputMgr->SetConfigProc(&ConfigProc, this);
    SetFocusWidget(controlList);
}


bool ControlSettingsWindow::HandleKeyboardEvent(const KeyboardEventData *eventData) //-V2506
{
    if(eventData->eventType == EventKeyboard::KeyDown)
    {
        KeyCode::E keyCode = eventData->keyCode;

        if(keyCode == KeyCode::Enter)
        {
            if(GetFocusWidget() == controlList)
            {
                controlList->Activate();
                return (true);
            }
        }
        else if((keyCode == KeyCode::Backspace) || (keyCode == KeyCode::Delete)) //-V2516
        {
            if(GetFocusWidget() == controlList)
            {
                const Widget *group = controlList->GetFirstSelectedListItem();
                if(group)
                {
                    static_cast<InputWidget *>(group->GetLastSubnode())->SetInputControl(nullptr);
                }

                return (true);
            }
        }
    }

    return (Window::HandleKeyboardEvent(eventData));
}


void ControlSettingsWindow::HandleWidgetEvent(Widget *widget, const WidgetEventData *eventData) //-V2558
{
    EventWidget::S eventType = eventData->eventType;

    if(eventType == EventWidget::Activate)
    {
        if(widget == okayButton)
        {
            TheInputMgr->ClearAllControlActions();

            const Widget *group = controlList->GetFirstListItem();
            while(group)
            {
                const InputWidget *inputWidget = static_cast<InputWidget *>(group->GetLastSubnode());

                InputControl *control = inputWidget->GetInputControl();
                if(control)
                {
                    control->SetControlAction(inputWidget->GetInputAction());
                }

                group = group->Next();
            }

            TheEngine->GetVariable("sensitivity")->SetIntegerValue(mouseSlider->GetValue() + 1); //-V522
            TheEngine->GetVariable("invertMouse")->SetIntegerValue(invertMouseBox->GetValue()); //-V522
            TheEngine->GetVariable("smoothMouse")->SetIntegerValue(smoothMouseBox->GetValue()); //-V522

            TheEngine->GetVariable("looksens")->SetIntegerValue(controllerSlider->GetValue() + 1); //-V522
            TheEngine->GetVariable("invertX")->SetIntegerValue(invertXAxisBox->GetValue()); //-V522
            TheEngine->GetVariable("invertY")->SetIntegerValue(invertYAxisBox->GetValue()); //-V522

            ConfigDataDescription::WriteEngineConfig(TheEngine->GetConfigFileName());
            ConfigDataDescription::WriteInputConfig(TheEngine->GetInputFileName());

            CallCompletionProc();
            Close();
        }
        else if(widget == cancelButton)
        {
            CallCompletionProc();
            Close();
        }
        else if(widget == controlList) //-V2516
        {
            const Widget *group = controlList->GetFirstSelectedListItem();
            if(group)
            {
                static_cast<InputWidget *>(group->GetLastSubnode())->BeginConfig();
            }
        }
    }
    else if(eventType == EventWidget::Change) //-V2516
    {
        if(widget == mouseSlider)
        {
            mouseText->SetText(String<7>(mouseSlider->GetValue() + 1));
        }
        else if(widget == controllerSlider) //-V2516
        {
            controllerText->SetText(String<7>(controllerSlider->GetValue() + 1));
        }
    }
}


void ControlSettingsWindow::SelectControl(const InputWidget *inputWidget)
{
    int index = 0;
    const Widget *group = controlList->GetFirstListItem();
    while(group)
    {
        InputWidget *widget = static_cast<InputWidget *>(group->GetLastSubnode());
        if(widget == inputWidget)
        {
            controlList->SelectListItem(index);
        }

        index++;
        group = group->Next();
    }
}


void ControlSettingsWindow::ClearDuplicateControls(const InputControl *control, const InputWidget *inputWidget)
{
    const Widget *group = controlList->GetFirstListItem();
    while(group)
    {
        InputWidget *widget = static_cast<InputWidget *>(group->GetLastSubnode());
        if((widget != inputWidget) && (widget->GetInputControl() == control))
        {
            widget->SetInputControl(nullptr);
        }

        group = group->Next();
    }
}
