#pragma once

typedef enum { I_AM_READY, ACK, MOVE, QUIT, ERROR, TIMEOUT, TIMEOUT_2, SEND_MOVE, FIN_TABLA } tEvento;

typedef struct tEstado STATE;

struct tEstado
{
	tEvento ev;
	const tEstado * proximoEstado;
	void(*action)(void *);
};

/* output functions */
void sendERROR(void * userData);
void sendMOVE(void * userData);
void sendACK(void * userData);
void noAction(void * userData);

extern STATE START[];
extern STATE STAND_BY[];
extern STATE WAIT_FOR_ACK[];
extern STATE END_PROGRAM[];


class fsm
{
private:
	const tEstado * estado;

public:
	fsm(const tEstado * s);
	~fsm();

	void run(tEvento ev, void * userData);
	const tEstado* getState();

};