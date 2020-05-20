/* BSD 3 - Clause License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Code by Cassius Fiorin - cafiorin@gmail.com
http://pinballhomemade.blogspot.com.br
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(NewTimer__INCLUDED_)
#define NewTimer__INCLUDED_

#include "defines.h"
#include "Runnable.h"

class Observer;
class Subject;

enum NewTimerType
{
	once,
	continuous
};

class NewTimer : public Runnable
{
public:
	NewTimer(unsigned long time, NewTimerType type, Observer* observer);

	virtual ~NewTimer();
	byte GetId() { return m_Id; }

	void loop();
	void Start();
	void Stop() { m_enabled = false; }
	bool Check(unsigned long time=0);
	void ChangeTimerValue(unsigned long time) 
	{ 
		m_time = time; 
	}
	void AddObserverToTimeIsOver(Observer* observer);

private:
	void Initialize(unsigned long time, NewTimerType type);
	NewTimerType m_type;
	bool m_enabled;
	Subject* m_EventToTimeIsOver;

	static byte m_IdGenerator;
	byte m_Id;

protected:
	#ifdef DOS
	clock_t m_time;
	clock_t m_lastTime;  // the last time
	#endif
	
	#ifdef ARDUINOLIB
	unsigned long m_time;
	unsigned long m_lastTime;  // the last time
	#endif
};
#endif // !defined(NewTimer__INCLUDED_)
