Sub connection_PLC1()

'**********************************************************************************************
'****   	    	VB Script for connecting a Comfort Panel to an H-System   			   ****
'****                           Author: André Blochwitz                                    ****
'****                         Part 3 / 3 - connection lost                                 ****
'**********************************************************************************************


'Initialization / Initialisierung
'During initialization the default connection is saved into the memory of connections (connected_to). 
'bei der Initialisierung wird die default - Verbindung in den Verbindungsspeicher gesichert (connected_to). 

If SmartTags("connected_to") = "" Then
	SmartTags("connected_to") = "Connected with PLC 1"
End If


'Reset / Rücksetzen
'Reset of connection brake detection for PLC_1
'Rücksetzen der Verbindungsausfallerkennung für PLC_1

SmartTags("con_state_PLC1") = 1


'Fault detection / Störungserkennung
'Incrementation of the brake detection value for the connection to PLC_2
'Inkrementieren der Ausfallerkennung für die Verbindung zu PLC_2

If SmartTags("con_state_PLC2") <= 10 Then
	SmartTags("con_state_PLC2") = SmartTags("con_state_PLC2") +1
End If


' Switch over / Umschalten
'is the limit of the status tag for the connection to PLC_2 reached, the connection to PLC_1 will switch the data connection.
'Erreicht die Statusvariable für die Verbindung zu PLC2 einen Grenzwert, schaltet die Verbindung zu PLC1 die Datenverbindung auf Ihre Parameter um

If SmartTags("con_state_PLC2") >= 11 Then
	If SmartTags("connected_to") = "Connected with PLC 2" Then
		ChangeConnection "Connection12", "192.168.0.100", 1, 0
		SmartTags("con_state_PLC2") = 100
		SmartTags("connected_to") = "Connected with PLC 1"
	ElseIf SmartTags("connected_to") = "Connected with PLC 1" Then
		SmartTags("con_state_PLC2") = 100
	End If
End If


'Reintegration / Wiedereintritt
'after a full connection brake the first repaired connection will activate the data connection
'Nach einem Totalausfall wird die Datenverbindung auf die Paramter der Verbindung umgeschalten, über die als erstes das Taktmerkerbit gelesen werden kann

If SmartTags("connected_to") = "connection lost" Then
	ChangeConnection "Connection12", "192.168.0.100", 1, 0
	SmartTags("con_state_PLC2") = 100
	SmartTags("connected_to") = "Connected with PLC 1"
End If

End Sub