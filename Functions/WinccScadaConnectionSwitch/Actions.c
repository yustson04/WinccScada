#include "apdefap.h"

int gscAction( void )
{
/*  My Project Parameter   
                CPU1: PLC_60,                      CPU2: PLC_70
    IP:         192.168.0.60                       192.168.0.70
    1Hz clock   m10.5                              m10.5
    WinccTag    @CPU1500RH_60@AlivePuls            @CPU1500RH_70@AlivePuls
*/
 
 // Siemens Manual
 // https://support.industry.siemens.com/cs/mdm/109772961?c=127349029387&lc=fr-MA

 /*         Initial situation
    The WinCC project is in Runtime.
    The connection "PLC1" to the primary CPU is active.
    The system tag "@<PLC1>@AlternativeAddress" contains the valid address of the backup CPU, for example:
    - AccessPoint=abc;
    IPAddress=111.111.111.111;
 */

/*      Connection fault
    1. The loss of connection is determined via the tag "@<PLC1>@ConnectionState".
    2. The connection is deactivated:
        - @<PLC1>@ForceConnectionState = 0
    3. The connection parameters are changed:
        - @<PLC1>@UseAlternativeAddress = 1
    4. The connection is re-established:
        - @<PLC1>@ForceConnectionState = 1
    5. WinCC establishes the alternative connection to the backup CPU.
*/

/*      System Tags for software redundancy
Tagname                             Use                                         Value                   Explanation
@<...>@ForceConnectionState         Establish / terminate redundant connection  1 / 0                   Behavior when runtime is activated:
                                                                                                        Start value = 1: The connection is established.
                                                                                                        Start value = 0: The connection remains deactivated.
                                                                                                        Data type: Unsigned 32-bit value
                                                                                                        Access: read / write
@<...>@ConnectionState              Redundant connection status                 1 / 0                   Querying of the connection status:
                                                                                                        1: The connection is ready for operation.
                                                                                                        0: The connection is interrupted or terminated.
                                                                                                        The tags of the connection are not archived.
                                                                                                        Data type: Unsigned 32-bit value
                                                                                                        Access: read
@<...>@ConfiguredAddress            Connection to the primary CPU               String                  Properties of the connection that is configured in the Tag Management
                                                                                                        Data type: Text tag 8-bit character set; length = 255
                                                                                                        Access: read
@<...>@AlternativeAddress           Connection to the backup CPU                String                  Properties of the alternative connection to the backup CPU
                                                                                                        The tag must have a start value, for example:
                                                                                                        AccessPoint=abc;IPAddress=111.111.111.111;
                                                                                                        The value can be changed subsequently.
                                                                                                        Data type: Text tag 8-bit character set; length = 255
                                                                                                        Access: read / write
@<...>@CurrentAddress               Current address                             String                  Properties of the currently used connection
                                                                                                        Data type: Text tag 8-bit character set; length = 255
                                                                                                        Access: read
@<...>@UseAlternativeAddress        Use an alternative connection               1 / 0                   Determines the currently used connection:
                                                                                                        1: Alternative connection to backup CPU
                                                                                                        0: Connection to the primary CPU
                                                                                                        Data type: Unsigned 32-bit value
                                                                                                        Access: read / write
@<...>@RedundantCPUs                Redundancy active                           1 / 0                   Indicates whether the connected controller is redundant:
                                                                                                        1: Yes
                                                                                                        0: No, CPU is not redundant
                                                                                                        The tag must have a start value.
                                                                                                        The value can be changed subsequently.
                                                                                                        Data type: Unsigned 32-bit value
                                                                                                        Access: read / write
@<...>@OpStateConfiguredAddress     Operating mode of the primary CPU           0 / 4 / 6 / 8 / 22      Operating modes of the controller:
@<...>@OpStateAlternativeAddress    Operating mode of the backup CPU                                    0: not connected
                                                                                                        4: STOP
                                                                                                        6: STARTUP
                                                                                                        8: RUN
                                                                                                        22: SYNCUP
                                                                                                        Data type: Unsigned 32-bit value
                                                                                                        Access: read

*/
int iDummy;
iDummy=0;


return 0; 
}