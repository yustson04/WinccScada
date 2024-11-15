Sub connection_lost()

'**********************************************************************************************
'****   	    	VB Script for connecting a Comfort Panel to an H-System   			   ****
'****                           Author: André Blochwitz                                    ****
'****                         Part 3 / 3 - connection lost                                 ****
'**********************************************************************************************

'Deactivation / Deaktivierung
'If the connections are not able to reset there status tag back to "1" they will be marked with 100 (disabled).
'Setzen die Verbindungen ihren Status nicht zyklisch auf 1 zurück werden sie als ausgefallen markiert

If SmartTags("con_state_PLC1") >= 5 Then
	SmartTags("con_state_PLC1") = 100
End If

If SmartTags("con_state_PLC2") >= 5 Then
	SmartTags("con_state_PLC2") = 100
End If

'If both connections are marked with "disabled", the connection memory will be set to "connection_lost" 
'Sind beide Verbindungen als deaktiviert gekennzeichnet, wird der Verbindungsspeicher der Datenverbindung entsprechend mit "connection_lost" beschrieben 

If SmartTags("con_state_PLC1") = 100 And SmartTags("con_state_PLC2") = 100 Then
	SmartTags("connected_to") = "connection lost"
End If


'Setting fault flag / Störungsmarkierung 
'In each cycle of 1 minute the status tags of the connections will be set to 5.
'Im Zyklus von 1 Minute werden die Statusvariablen der beiden Verbindungen auf 5 gesetzt

If SmartTags("con_state_PLC1") < 5 Then
	SmartTags("con_state_PLC1") = 5
End If

If SmartTags("con_state_PLC2") < 5 Then
	SmartTags("con_state_PLC2") = 5
End If

End Sub