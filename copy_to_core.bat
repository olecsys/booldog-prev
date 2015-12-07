@set bat_dir=%~dp0
@set path_to_copy=%bat_dir%..\core\inc\booldog

@if not exist "%path_to_copy%" @md "%path_to_copy%"

@xcopy /e /v /q /r /y "%bat_dir%include" "%path_to_copy%"

@echo Copy files to %path_to_copy% success
