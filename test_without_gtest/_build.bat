@set project_name=%1
@set configuration=%2
@set platform=%3
%windir%\microsoft.net\framework\v4.0.30319\msbuild %project_name%.vcxproj /verbosity:n /p:Configuration=%configuration% /p:Platform=%platform% /t:Clean
%windir%\microsoft.net\framework\v4.0.30319\msbuild %project_name%.vcxproj /verbosity:n /p:Configuration=%configuration% /p:Platform=%platform% /t:build