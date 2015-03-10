//-----------------------------------------------------
// DEFINITION OF THE STATES BASED ON THE FSM.h
//-----------------------------------------------------

#ifndef myStates_H
#define myStates_H


//Declaracion de las funciones
extern void estadoinicial(void);
extern void subTime(void);
extern void addTime(void);
extern void counting(void);
extern void failure(void);
extern void deactivated(void);
extern void explosion(void);
extern void adjusting(void);
//extern void bomb_ready(void);


//Declaracion del nombre de ESTADOS y de EVENTOS
#define S_INITIAL  		0x01
#define S_ADJTIME		0x02
#define S_ADDTIME		0x12
#define S_MINTIME		0x22
#define S_START 		0x03
#define S_STARTED   	0x04
#define S_STARTETEDERR	0X14
#define S_DEACTIVATED   0x05
#define S_EXPLOSION   	0x05

#define EV_BOOM     	0x41
#define EV_SUCCESS 		0x43	
#define EV_ERROR    	0x44
#define EV_BACK         0x45	

#define bnegro 	0x10
#define brojo 	0x11
#define bverde 	0x12

// Estructuras descriptivas de mi diagrama de flujo
const FSMClass::FSM_State_t FSM_State[] PROGMEM= {
	// STATE,STATE_FUNC
	{S_INITIAL,estadoinicial},
	{S_ADJTIME,adjusting},
	{S_ADDTIME,addTime},
	{S_MINTIME,subTime},
	{S_START,0},
	{S_STARTED,counting},
	{S_STARTETEDERR,failure},
	{S_DEACTIVATED,deactivated},
	{S_EXPLOSION,explosion}
};

const FSMClass::FSM_NextState_t FSM_NextState[] PROGMEM= {
	// STATE,EVENT,NEXT_STATE
	{S_INITIAL,bnegro,S_ADJTIME},
	{S_ADJTIME,brojo,S_ADDTIME},
	{S_ADJTIME,bverde,S_MINTIME},
	{S_ADJTIME,bnegro,S_START},
        {S_ADDTIME,EV_BACK,S_ADJTIME},
        {S_MINTIME,EV_BACK,S_ADJTIME},
	{S_START,bnegro,S_ADJTIME},
	{S_START,brojo,S_STARTED},
	{S_STARTED,brojo,S_STARTETEDERR},
	{S_STARTED,bverde,S_DEACTIVATED},
	{S_STARTED,EV_BOOM,S_EXPLOSION},  
	{S_DEACTIVATED,bverde,S_DEACTIVATED},
	{S_DEACTIVATED,EV_SUCCESS,S_STARTED},
	{S_DEACTIVATED,bnegro,S_INITIAL},
	{S_EXPLOSION,bnegro,S_INITIAL},
};


//Macros para el cálculo de los tamaños de las estructuras
//NO MODIFICAR
#define nStateFcn		sizeof(FSM_State)/sizeof(FSMClass::FSM_State_t)
#define nStateMachine		sizeof(FSM_NextState)/sizeof(FSMClass::FSM_NextState_t)

#endif

