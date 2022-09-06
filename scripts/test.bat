set /p content=<rsrc/buildnumber.txt
set /A content=content+1
(echo %content%)>rsrc/buildnumber2.txt
cd rsrc
del buildnumber.txt
rename buildnumber2.txt buildnumber.txt

cd %BPP_ROOT%