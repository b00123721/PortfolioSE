#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
class Machine				//classe Machine 
{
	class State* current;
public:
	Machine();
	void setCurrent(State* s)
	{
		current = s;			//der derzeitige state der fsm??
	}
	void sense();
	void idle();
	void process();
};
 
class State
{
public:
	virtual void sense(Machine* m)
	{
		cout << "   already sensing\n";
	}
	virtual void idle(Machine* m)
	{
		cout << "   already ideling\n";
	}
	virtual void process(Machine* m)
	{
		cout << "already processing\n";
	}
};

//method of class machine
void Machine::sense()
{
	current->sense(this);
}

//method of class machine
void Machine::idle()
{
	current->idle(this);
}

//method of class machine
void Machine::process()
{
	current->process(this);
}

class SENSE : public State
{
public:
	SENSE()//constructor for ON class
	{
		cout << "   sense-constructor ";
	};
	~SENSE()//destructor for ON class
	{
		cout << "   destructor-sense\n";
	};
	void process(Machine* m);
};

class IDLE : public State
{
public:
	IDLE()//constructor for OFF class
	{
		cout << "   idle-constructor ";
	};
	~IDLE()//destructor for OFF class
	{
		cout << "   destructor-idle\n";
	};
	void sense(Machine* m)
	{
		cout << "   going from idle to sense";
		m->setCurrent(new SENSE());
		delete this;
	}
};

class PROCESS : public State
{
public:
	PROCESS()
	{
		cout << "Process constructor";
	}
	~PROCESS()
	{
		cout << "Proces destructor\n";
	}
	void idle(Machine* m)
	{
		cout << " going from process to idle";
		m->setCurrent(new IDLE());
		delete this;
	}

};

//method of SENSE (already declared)
void SENSE::process(Machine* m)
{
	cout << "   going from sense to PROCESS";
	m->setCurrent(new PROCESS());
	delete this;
}

//constructor Machine? neuer off state als Beginn
Machine::Machine()
{
	current = new IDLE();
	cout << '\n';
}

int main()
{
	void(Machine:: *ptrs[])() =
	{
	  &Machine::idle, &Machine::sense, &Machine::process
	};
	Machine fsm;			//create object of Machine calles fsm
	int num;

	using namespace std::this_thread;     // sleep_for, sleep_until
	using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
	using std::chrono::system_clock;

	while (1)
	{

		num = 0;
		cout << "Enter 1 to triger a measurement event!";
		cin >> num;
		if (num < 0 || num > 1)
		{
			cout << "number was wrong";
			break;
		}
		if (num == 1)
		{
			(fsm.*ptrs[1])();
			sleep_for(4s);
			(fsm.*ptrs[2])();
			sleep_for(4s);
			(fsm.*ptrs[0])();
			num = 0;
		}

	}
}

/*
#include <iostream>
using namespace std;
class Machine				//classe Machine
{
	class State* current;
public:
	Machine();
	void setCurrent(State* s)
	{
		current = s;			//der derzeitige state der fsm??
	}
	void on();
	void off();
};

class State
{
public:
	virtual void on(Machine* m)
	{
		cout << "   already ON\n";
	}
	virtual void off(Machine* m)
	{
		cout << "   already OFF\n";
	}
};

//method of class machine
void Machine::on()
{
	current->on(this);
}

//method of class machine
void Machine::off()
{
	current->off(this);
}

class ON : public State
{
public:
	ON()//constructor for ON class
	{
		cout << "   ON-constructor ";
	};
	~ON()//destructor for ON class
	{
		cout << "   destructor-ON\n";
	};
	void off(Machine* m);
};

class OFF : public State
{
public:
	OFF()//constructor for OFF class
	{
		cout << "   OFF-constructor ";
	};
	~OFF()//destructor for OFF class
	{
		cout << "   destructor-OFF\n";
	};
	void on(Machine* m)
	{
		cout << "   going from OFF to ON";
		m->setCurrent(new ON());
		delete this;
	}
};

//method of ON (already declared)
void ON::off(Machine* m)
{
	cout << "   going from ON to OFF";
	m->setCurrent(new OFF());
	delete this;
}

//constructor Machine? neuer off state als Beginn
Machine::Machine()
{
	current = new OFF();
	cout << '\n';
}

int main()
{
	void(Machine:: *ptrs[])() =
	{
	  &Machine::off, &Machine::on
	};
	Machine fsm;			//create object of Machine calles fsm
	int num;
	while (1)
	{
		cout << "Enter 0/1: ";
		cin >> num;
		(fsm.*ptrs[num])();
	}
}
*/