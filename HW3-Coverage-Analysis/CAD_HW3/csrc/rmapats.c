// file = 0; split type = patterns; threshold = 100000; total count = 0.
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "rmapats.h"

void  hsG_0__0 (struct dummyq_struct * I1286, EBLK  * I1280, U  I683);
void  hsG_0__0 (struct dummyq_struct * I1286, EBLK  * I1280, U  I683)
{
    U  I1544;
    U  I1545;
    U  I1546;
    struct futq * I1547;
    struct dummyq_struct * pQ = I1286;
    I1544 = ((U )vcs_clocks) + I683;
    I1546 = I1544 & ((1 << fHashTableSize) - 1);
    I1280->I725 = (EBLK  *)(-1);
    I1280->I729 = I1544;
    if (I1544 < (U )vcs_clocks) {
        I1545 = ((U  *)&vcs_clocks)[1];
        sched_millenium(pQ, I1280, I1545 + 1, I1544);
    }
    else if ((peblkFutQ1Head != ((void *)0)) && (I683 == 1)) {
        I1280->I731 = (struct eblk *)peblkFutQ1Tail;
        peblkFutQ1Tail->I725 = I1280;
        peblkFutQ1Tail = I1280;
    }
    else if ((I1547 = pQ->I1187[I1546].I743)) {
        I1280->I731 = (struct eblk *)I1547->I742;
        I1547->I742->I725 = (RP )I1280;
        I1547->I742 = (RmaEblk  *)I1280;
    }
    else {
        sched_hsopt(pQ, I1280, I1544);
    }
}
#ifdef __cplusplus
extern "C" {
#endif
void SinitHsimPats(void);
#ifdef __cplusplus
}
#endif
