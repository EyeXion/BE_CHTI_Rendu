#include <stdio.h>
#include <stdlib.h>
int calculModule(short ** TabSig,int k);

extern short * TabSig;
int res[64];
int res_verif;
int k;
int val;

int main(){
	val = 17;
	for (k =1; k<65; k++){
		if (k == val) {
			int break_pt = -1;
		}
		res[k-1] = calculModule(&TabSig, k);
		if (k == val){
			res_verif = res[k-1];
		}
	}
	k = 0;
	while(1){}
}
