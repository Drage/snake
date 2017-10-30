
#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
	public:
		// Constructors
		Time();
		Time(long secs, long usecs = 0);
	
		// Get the current time
		static Time Now();
	
		// Operators
		Time operator+ (const Time &other) const;
		Time operator- (const Time &other) const;
		void operator+= (const Time &other);
		void operator-= (const Time &other);
		void operator= (const Time &other);
		bool operator== (const Time &other) const;
		bool operator!= (const Time &other) const;
		bool operator< (const Time &other) const;
		bool operator> (const Time &other) const;
	
		// Decomposition
		void Breakdown(int &days, int &hours, int &mins, int &secs, int &us) const;
	
		// Conversion to fractional number
		double ToSecs() const;
	
		// Conversion to text representation hh:mm:ss:uuuuuu
		std::string ToString() const;

	private:
		long m_sec;
		long m_usec;
};

class Timer
{
	public:
		// Constructor
		Timer();
		
		// Operations
		void Start();
		void Pause();
		void Stop();
		void Reset();
		
		// Check state
		bool IsPaused() const;
		bool IsStarted() const;
		
		// Decomposition
		void ElapsedTime(int &days, int &hours, int &mins, int &secs, int &us) const;
		
		// Convert to fractional number
		double ElapsedSeconds() const;
		
		// Convert to text representation hh:mm:ss:uuuuuu
		std::string ToString();
		
	private:
		Time m_startTime;
		Time m_pausedTime;
		bool m_paused;
		bool m_started;
};

#endif
