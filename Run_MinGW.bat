pushd %~dp0build_MinGW\
call make_lu.exe
call lu_gauss.exe
call make_qr.exe
call qr_gauss.exe
call find_poly.exe
PAUSE