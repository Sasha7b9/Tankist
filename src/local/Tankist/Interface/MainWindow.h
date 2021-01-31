#pragma once


using namespace Pi;


namespace Pi
{
	namespace MutatorType
	{
		const S Attempt = 'ACWM';
	}
}


/// Окно ожидания соединения с сервером
class AttemptConnectionWindow : public Window, public Completable<AttemptConnectionWindow>, public Singleton<AttemptConnectionWindow>
{
public:
    AttemptConnectionWindow();

private:
	TextWidget* text = nullptr; //-V122
	virtual void Move() override;
};


/// Окно ошибки соединения
class FailedConnectionWindow : public Window, public Completable<FailedConnectionWindow>, public Singleton<FailedConnectionWindow>
{
public:
	static void Open();
private:
	FailedConnectionWindow();
	virtual void HandleWidgetEvent(Widget*, const WidgetEventData*) override;
};


class MainWindow : public Window
{
public:
	MainWindow();

    // Возвращает адрес подключения к ангару
    pchar GetHangarAddress() const;

	pchar GetLogin() const;

	// Эту функцию нужно вызвать после удачного присоединения к master'у
	void ConnectToMasterIsOK();

	virtual void Move() override;

private:

	/// Текущий язык. 0 - английский, 1 - русский
	int language = 0;
	/// Расширенный режим. 0 - выключен, 1 - включён
	int extra = 0;

	bool connectedToMasterIsOK = false;

	PushButtonWidget *buttonLanguage = nullptr; //-V122
	PushButtonWidget *buttonHelp = nullptr; //-V122
	PushButtonWidget *buttonExtra = nullptr; //-V122
	PushButtonWidget *buttonExit = nullptr; //-V122
	PushButtonWidget *buttonSite = nullptr; //-V122
	PushButtonWidget *buttonConnect = nullptr; //-V122
	PushButtonWidget *buttonRegistration = nullptr; //-V122
	EditTextWidget   *lineEditLogin = nullptr; //-V122
	EditTextWidget   *lineEditPassword = nullptr; //-V122
	EditTextWidget   *lineEditAddress = nullptr; //-V122

	List<Widget> widgetsNormalMode;					///< Здесь хранятся виджеты, используемые в нормальном режиме
	List<Widget> widgetsExtraMode;					///< Здесь хранятся виджеты, используемые в расширенном режиме
	virtual void HandleWidgetEvent(Widget *, const WidgetEventData *) override;

	/// Переключить режим с обычного на расширенный и обратно
	void SetExtraMode();
	/// Добавить виджет нормального режима
	void AppendNormalWidget(Widget *);
	/// Добавить виджет обоих режимов
	void AppendBothWidget(Widget *);
	/// Установить настройки
	void LoadSettings();
	/// Сделать попытку поключения
	void AttemptConnection();
};
