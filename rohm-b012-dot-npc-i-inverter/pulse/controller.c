#include "pulse/software.h"
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
#define PAIRS 9
#define GATES 18
#define HALF 0.00005L
#define DEAD 0.000001
#define PI 3.141592653589793238462643383279502884L
/* Group order: each phase upper carrier, lower carrier, sine-sign. */
typedef struct { uint64_t tick; double start; int raw[PAIRS],gate[GATES],want[GATES],initialized; double due[GATES],root[PAIRS]; } State;
static long double sine_at(uint64_t tick, long double dt, int phase) {
  uint64_t reduced=tick%400; long double cycles=(long double)reduced/400.0L+dt/0.02L;
  if(phase==0 && dt==0 && (reduced%200)==0) return 0;
  long double shift=phase==0?0:(phase==1?2*PI/3:-2*PI/3);
  return 0.8L*sinl(2*PI*cycles+shift);
}
static long double guard(uint64_t tick,long double dt,int group) {
 int phase=group/3,kind=group%3;long double s=sine_at(tick,dt,phase);
 if(kind==2)return s;
 long double tri=(tick%2==0)?dt/HALF:1-dt/HALF;
 return s-(kind==0?tri:tri-1);
}
static int side(uint64_t tick,int g,int at_end) {
 long double t=at_end?HALF:0, v=guard(tick,t,g);
 /* Exact phase-A half-cycle roots are structural, not a numeric epsilon. */
 uint64_t endpoint=tick+(at_end?1:0);
 if(g/3==0 && endpoint%200==0 && ((g%3==2)||((g%3==0)&&(endpoint%2==0))||((g%3==1)&&(endpoint%2==1))))v=0;
 if(v>0)return 1;if(v<0)return 0;
 long double tmid=at_end?HALF/2:HALF/2;return guard(tick,tmid,g)>0;
}
static void set_raw(State*s,int g,int value,double now) {
 if(s->initialized && s->raw[g]==value)return;
 s->raw[g]=value;
 for(int k=0;k<2;k++){int i=2*g+k,desired=(k==0)?value:!value;
  if(!desired){s->want[i]=0;s->gate[i]=0;s->due[i]=0;}
  else if(!s->want[i]){s->want[i]=1;s->gate[i]=0;s->due[i]=now+DEAD;}
 }
}
static void schedule_half(State*s,double now) {
 uint64_t tick=s->tick; s->start=now;
 for(int g=0;g<PAIRS;g++){
  int left=side(tick,g,0),right=side(tick,g,1);set_raw(s,g,left,now);s->root[g]=0;
  if(left!=right){long double lo=0,hi=HALF;
   for(int j=0;j<90;j++){long double mid=(lo+hi)/2;if(mid==lo||mid==hi)break;int v=guard(tick,mid,g)>0;if(v==left)lo=mid;else hi=mid;}
   double offset=(double)((lo+hi)/2);if(offset>0 && offset<(double)HALF)s->root[g]=now+offset;
  }
 }
 s->initialized=1;s->tick++;
}
PULSE_SW_EXPORT const pulse_software_info *PULSE_SW_CALL pulse_software_describe(void){static const pulse_software_info i={PULSE_SOFTWARE_ABI,sizeof(pulse_software_info),sizeof(State),0,GATES,0};return &i;}
PULSE_SW_EXPORT int PULSE_SW_CALL control_step(pulse_software_call*c){
 State*s=(State*)c->next_state;*s=*(const State*)c->previous_state;double now=c->time;
 if(c->trigger_flags&PULSE_SW_EXTERNAL)schedule_half(s,now);
 if(c->trigger_flags&PULSE_SW_WAKEUP){
  double edge=nextafter(now,INFINITY);
  for(int g=0;g<PAIRS;g++)if(s->root[g]>0 && s->root[g]<=edge){s->root[g]=0;set_raw(s,g,!s->raw[g],now);}
 }
 /* External halfclock can coincide with a pending turn-on deadline.
    Update raw desires first, then honor still-valid due gates. */
 double edge=nextafter(now,INFINITY);
 for(int i=0;i<GATES;i++)if(s->due[i]>0 && s->due[i]<=edge){s->due[i]=0;if(s->want[i])s->gate[i]=1;}
 for(int i=0;i<GATES;i++)c->outputs[i]=(double)s->gate[i];
 double next=INFINITY,stop=s->start+(double)HALF;
 for(int g=0;g<PAIRS;g++)if(s->root[g]>now && s->root[g]<stop && s->root[g]<next)next=s->root[g];
 for(int i=0;i<GATES;i++)if(s->due[i]>now && s->due[i]<stop && s->due[i]<next)next=s->due[i];
 if(isfinite(next))c->next_delay=next-now;
 return 0;
}
