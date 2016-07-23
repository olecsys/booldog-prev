@set bat_dir=%~dp0
@set path_to_copy=%bat_dir%..\core\inc\booldog

@if not exist "%path_to_copy%" @md "%path_to_copy%"

@xcopy /e /v /q /r /y "%bat_dir%include" "%path_to_copy%"

@echo Copy files to %path_to_copy% success


@set path_to_copy=%bat_dir%..\core\TESTS\booldog

@copy /Y /V "%bat_dir%test\"*.bat "%path_to_copy%"

@copy /Y /V "%bat_dir%test\"*.sh "%path_to_copy%"

@copy /Y /V "%bat_dir%test\"*.vcxproj "%path_to_copy%"

@copy /Y /V "%bat_dir%test\"*.ruxprj "%path_to_copy%"

@xcopy /e /v /q /r /y "%bat_dir%test\src" "%path_to_copy%\src"

@xcopy /e /v /q /r /y "%bat_dir%test_data" "%path_to_copy%\..\test_data"


@set path_to_copy=%bat_dir%..\rux\extern_includes\booldog

@if not exist "%path_to_copy%" @md "%path_to_copy%"

@xcopy /e /v /q /r /y "%bat_dir%include" "%path_to_copy%"

@echo Copy files to %path_to_copy% success