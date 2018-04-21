#include "fsm.h"


fsm::fsm(const tEstado * s)
{
	estado = s;
}

fsm::~fsm()
{
}

void fsm::run(tEvento ev, void * userData)
{
	tabla[estado][ev].action(userData);
	estado = tabla[estado][ev].proximoEstado;
}