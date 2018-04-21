#include "tableFsm.h"
#include <curses.h>

void A0(void * userData)
{
	mvaddstr(11, 55, "A0");
}

void A1(void * userData)
{
	mvaddstr(11, 55, "A1");
}

void A2(void * userData)
{
	mvaddstr(11, 55, "A2");
}

void A3(void * userData)
{
	mvaddstr(11, 55, "A3");
}

void A4(void * userData)
{
	mvaddstr(11, 55, "A4");
}

void A5(void * userData)
{
	mvaddstr(11, 55, "A5");
}

tableFsm::tableFsm(const tEstado s)
{
	estado = s;
}

tableFsm::~tableFsm()
{
}

void tableFsm::run(tEvento ev, void * userData)
{
	tabla[estado][ev].action(userData);
	estado = tabla[estado][ev].proximoEstado;
}

tEstado tableFsm::getState()
{
	return estado;
}

