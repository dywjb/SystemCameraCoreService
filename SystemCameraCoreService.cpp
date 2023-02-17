#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/expressions.hpp>
#include <boost/date_time.hpp>
#include <boost/locale.hpp>
#include <boost/json.hpp>
#include <Windows.h>


void startCapture()
{
	WCHAR workDirPath[MAX_PATH]{};
	WCHAR logFilePath[MAX_PATH]{};

	if (!GetEnvironmentVariableW(L"USERPROFILE", workDirPath, MAX_PATH))
	{
		ExitProcess(GetLastError());
	}

	lstrcatW(workDirPath, L"\\SystemInformation\\");

	if (!SetCurrentDirectoryW(workDirPath))
	{
		ExitProcess(GetLastError());
	}

	for (;;)
	{
		SYSTEMTIME time{};
		GetLocalTime(&time);

		if (time.wHour > 6 && time.wHour < 10)
		{
			// TODO: take photo
		}

		Sleep(2 * 60 * 1000);  // 2 minutes
	}
}


int main()
{
    startCapture();
}