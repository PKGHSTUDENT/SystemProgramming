VOID WINAPI ServiceCtrlHandler(DWORD dwControl)
{
	switch (dwControl)
	{
	case SERVICE_CONTROL_STOP:

		out << "Count = " << nCount << endl;
		out << "The service is finished." << endl << flush;
		out.close();
		
		service_status.dwCurrentState = SERVICE_STOPPED;
		
		SetServiceStatus(hServiceStatus, &service_status);
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		service_status.dwCurrentState = SERVICE_STOPPED;
		
		SetServiceStatus(hServiceStatus, &service_status);
		break;
	default:
		++service_status.dwCheckPoint;
		SetServiceStatus(hServiceStatus, &service_status);
		break;
	}
	return;
}