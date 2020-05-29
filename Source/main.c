#include <stdio.h>
#include <stdlib.h>
#include "../Drivers/gassp72.h"
#include "../Drivers/etat.h"

#define TYPESIG (0x33)

int calculModule(short * TabSig,int k);
void timer_callback(void);


int res[6];
int res_verif;
short dma_buf[64];
int k[6] = {17,18,19,20,23,24};
int nb_occ[6] = {0,0,0,0,0,0};//ne prendre ne compte un tir que s'il est détecté sur plusieurs fenêtres consécutives (par exemple 3)
int M2Tir = (int)(0xF07A8);
int tab_scores[6] = {0,0,0,0,0,0};
int seuil_score = 15;
//Valeur théo M2Tir : F07A8



extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;
int SonEnCours;
type_etat etat;


void sys_callback(){
	// Démarrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for (int i = 0; i < 6; i++){
		res[i] = calculModule(dma_buf, k[i]);
		if (res[i] > M2Tir){
			nb_occ[i]++;
		}
		if (res[i] < M2Tir){
			nb_occ[i] = 0;
		}
		if (nb_occ[i] == 15){
			SonEnCours = 1;
			tab_scores[i] += 1;
			nb_occ[i] = 0;
			etat.position = 0;
		}
	}
}


int main(){
	
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entrée analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage à l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, TYPESIG );
	Single_Channel_ADC( ADC1, 2 );
	// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf (a créér)
	Init_ADC1_DMA1( 0, dma_buf);

	// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
	Systick_Period_ff( 360000 );//période du traitement sera de 5 m
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorité, sys_callback est l'adresse de cette fonction, a créér en C
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;
	
	
	
		// config port PB1 pour être utilisé en sortie
		//GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
		// initialisation du timer 4
		// Periode_en_Tck doit fournir la durée entre interruptions,
		float f = 110250;
		int periode_en_Tck_PWM = (((float)(72*1000000))/f);
		// config port PB0 pour être utilisé par TIM3-CH3
		GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
		// config TIM3-CH3 en mode PWM
	
	
		etat.resolution = PWM_Init_ff(TIM3, 3, periode_en_Tck_PWM);
		float periode_ticks = (float)(72)*(float)PeriodeSonMicroSec;
		etat.periode_ticks = (int)periode_ticks;
		etat.son = (void *)&Son;
		etat.taille = LongueurSon;
		etat.position = etat.taille;
		// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
		Timer_1234_Init_ff(TIM4, etat.periode_ticks);
		// enregistrement de la fonction de traitement de l'interruption timer
		// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
		// cette fonction doit être conforme à l'AAPCS
		Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
		// lancement du timer
		Run_Timer(TIM4);
		timer_callback();
	
	while(1){}
}
