#pragma once
#include <Windows.h>
class Timer {
	long long startTime;
	long long lastCallToUpdate;
	long long currentCallToUpdate;
	long long frequency;

public:

	Timer() {
		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);
		frequency = t.QuadPart;

		Reset();
	}
	void Reset() {
		//Set the Current time:
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		startTime = t.QuadPart;
		currentCallToUpdate = t.QuadPart;
		lastCallToUpdate = t.QuadPart;
	}
	void Update() {
		lastCallToUpdate = currentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		currentCallToUpdate = t.QuadPart;
	}

	double GetTimeTotal() {
		double d = currentCallToUpdate - startTime;
		return d / frequency;
	}

	double GetTimeDelta() {
		double d = currentCallToUpdate - lastCallToUpdate;
		return d / frequency;
	}
};