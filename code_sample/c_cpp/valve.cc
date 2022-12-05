#include <stdio.h>
#include <unistd.h>

//関節角をマニピュレータに送る関数
//引数: 各関節角とwait（ms）
void sendAngles(int j1,int j2,int j3,int j5,int j6,double wait)
{
	FILE *manip = fopen("/run/shm/angles","w");
	if(manip == NULL)
		return;
	fprintf(manip,"%d,%d,%d,%d,%d\n",j1,j2,j3,j5,j6);
	fclose(manip);
	usleep((int)(wait*1000));
}

//バルブの開閉指令を送るための関数
//引数: バルブの開閉状態（0か1）
void setValve(int valve_on_off)
{
	FILE *manip = fopen("/run/shm/ev_on_off","w");
	if(manip == NULL)
		return;
	fprintf(manip,"%d\n",valve_on_off);
	fclose(manip);

	FILE *manip = fopen("/run/shm/ev2_on_off","w");
	if(manip == NULL)
		return;
	fprintf(manip,"%d\n",valve_on_off);
	fclose(manip);
}

int main(int argc, char const* argv[])
{
	for(int i=0;i<10;i++){
		if(i%2){
			sendAngles(45,45,45,45,45,3000.0);
			setValve(0);
		}else{
			sendAngles(0,0,0,0,0,3000.0);
			setValve(1);
		}
	}

	return 0;
}
