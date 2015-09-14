
#include "timer.h"



Timer::Timer()
{

	is_started = false;
	is_paused = false;
	is_stopped = false;

}


int Timer::StartTimer()
{
    
    if (!is_started)
    {

	start = SDL_GetTicks();

	is_started = true;

	is_stopped = false;

	is_paused = false;

        return 0;

    }

    return -1;

}


int Timer::RestartTimer()
{

    if (is_paused)
    {

        start = SDL_GetTicks() - paused;

	is_paused = false;

	is_stopped = false;

        return 0;

    }


    return -1;

}


int Timer::StopTimer()
{
	if (is_started)
	{

		if (is_paused)
		{

			stop = paused;

		}
		else
		{

			stop = SDL_GetTicks() - start;

		}
		is_stopped = true;

		is_paused = false;

		is_started = false;

        return 0;

    }

    return -1;

}


Uint32 Timer::GetTimeMs()
{

	if (is_stopped)
	{

		return stop;

	}

	if (is_paused)
	{

		return paused;

	}

	if (is_started)
	{

		return SDL_GetTicks() - start;

	}

	return 0;
}


float Timer::GetTimeSeconds()
{

	return GetTimeMs() / 1000.f;

}


int Timer::PauseTimer()
{
	if (!is_paused)
	{
		paused = SDL_GetTicks() - start;
		is_paused = true;

        return 0;

	}

    return -1;

}


bool Timer::IsStarted()
{

	return is_started;

}


bool Timer::IsPaused()
{

	return is_paused;

}


bool Timer::IsStopped()
{

	return is_stopped;

}
