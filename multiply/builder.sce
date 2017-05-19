files=["sci_multiply.c"];
// TODO: WTF ?
WITHOUT_AUTO_PUTLHSVAR = %t;
ilib_build('build_lib',['multiply','sci_multiply'],files,[]);
exec loader.sce
c = multiply([2, 2] , [2, 2; 2, 2])
