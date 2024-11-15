'VBS381
Option Explicit
Function action
  
    Dim C1ConnectionState
    Set C1ConnectionState = HMIRuntime.Tags("@Connection1@ConnectionState")
    C1ConnectionState.Read
  
    Dim C1OpStateConfiguredAddress
    Set C1OpStateConfiguredAddress = HMIRuntime.Tags("@Connection1@OpStateConfiguredAddress")
    C1OpStateConfiguredAddress.Read
  
    Dim C1OpStateAlternativeAddress
    Set C1OpStateAlternativeAddress = HMIRuntime.Tags("@Connection1@OpStateAlternativeAddress")
    C1OpStateAlternativeAddress.Read
  
    Dim C1UseAlternativeAddress
    Set C1UseAlternativeAddress = HMIRuntime.Tags("@Connection1@UseAlternativeAddress")
    C1UseAlternativeAddress.Read
  
    Dim C1ForceConnectionState
    Set C1ForceConnectionState = HMIRuntime.Tags("@Connection1@ForceConnectionState")
    C1ForceConnectionState.Read
  
  
  'check if connection got disconnected
    If C1ConnectionState.Value = 0  Then
  'set force connection state = 0
        C1ForceConnectionState.Value = 0
        C1ForceConnectionState.Write
  
  'switch between plc1 and plc2
        Select Case C1UseAlternativeAddress.Value
  
            Case 0
                    C1UseAlternativeAddress.Value = 1
                    C1UseAlternativeAddress.Write
            Case 1
                    C1UseAlternativeAddress.Value = 0
                    C1UseAlternativeAddress.Write
  
        End Select
  
  'reconnect
        C1ForceConnectionState.Value = 1
        C1ForceConnectionState.Write
  
  
  'example for handling operating states: stop mode
  'check if plc is in stop mode; stop mode does not deliver connectionstate = 0
    Elseif (C1OpStateConfiguredAddress.Value = 4 And C1UseAlternativeAddress.Value = 0) Or (C1OpStateAlternativeAddress.Value = 4 And C1UseAlternativeAddress.Value = 1) Then
  
  'set force connection state = 0
        C1ForceConnectionState.Value = 0
        C1ForceConnectionState.Write
  
  'switch between plc1 and plc2
        Select Case C1UseAlternativeAddress.Value
  
            Case 0
                    C1UseAlternativeAddress.Value = 1
                    C1UseAlternativeAddress.Write
            Case 1
                    C1UseAlternativeAddress.Value = 0
                    C1UseAlternativeAddress.Write
  
        End Select
  
  'reconnect
        C1ForceConnectionState.Value = 1
        C1ForceConnectionState.Write
  
    Else
  
    End If
  
Set C1ConnectionState = Nothing
Set C1OpStateConfiguredAddress = Nothing
Set C1OpStateAlternativeAddress = Nothing
Set C1UseAlternativeAddress = Nothing
Set C1ForceConnectionState = Nothing
  
End Function