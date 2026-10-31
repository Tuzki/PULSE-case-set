#include "pulse/software.h"
#include <math.h>
#define PERIOD (1.0/30000.0)
/* Source: fixed 50% triangular PWM; phase [0,D/2] latched at master zero.
   Continuous PI state remains in the native circuit integrator (no new ZOH).
   Gate turn-on is delayed 100 ns; turn-off is immediate. */
typedef struct {double at[4],due[4];int want[4],gate[4];} State;
static void set_gate(State*s,int i,int on,double now){
 if(!on){s->want[i]=s->gate[i]=0;s->due[i]=0;}
 else if(!s->want[i]){s->want[i]=1;s->gate[i]=0;s->due[i]=now+1e-7;}
}
static void set_leg(State*s,int leg,int high,double now){set_gate(s,2*leg,high,now);set_gate(s,2*leg+1,!high,now);}
static double wrap(double x){return x-floor(x);}
static void reload(State*s,double phase,double now){
 phase=wrap(phase/2);
 set_leg(s,0,1,now);set_leg(s,1,phase<=.25 || phase>=.75,now);
 s->at[0]=now+PERIOD/4;s->at[1]=now+3*PERIOD/4;
 double rise=wrap(phase-.25)*PERIOD,fall=wrap(phase+.25)*PERIOD;
 s->at[2]=rise>0?now+rise:0;s->at[3]=fall>0?now+fall:0;
}
PULSE_SW_EXPORT const pulse_software_info *PULSE_SW_CALL pulse_software_describe(void){static const pulse_software_info i={PULSE_SOFTWARE_ABI,sizeof(pulse_software_info),sizeof(State),1,4,0};return &i;}
PULSE_SW_EXPORT int PULSE_SW_CALL control_step(pulse_software_call*c){
 State*s=(State*)c->next_state;*s=*(const State*)c->previous_state;double now=c->time,edge=nextafter(now,INFINITY);
 if(c->trigger_flags&PULSE_SW_EXTERNAL)reload(s,c->inputs[0],now);
 if(c->trigger_flags&PULSE_SW_WAKEUP)
  for(int i=0;i<4;i++)if(s->at[i]>0 && s->at[i]<=edge){s->at[i]=0;set_leg(s,i/2,(i==1||i==2),now);}
 for(int i=0;i<4;i++){if(s->due[i]>0 && s->due[i]<=edge){s->due[i]=0;if(s->want[i])s->gate[i]=1;}c->outputs[i]=s->gate[i];}
 double next=INFINITY;for(int i=0;i<4;i++){if(s->at[i]>now && s->at[i]<next)next=s->at[i];if(s->due[i]>now && s->due[i]<next)next=s->due[i];}
 if(isfinite(next))c->next_delay=next-now;return 0;
}
