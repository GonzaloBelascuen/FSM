#pragma once

typedef enum { I_AM_READY, ACK, MOVE, QUIT, ERROR, TIMEOUT, TIMEOUT_2, SEND_MOVE, FIN_TABLA } tEvento;

struct tEstado
{
	tEvento ev;
	const tEstado * proximoEstado;
	void(*action)(void *);
};


class fsm
{
private:
	const tEstado * estado;

public:
	fsm(const tEstado * s);
	~fsm();

	void run(tEvento ev, void * userData);
};