#include "Framework.h"
#include "Time.h"

bool  Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;

Time::Time()
	: tickPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0),
	  fpsUpdateInterval(0), frameCount(0), runningTime(0), framePerSecond(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&tickPerSecond);
	fpsUpdateInterval = tickPerSecond >> 1;
}

Time::~Time() { }

void Time::Update()
{
	if (isTimerStopped) return;

	//1. ����ð��� ������ �ð� ���� �� ���� �ð��� ����Ѵ�.
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)tickPerSecond;
	runningTime += timeElapsed;


	//2. FPS Update
	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)tickPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)tickPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}

	lastTime = currentTime;
}

void Time::Print()
{
}

void Time::Start()
{
	if (!isTimerStopped)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	isTimerStopped = false;
}

void Time::Stop()
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)tickPerSecond;
	isTimerStopped = true;
}

//////////////////////////  Timer  //////////////////////////

Timer::Timer()
	: bComplete(false), count(0) { }

Timer::~Timer() { }

void Timer::Start(function<void()> func, int milliSec, uint repeat)
{
	assert(bComplete == false);

	bComplete = false;
	thread t([=]()
		{
			while (true)
			{
				if (repeat > 0 && count == repeat)
					break;

				if (bComplete == true)
					break;

				count++;
				Sleep(milliSec);

				if (bComplete == true)
					break;

				func();
			}

			Stop();
		});
	t.detach();
}

void Timer::Stop()
{
	count = 0;

	bComplete = true;
}

//////////////////////////  Performance  //////////////////////////

Performance::Performance()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&tick);
}

void Performance::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&start);
}

float Performance::End()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&end);

	return (float)((double)(end - start) / tick * 1000.0f);
}
