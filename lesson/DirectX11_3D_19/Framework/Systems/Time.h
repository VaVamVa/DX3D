#pragma once

class Time : public Singleton<Time>
{
public:
	friend Singleton<Time>;

	static bool IsStopped() { return isTimerStopped; }
	static float Delta() { return timeElapsed; }

	void Update();
	void Print();

	void Start();
	void Stop();

	float FPS() const { return framePerSecond; }
	float Running() const { return runningTime; }

private:
	Time();
	~Time();

private:
	static bool isTimerStopped;
	static float timeElapsed;

	int64 tickPerSecond;
	int64 currentTime;
	int64 lastTime;
	int64 lastFPSUpdate;
	int64 fpsUpdateInterval;

	uint frameCount;
	float runningTime;
	float framePerSecond;
};

class Timer
{
public:
	Timer();
	~Timer();
	
	void Start(function<void()> func, int milliSec, uint repeat = 0);
	void Stop();

private:
	mutex m;

	bool bComplete;
	uint count;
};

class Performance
{
public:
	Performance();

	void Start();
	float End();

private:
	__int64 tick;
	__int64 start, end;
};