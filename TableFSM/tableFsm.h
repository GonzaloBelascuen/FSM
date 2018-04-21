#pragma once

typedef enum { S1, S2, S3 } tEstado;
typedef enum { E1, E2, E3, E4, E5 } tEvento;

void A0(void *userData);
void A1(void *userData);
void A2(void *userData);
void A3(void *userData);
void A4(void *userData);
void A5(void *userData);

struct cell
{
	tEstado proximoEstado;
	void(*action)(void *);
};

class tableFsm
{
	private:

	const cell tabla[3][5] = {
	//    E1           E2           E3           E4              E5
	{ { S2,A1 },{ S1,A0 },{ S1,A0 },{ S1,A0 },{ S1,A0 } }, //S0
	{ { S2,A0 },{ S1,A2 },{ S3,A3 },{ S2,A0 },{ S2,A0 } }, //S1
	{ { S3,A0 },{ S3,A0 },{ S3,A0 },{ S1,A4 },{ S2,A5 } } };//S2

	tEstado estado;

	public:
	tableFsm(const tEstado s);
	~tableFsm();

	void run(tEvento ev, void  *  userData);

	tEstado getState();
};
