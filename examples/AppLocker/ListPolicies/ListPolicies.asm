; @file        ListPolicies.asm
; @date        18-08-2020
; @author      Paul Laîné (@am0nsec)
; @version     1.0
; @brief       List AppLocker policies.
; @details	
; @link        
; @copyright   This project has been released under the GNU Public License v3 license.

INCLUDE applocker.inc
INCLUDE kernel32.inc

_DATA$00 SEGMENT PAGE 'DATA'
	pIAppIdPolicyHandler          IAppIdPolicyHandler <>
    bstrPolicies                  BSTR ?

	hConsoleOutput                QWORD ?
	NumberOfCharsWritten          QWORD ?
	dwStringSize                  DWORD ?
	bResult                       BYTE 0h

	IIDIAppIdPolicyHandler        IID_IAppIdPolicyHandler <>
	CLSIDAppIdPolicyHandlerClass  CLSID_AppIdPolicyHandlerClass <>
	
	STD_OUTPUT_HANDLE             DWORD -11
_DATA$00 ENDS

_TEXT$00 SEGMENT ALIGN(10h) 'CODE'

	ListPolicies PROC
		push rbp     ; Frame pointer
		mov rbp, rsp ; Stack pointer
		sub rsp, 30h ; Room for shadow stack

;--------------------------------------------------------------------------------------------------
; Initialise COM
;--------------------------------------------------------------------------------------------------
		xor rcx, rcx      ; pvReserved = NULL
		and rsp, not 8    ; Shadow stack alignment
		call CoInitialize ;

		cmp rax, 00h      ; if (RAX != S_OK)
		jne _failure      ;
		
;--------------------------------------------------------------------------------------------------
; Get pointer to IAppIdPolicyHandler interface
;--------------------------------------------------------------------------------------------------
		lea rcx, CLSIDAppIdPolicyHandlerClass     ; rclsid
		xor rdx, rdx                              ; pUnkOuter
		mov r8, 1h                                ; dwClsContext
		lea r9, IIDIAppIdPolicyHandler            ; riid
		lea rax, pIAppIdPolicyHandler             ;
		mov qword ptr [rsp + 20h], rax            ; ppv
		and rsp, not 8                            ; Shadow stack alignment
		call CoCreateInstance                     ;

		cmp rax, 00h                              ; if (rax != S_OK)
		jne _failure                              ;
		cmp qword ptr [pIAppIdPolicyHandler], 00h ; if (pIAppIdPolicyHandler != NULL) 
		je _failure                               ;

		mov rax, [pIAppIdPolicyHandler]           ; 
		mov rax, qword ptr [rax]                  ; Dereference pointer
		mov pIAppIdPolicyHandler.lpVtbl, rax      ; Fix virtual table

;--------------------------------------------------------------------------------------------------
;  Get effective policies
;--------------------------------------------------------------------------------------------------
		mov rcx, pIAppIdPolicyHandler                        ; This
		lea rdx, bstrPolicies                                ; pbstrXmlPolicies

		and rsp, not 8                                       ; Shadow stack alignment
		mov rax, pIAppIdPolicyHandler.lpVtbl                 ; Address of the function in interface
		call [rax].AppIdPolicyHandlerVtbl.GetEffectivePolicy ; 
		cmp rax, 00h                                         ; if (RAX != S_OK)
		jne _failure                                         ;

;--------------------------------------------------------------------------------------------------
;  Get handle to console for I/O
;--------------------------------------------------------------------------------------------------
		mov ecx, -11            ; nStdHandle = STD_OUTPUT_HANDLE 
		and rsp, not 8          ; Shadow stack alignment
		call GetStdHandle       ;

		cmp rax, 00h            ; if (RAX != NULL)
		je _failure             ;
		mov hConsoleOutput, rax ;

;--------------------------------------------------------------------------------------------------
;  Get size of string
;--------------------------------------------------------------------------------------------------
		mov rcx, bstrPOlicies ; lpString
		and rsp, not 8        ; Shadow stack alignment
		call lstrlenW         ;

		cmp rax, 00h          ; if (RAX != 0)
		je _failure           ;
		mov dwStringSize, eax ;

;--------------------------------------------------------------------------------------------------
;  Display AppLocker policies to console
;--------------------------------------------------------------------------------------------------
		mov rcx, hConsoleOutput        ; hConsoleOutput
		mov rdx, bstrPolicies          ; lpBuffer
		mov r8d, dwStringSize          ; nNumberOfCharsToWrite
		lea r9, NumberOfCharsWritten   ; lpNumberOfCharsWritten
		mov qword ptr [rsp + 20h], 00h ; lpReserved

		and rsp, not 8                 ; Shadow stack alignment
		call WriteConsoleW             ;

		mov bResult, 1h                ; return TRUE

;--------------------------------------------------------------------------------------------------
;  Exit & Cleanup
;--------------------------------------------------------------------------------------------------
_failure:
		cmp hConsoleOutput, 00h ; if (hConsoleOutput != NULL)
		je $ + 12h              ;
		mov rcx, hConsoleOutput ; hObject
		and rsp, not 8          ; Shadow stack alignment
		call CloseHandle        ;

		and rsp, not 8          ; Shadow stack alignment
		call CoUninitialize     ;
_prologue:
		xor rax, rax
		mov al, bResult         ; 
		mov rsp, rbp            ;
		pop rbp                 ;
		ret                     ;
	ListPolicies ENDP

_TEXT$00 ENDS

END
