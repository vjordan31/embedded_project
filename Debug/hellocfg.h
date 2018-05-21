/*   Do *not* directly modify this file.  It was    */
/*   generated by the Configuration Tool; any  */
/*   changes risk being overwritten.                */

/* INPUT hello.cdb */

/*  Include Header Files  */
#include <std.h>
#include <prd.h>
#include <hst.h>
#include <swi.h>
#include <tsk.h>
#include <log.h>
#include <sem.h>
#include <sts.h>

#ifdef __cplusplus
extern "C" {
#endif

extern far PRD_Obj dipStatusPRD;
extern far PRD_Obj systemOnBufferLEDPRD;
extern far PRD_Obj systemBufferPlaybackLEDPRD;
extern far PRD_Obj systemFilBufferPlaybackLEDPRD;
extern far HST_Obj RTA_fromHost;
extern far HST_Obj RTA_toHost;
extern far SWI_Obj PRD_swi;
extern far SWI_Obj KNL_swi;
extern far TSK_Obj TSK_idle;
extern far LOG_Obj LOG_system;
extern far LOG_Obj trace;
extern far SEM_Obj dipMonitorSem;
extern far SEM_Obj systemOnBufferLEDSem;
extern far SEM_Obj systemBufferPlaybackLEDSem;
extern far SEM_Obj systemFilBufferPlaybackLEDSem;
extern far STS_Obj IDL_busyObj;


#ifdef __cplusplus
}
#endif /* extern "C" */
