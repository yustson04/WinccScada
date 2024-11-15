#include "apdefap.h"

int gscAction( void )
{
unsigned int Cpu1ConnectionState, Cpu2ConnectionState, Cpu1ForceConnectionState, Cpu2ForceConnectionState ;
unsigned int dRedundantState,dRedundantState70, OpStatePrimaryCpu, OpStateStandbyCpu ;
char *PrimaryCpuAddress, *StandbyCpuAddress, *CurrentCpuAddress ;
char *PrimaryCpu70Address, *StandbyCpu70Address, *CurrentCpu70Address ;

/*      Check/Set Address of CPUs
    Confifured(Primary)
        Data type: Text tag 8-bit character set; length = 255
        Access: read
    Altanative(Standby)
        The tag must have a start value, for example:
        AccessPoint=abc;IPAddress=111.111.111.111;
        The value can be changed subsequently.
        Data type: Text tag 8-bit character set; length = 255
        Access: read / write
    CurrentCpu
        Data type: Text tag 8-bit character set; length = 255
        Access: read
*/
PrimaryCpuAddress = GetTagChar("@CPU1500RH_60@ConfiguredAddress") ;
SetTagChar("@CPU1500RH_60@AlternativeAddress","AccessPoint=S7ONLINE;IPAddress=192.168.0.70;");	//Return-Type: BOOL 
StandbyCpuAddress = GetTagChar("@CPU1500RH_60@AlternativeAddress") ;
CurrentCpuAddress = GetTagChar("@CPU1500RH_60@CurrentAddress") ;

printf("#####  CPU60 Tags#########\r\n");
printf("Primary Address is %s.\r\n", PrimaryCpuAddress);
printf("Standby Address is %s.\r\n", StandbyCpuAddress);
printf("Current CPU Address is %s.\r\n", CurrentCpuAddress);
printf("##########################\r\n");

PrimaryCpu70Address = GetTagChar("@CPU1500RH_70@ConfiguredAddress") ;
SetTagChar("@CPU1500RH_70@AlternativeAddress","AccessPoint=S7ONLINE;IPAddress=192.168.0.60;");	//Return-Type: BOOL 
StandbyCpu70Address = GetTagChar("@CPU1500RH_70@AlternativeAddress") ;
CurrentCpu70Address = GetTagChar("@CPU1500RH_70@CurrentAddress") ;

printf("#####  CPU70 Tags#########\r\n");
printf("Primary Address is %s.\r\n", PrimaryCpu70Address);
printf("Standby Address is %s.\r\n", StandbyCpu70Address);
printf("Current CPU Address is %s.\r\n", CurrentCpu70Address);
printf("##########################\r\n");



/*
	Set CPUs to Redundant mode
*/
//SetTagDouble("@CPU1500RH_60@RedundantCPUs",1);	//Return-Type: BOOL 
//SetTagDouble("@CPU1500RH_70@RedundantCPUs",1);	//Return-Type: BOOL 



/*  Check Connection State
    Start value = 1: The connection is established.
    Start value = 0: The connection remains deactivated.
    Data type: Unsigned 32-bit value
    Access: read / write
*/
Cpu1ForceConnectionState = (int)GetTagDouble("@CPU1500RH_60@ForceConnectionStateEx");
switch (Cpu1ForceConnectionState)
{
case 1:
    printf("CPU60 The connection is established.\r\n");
    break;

default:
    printf("CPU60 The connection remains deactivated.\r\n");
//	SetTagDouble("@CPU1500RH_70@ForceConnectionStateEx",1);
//	SetTagDouble("@CPU1500RH_70@UseAlternativeAddress",1);	//Return-Type: BOOL 

    break;
}
Cpu2ForceConnectionState = (int)GetTagDouble("@CPU1500RH_70@ForceConnectionStateEx");
switch (Cpu2ForceConnectionState)
{
case 1:
    printf("CPU70 The connection is established.\r\n");
    break;

default:
    printf("CPU70 The connection remains deactivated.\r\n");
//	SetTagDouble("@CPU1500RH_60@ForceConnectionStateEx",1);
	//use backup CPU
//	SetTagDouble("@CPU1500RH_60@UseAlternativeAddress",1);	//Return-Type: BOOL 

    break;
}


/*  
    1: The connection is ready for operation.
    0: The connection is interrupted or terminated.
    Data type: Unsigned 32-bit value
    Access: read
*/
Cpu1ConnectionState = (int)GetTagDouble("@CPU1500RH_60@ConnectionStateEx");
switch (Cpu1ConnectionState)
{
case 1:
    printf("CPU60 The connection is ready for operation.\r\n");
    break;

default:
    printf("CPU60 The connection is interrupted or terminated.\r\n");
	switch((int)GetTagDouble("@CPU1500RH_60@UseAlternativeAddress"))
	{
	case 0:
		SetTagDouble("@CPU1500RH_60@ForceConnectionStateEx",0);
		SetTagDouble("@CPU1500RH_60@UseAlternativeAddress",1);
		SetTagDouble("@CPU1500RH_60@ForceConnectionStateEx",1);
	break;
	case 1:
		SetTagDouble("@CPU1500RH_60@ForceConnectionStateEx",0);
		SetTagDouble("@CPU1500RH_60@UseAlternativeAddress",0);
		SetTagDouble("@CPU1500RH_60@ForceConnectionStateEx",1);
	break;	
	}
    break;
}

/*
Cpu2ConnectionState = (int)GetTagDouble("@CPU1500RH_70@ConnectionStateEx");
switch (Cpu2ConnectionState)
{
case 1:
    printf("CPU70 The connection is ready for operation.\r\n");
	SetTagDouble("@CPU1500RH_70@UseAlternativeAddress",0);

    break;

default:
    printf("CPU70 The connection is interrupted or terminated.\r\n");
//	SetTagDouble("@CPU1500RH_70@ForceConnectionStateEx",0);
	SetTagDouble("@CPU1500RH_70@UseAlternativeAddress",1);
//	SetTagDouble("@CPU1500RH_60@ForceConnectionStateEx",1);
    break;
}

*/



/*      Check Redundant or NOT
    1: Yes
    0: No, CPU is not redundant
    The tag must have a start value.
    The value can be changed subsequently.
    Data type: Unsigned 32-bit value
    Access: read / write
*/
dRedundantState =  (int)GetTagDouble("@CPU1500RH_60@RedundantCPUs");
switch (dRedundantState)
{
case 1:
    printf("CPU60 is Redundant\r\n");
    break;

default:
    printf("CPU60 is NOT Redundant\r\n");
    break;
}

dRedundantState70 =  (int)GetTagDouble("@CPU1500RH_70@RedundantCPUs");
switch (dRedundantState70)
{
case 1:
    printf("CPU70 is Redundant\r\n");
    break;

default:
    printf("CPU70 is NOT Redundant\r\n");
    break;
}



/*  Check CPU Mode
        0: not connected
        4: STOP
        6: STARTUP
        8: RUN
        22: SYNCUP
        Data type: Unsigned 32-bit value
        Access: read
*/
OpStatePrimaryCpu = (int)GetTagDouble("@CPU1500RH_60@OpStateConfiguredAddress");
switch (OpStatePrimaryCpu)
{
    case 0:
    printf("CPU1 is not connected\r\n");
    break;

    case 4:
    printf("CPU1 is stopped\r\n");
    break;

    case 6:
    printf("CPU1 is starting up\r\n");
    break;

    case 8:
    printf("CPU1 is running\r\n");
    break;

    case 22:
    printf("CPU1 is in syncup status\r\n");
    break;

default:
    printf("CPU1 state is unknown\r\n");
    break;
}

OpStateStandbyCpu = (int)GetTagDouble("@CPU1500RH_60@OpStateAlternativeAddress");
switch (OpStateStandbyCpu)
{
case 0:
    printf("CPU2 is not connected\r\n");
    break;

    case 4:
    printf("CPU2 is stopped\r\n");
    break;

    case 6:
    printf("CPU2 is starting up\r\n");
    break;

    case 8:
    printf("CPU2 is running\r\n");
    break;

    case 22:
    printf("CPU2 is in syncup status\r\n");
    break;

default:
    printf("CPU2 state is unknown\r\n");
    break;
}

return 0; 
}