
ezSealps.dll: dlldata.obj ezSeal_p.obj ezSeal_i.obj
	link /dll /out:ezSealps.dll /def:ezSealps.def /entry:DllMain dlldata.obj ezSeal_p.obj ezSeal_i.obj \
		mtxih.lib mtx.lib mtxguid.lib \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
		ole32.lib advapi32.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		/MD \
		$<

clean:
	@del ezSealps.dll
	@del ezSealps.lib
	@del ezSealps.exp
	@del dlldata.obj
	@del ezSeal_p.obj
	@del ezSeal_i.obj
