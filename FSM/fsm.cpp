#include "fsm.h"

STATE START[] = { { I_AM_READY , STAND_BY, sendACK },{ FIN_TABLA,START, noAction } };
STATE STAND_BY[] = { { MOVE,STAND_BY,sendACK },{ QUIT,END_PROGRAM,sendACK },{ SEND_MOVE,WAIT_FOR_ACK,sendMOVE },{ FIN_TABLA,STAND_BY, noAction } };
STATE WAIT_FOR_ACK[] = { { MOVE , WAIT_FOR_ACK , sendACK },{ TIMEOUT , WAIT_FOR_ACK , sendMOVE },{ ERROR , END_PROGRAM , noAction },{ TIMEOUT_2, END_PROGRAM , sendERROR },{ QUIT, END_PROGRAM , sendACK },{ ACK , STAND_BY , noAction },{ FIN_TABLA, WAIT_FOR_ACK , noAction } };
STATE END_PROGRAM[] = { { FIN_TABLA, END_PROGRAM , noAction } };

fsm::fsm(const tEstado * s)
{
	estado = s;
}

fsm::~fsm()
{
}

void fsm::run(tEvento ev, void * userData)
{
	int i = 0;

	for (i = 0; (estado[i].ev != FIN_TABLA) && (estado[i].ev != ev); i++) {}

	estado[i].action(userData);
	estado = estado[i].proximoEstado;
}

const tEstado * fsm::getState()
{
	return estado;
}