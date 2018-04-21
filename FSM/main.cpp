#include <curses.h>
#include <stdlib.h>

#include "fsm.h"

void printMainScreenText(void);

int main(int argc, char *argv[])
{
	initscr();

	raw();
	keypad(stdscr, TRUE);
	noecho();

	start_color();

	printMainScreenText();

	int myUserData;

	fsm clientFSM(START);
	tEvento event;
	const tEstado * currentState;

	int ch;
	char character;
	while (true)
	{
		ch = getch();

		mvaddch(9, 55, ch);

		character = ch;

		switch (character)
		{
		case 'q':
			event = I_AM_READY;
			break;
		case 'w':
			event = ACK;
			break;
		case 'e':
			event = MOVE;
			break;
		case 'r':
			event = QUIT;
			break;
		case 't':
			event = ERROR;
			break;
		case 'y':
			event = TIMEOUT;
			break;
		case 'u':
			event = TIMEOUT_2;
			break;
		case 'i':
			event = SEND_MOVE;
			break;
		}

		clientFSM.run(event, &myUserData);

		currentState = clientFSM.getState();

		if (currentState == START)
		{
			mvaddstr(12, 55, "START                  ");
		}
		else if (currentState == STAND_BY)
		{
			mvaddstr(12, 55, "STAND_BY                ");
		}
		else if (currentState == WAIT_FOR_ACK)
		{
			mvaddstr(12, 55, "WAIT_FOR_ACK              ");
		}
		else if (currentState == END_PROGRAM)
		{
			mvaddstr(12, 55, "END_PROGRAM          ");
		}

		refresh();
	}


	endwin();
	return 0;
}

void sendERROR(void * userData)
{
	mvaddstr(11, 55, "ERROR");
}

void sendMOVE(void * userData)
{
	mvaddstr(11, 55, "MOVE");
}

void sendACK(void * userData)
{
	mvaddstr(11, 55, "ACK  ");
}

void noAction(void * userData)
{
	mvaddstr(11, 55, "               ");
}

void printMainScreenText(void)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvaddstr(0, 0, "Programa de Simulacion de Cliente de Worms Movement Implementado con FSM.");
	mvaddstr(1, 0, "Gonzalo Belascuen");
	mvaddstr(3, 0, "Presione las teclas indicadas para simular eventos \ny ver que la maquina de estados responde correctamente.");

	mvaddstr(6, 0, "Tecla = Evento");

	int i = 0;
	mvaddstr(8 + i++, 0, "Q = I_AM_READY");
	mvaddstr(8 + i++, 0, "W = ACK");
	mvaddstr(8 + i++, 0, "E = MOVE");
	mvaddstr(8 + i++, 0, "R = QUIT");
	mvaddstr(8 + i++, 0, "T = ERROR");
	mvaddstr(8 + i++, 0, "Y = TIMEOUT");
	mvaddstr(8 + i++, 0, "U = TIMEOUT_2");
	mvaddstr(8 + i++, 0, "I = SEND_MOVE");
	mvaddstr(8 + i++, 0, "O = START_TIMER");
	mvaddstr(8 + i++, 0, "P = STERT_TIMER2");

	for (i = 0; i < 5; i++)
	{
		mvaddch(8 + i, 20, '|');
	}

	i = 0;
	mvaddstr(8 + i++, 30, "Status de la FSM");
	mvaddstr(8 + i++, 25, "Evento Recibido:");
	mvaddstr(8 + i++, 25, "Evento Recibido Anterior:");
	mvaddstr(8 + i++, 25, "Accion Ejecutada:");
	mvaddstr(8 + i++, 25, "Current State:");

	attroff(COLOR_PAIR(1));
	refresh();
}

