VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	// регистрируем обработчик управляющих команд для сервиса
	hServiceStatus = RegisterServiceCtrlHandler(
		service_name, // имя сервиса
		ServiceCtrlHandler // обработчик управляющих команд
	);
	if (!hServiceStatus)
	{
		out.open("C:\\ServiceFile.log");
		out << "Register service control handler failed.";
		out.close();
		return;
	}
	// инициализируем структуру состояния сервиса
	service_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	service_status.dwCurrentState = SERVICE_START_PENDING;
	service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP |
		SERVICE_ACCEPT_SHUTDOWN;
	service_status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
	service_status.dwServiceSpecificExitCode = 0;
	service_status.dwCheckPoint = 0;
	service_status.dwWaitHint = 5000;
	// устанавливаем состояние сервиса
	if (!SetServiceStatus(hServiceStatus, &service_status))
	{
		out.open("C:\\ServiceFile.log");
		out << "Set service status 'SERVICE_START_PENDING' failed.";
		out.close();
		return;
	}

	// определяем сервис как работающий
	service_status.dwCurrentState = SERVICE_RUNNING;
	// нет ошибок
	service_status.dwWin32ExitCode = NO_ERROR;
	// устанавливаем новое состояние сервиса
	if (!SetServiceStatus(hServiceStatus, &service_status))
	{
		out.open("C:\\ServiceFile.log");
		out << "Set service status 'START_PENDING' failed.";
		out.close();
		return;
	}

	// открываем файл протокола работы сервиса
	out.open("C:\\ServiceFile.log");
	out << "The service is started." << endl << flush;
	out << "My name is: " << lpszArgv[0] << endl << flush;
	for (int i = 1; i < (int)dwArgc; ++i)
		out << "My " << i << " parameter = " << lpszArgv[i] << endl << flush;
	// рабочий цикл сервиса
	while (service_status.dwCurrentState == SERVICE_RUNNING)
	{
		++nCount;
		Sleep(3000);
	}
}