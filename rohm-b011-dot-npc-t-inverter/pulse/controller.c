#include "pulse/software.h"
#include <math.h>
#include <stdint.h>
#define PI 3.141592653589793238462643383279502884L
#define HALF 0.00005L
#define DEAD 0.000001
/* Manufacturer B011: natural, minimum-start carrier; negative carrier flipped.
   Three-level s=(m>=positive)-(m<=negative).
   U/V/W outputs: [s>0,s>=0,s<=0,s<0], each with turn-on delay.
   Roots are solved on monotone half-carrier segments, never sampled at SAVE_DT.
   Equality at a zero-width contact uses its right-hand state; no injected pulse. */
typedef struct {
 uint64_t half;
 double start,root[6],due[12];
 int cmp[6],want[12],gate[12];
} State;
static long double guard(uint64_t half,long double dt,int i) {
 int phase=i/2;
 long double angle=2*PI*((long double)(half%400)/400+dt/.02L+(long double)phase/3);
 long double m=.8L*sinl(angle),tri=(half%2)?1-dt/HALF:dt/HALF;
 /* Preserve exact mathematical sine zeros at carrier boundaries using integer
    phase arithmetic (400 half-carriers per fundamental period, thirds phases).
    This chooses the mathematical contact; it does not insert a gate event. */
 if((dt==0 || dt==HALF) && ((3*((half+(dt==HALF))%400)+400*phase)%600)==0)m=0;
 return m+(i%2?tri:-tri);
}
static int side(uint64_t half,int i,int end) {
 long double v=guard(half,end?HALF:0,i);
 if(v==0)v=guard(half,HALF/2,i);
 return v>0;
}
static void desires(State*s,double now) {
 for(int p=0;p<3;p++) {
  int level=s->cmp[2*p]-(1-s->cmp[2*p+1]);
  int a[4]={level>0,level>=0,level<=0,level<0};
  for(int k=0;k<4;k++) {
   int i=4*p+k;
   if(!a[k]) {s->gate[i]=0;s->want[i]=0;s->due[i]=0;}
   else if(!s->want[i]) {s->want[i]=1;s->due[i]=now+DEAD;}
  }
 }
}
static void schedule(State*s,double now) {
 uint64_t h=s->half;s->start=now;
 for(int i=0;i<6;i++) {
  int l=side(h,i,0),rr=side(h,i,1);s->cmp[i]=l;s->root[i]=0;
  if(l!=rr) {
   long double lo=0,hi=HALF;
   for(int j=0;j<90;j++) {
    long double mid=(lo+hi)/2;if(mid==lo||mid==hi)break;
    if((guard(h,mid,i)>0)==l)lo=mid;else hi=mid;
   }
   double off=(double)((lo+hi)/2);
   if(off>0 && off<(double)HALF)s->root[i]=now+off;
  }
 }
 s->half++;
}
PULSE_SW_EXPORT const pulse_software_info *PULSE_SW_CALL pulse_software_describe(void) {
 static const pulse_software_info info={PULSE_SOFTWARE_ABI,sizeof(pulse_software_info),sizeof(State),0,12,0};return &info;
}
PULSE_SW_EXPORT int PULSE_SW_CALL control_step(pulse_software_call*c) {
 State*s=(State*)c->next_state;*s=*(const State*)c->previous_state;
 double now=c->time,edge=nextafter(now,INFINITY);
 if(c->trigger_flags&PULSE_SW_EXTERNAL)schedule(s,now);
 if(c->trigger_flags&PULSE_SW_WAKEUP)
  for(int i=0;i<6;i++)if(s->root[i]>0 && s->root[i]<=edge){s->cmp[i]=!s->cmp[i];s->root[i]=0;}
 desires(s,now);
 for(int i=0;i<12;i++) {
  if(s->due[i]>0 && s->due[i]<=edge){s->due[i]=0;if(s->want[i])s->gate[i]=1;}
  c->outputs[i]=s->gate[i];
 }
 double next=INFINITY,stop=s->start+(double)HALF;
 for(int i=0;i<6;i++)if(s->root[i]>now && s->root[i]<stop && s->root[i]<next)next=s->root[i];
 for(int i=0;i<12;i++)if(s->due[i]>now && s->due[i]<stop && s->due[i]<next)next=s->due[i];
 if(isfinite(next))c->next_delay=next-now;
 return 0;
}
