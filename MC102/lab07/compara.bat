@REM comando1 || comando2 -> se 1 falhar, roda 2
@REM comando1 && comando2 -> se 1 der certo, roda 2
@REM comando1 & comando2 -> roda 1 e roda 2
@for /L %%i in (1,1,6) do @fc arq0%%i.out arq0%%i.res || (Echo Erro! & goto end)
:end
@pause