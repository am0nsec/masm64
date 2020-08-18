@echo off

ml64.exe /c /Zi /Fo"ListPolicies.obj" /W3 /errorReport:prompt ListPolicies.asm
link.exe /ERRORREPORT:PROMPT /INCREMENTAL:NO /DEBUG /SUBSYSTEM:CONSOLE /OPT:NOREF /OPT:NOICF /ENTRY:"ListPolicies" /DYNAMICBASE /NXCOMPAT /MACHINE:X64 /SAFESEH:NO ListPolicies.obj kernel32.lib ole32.lib
