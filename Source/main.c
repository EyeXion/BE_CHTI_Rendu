#include <stdio.h>
#include <stdlib.h>
#include "../Drivers/gassp72.h"

#define TYPESIG (0x33)

int calculModule(short * TabSig,int k);


int res[6];
int res_verif;
short dma_buf[64];
int k[6] = {17,18,19,20,23,24};
int nb_occ[6] = {0,0,0,0,0,0};//ne prendre ne compte un tir que s'il est détecté sur plusieurs fenêtres consécutives (par exemple 3)
int M2Tir = (int)(0xF07A8);
int tab_scores[6] = {0,0,0,0,0,0};
int seuil_score = 15;
//Valeur théo M2Tir : F07A8
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
			tab_scores[i] += 1;
			nb_occ[i] = 0;
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
	
	while(1){}
}
