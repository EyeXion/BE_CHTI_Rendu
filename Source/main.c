#include "../Drivers/gassp72.h"
#include "../Drivers/etat.h"

extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;
type_etat etat;

void timer_callback(void);
int main(void){
		// activation de la PLL qui multiplie la fr�quence du quartz par 9
		CLOCK_Configure();
		// config port PB1 pour �tre utilis� en sortie
		//GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
		// initialisation du timer 4
		// Periode_en_Tck doit fournir la dur�e entre interruptions,
		float f = 110250;
		int periode_en_Tck_PWM = (((float)(72*1000000))/f);
		// config port PB0 pour �tre utilis� par TIM3-CH3
		GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
		// config TIM3-CH3 en mode PWM
	
	
		etat.resolution = PWM_Init_ff(TIM3, 3, periode_en_Tck_PWM);
		float periode_ticks = (float)(72)*(float)PeriodeSonMicroSec;
		etat.periode_ticks = (int)periode_ticks;
		etat.son = (void *)&Son;
		etat.taille = LongueurSon;
		etat.position = 0;
		// exprim�e en p�riodes Tck de l'horloge principale du STM32 (72 MHz)
		Timer_1234_Init_ff(TIM4, etat.periode_ticks);
		// enregistrement de la fonction de traitement de l'interruption timer
		// ici le 2 est la priorit�, timer_callback est l'adresse de cette fonction, a cr��r en asm,
		// cette fonction doit �tre conforme � l'AAPCS
		Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
		// lancement du timer
		Run_Timer(TIM4);
		timer_callback();
		while(1){
		}
}
