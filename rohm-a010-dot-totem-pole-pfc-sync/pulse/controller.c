#include "pulse/software.h"
#include <math.h>
#include <stdint.h>
#include "transition.h"
#define PI 3.141592653589793238462643383279502884L
#define TS (1.0L/60000.0L)
typedef struct {
 uint64_t sample;
 long double q,p,integral,error,old_pi,old_b,old_sin,old_cos,held_i;
 double hf_edge[2],due[4],pi_out,pr_out,modulation;
 int want[4],gate[4];
} State;
static void want(State*s,int i,int on,double now) {
 if(!on){s->want[i]=0;s->gate[i]=0;s->due[i]=0;}
 else if(!s->want[i]){s->want[i]=1;s->gate[i]=0;s->due[i]=now+(i<2?2e-7:1e-7);}
}
static void hf(State*s,int positive,double now) {want(s,0,positive,now);want(s,1,!positive,now);}
static void sample(State*s,const double*in,double now) {
 uint64_t k=s->sample++;
 if(k) {
  long double z[7]={s->q,s->p,s->old_pi*s->old_sin,s->old_pi*s->old_cos,s->old_b*s->old_sin,s->old_b*s->old_cos,s->held_i};
  long double q=0,p=0;for(int j=0;j<7;j++){q+=T_PR[0][j]*z[j];p+=T_PR[1][j]*z[j];}
  s->q=q;s->p=p;s->integral+=s->old_b*TS;
 }
 if(k%50==0)s->error=500.0L-in[0];
 long double pi=.012L*s->error+s->integral;
 long double e=pi*((long double)in[2]/220.0L)-(long double)in[1];
 long double pr=19.8L*e+s->p;
 int positive=(k%1200)<600;
 long double vdc=fmaxl((long double)in[0],200.0L);
 long double mod=2*((long double)in[2]-pr)/vdc+(positive?-1:1);
 mod=fmaxl(-1,fminl(1,mod));
 s->pi_out=(double)pi;s->pr_out=(double)pr;s->modulation=(double)mod;
 long double phase=2*PI*(long double)(k%1200)/1200;
 s->old_pi=pi;s->old_b=7.2L*s->error;s->held_i=in[1];s->old_sin=sqrtl(2)*sinl(phase);s->old_cos=sqrtl(2)*cosl(phase);
 s->hf_edge[0]=s->hf_edge[1]=0;
 hf(s,mod>=1,now);
 if(mod>-1 && mod<1){double off=(double)(TS*(1-mod)/4);s->hf_edge[0]=now+off;s->hf_edge[1]=now+(double)TS-off;}
 want(s,2,!positive,now);want(s,3,positive,now);
}
PULSE_SW_EXPORT const pulse_software_info *PULSE_SW_CALL pulse_software_describe(void) {
 static const pulse_software_info info={PULSE_SOFTWARE_ABI,sizeof(pulse_software_info),sizeof(State),3,7,0};return &info;
}
PULSE_SW_EXPORT int PULSE_SW_CALL control_step(pulse_software_call*c) {
 State*s=(State*)c->next_state;*s=*(const State*)c->previous_state;double now=c->time,edge=nextafter(now,INFINITY);
 if(c->trigger_flags&PULSE_SW_EXTERNAL)sample(s,c->inputs,now);
 if(c->trigger_flags&PULSE_SW_WAKEUP){
  if(s->hf_edge[0]>0 && s->hf_edge[0]<=edge){s->hf_edge[0]=0;hf(s,1,now);}
  if(s->hf_edge[1]>0 && s->hf_edge[1]<=edge){s->hf_edge[1]=0;hf(s,0,now);}
 }
 for(int i=0;i<4;i++){if(s->due[i]>0 && s->due[i]<=edge){s->due[i]=0;if(s->want[i])s->gate[i]=1;}c->outputs[i]=s->gate[i];}
 c->outputs[4]=s->pi_out;c->outputs[5]=s->pr_out;c->outputs[6]=s->modulation;
 double next=INFINITY;
 for(int i=0;i<2;i++)if(s->hf_edge[i]>now && s->hf_edge[i]<next)next=s->hf_edge[i];
 for(int i=0;i<4;i++)if(s->due[i]>now && s->due[i]<next)next=s->due[i];
 if(isfinite(next))c->next_delay=next-now;
 return 0;
}
