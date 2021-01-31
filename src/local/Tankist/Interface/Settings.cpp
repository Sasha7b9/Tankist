#include "stdafx.h"


GraphicsSettingsWindow *TheGraphicsSettingsWindow = nullptr;


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
