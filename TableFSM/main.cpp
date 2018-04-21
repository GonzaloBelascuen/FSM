#include <curses.h>
#include <stdlib.h>

#include "tableFsm.h"

void printMainScreenText(void);

/* output functions */
int main(int argc, char *argv[])
{
	initscr();

	raw();
	keypad(stdscr, TRUE);
	noecho();

	start_color();

	printMainScreenText();

	int myUserData;

	tableFsm clientFSM(S1);
	tEvento event;
	tEstado currentState;


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
			event = E1;
			break;
		case 'w':
			event = E2;
			break;
		case 'e':
			event = E3;
			break;
		case 'r':
			event = E4;
			break;
		case 't':
			event = E5;
			break;
		default:
			character = NULL;
			break;
		}

		if(character)
			clientFSM.run(event, &myUserData);

		currentState = clientFSM.getState();

		switch (currentState)
		{
		case S1:
			mvaddstr(12, 55, "S1");
			break;
		case S2:
			mvaddstr(12, 55, "S2");
			break;
		case S3:
			mvaddstr(12, 55, "S3");
			break;
		}

		refresh();
	}


	endwin();
	return 0;
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
