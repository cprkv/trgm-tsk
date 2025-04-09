param
(
	[switch] $clean			= $false,
	[switch] $gen			= $false,
	[switch] $build			= $false,
	[string] $config		= 'Debug',
	[switch] $run			= $false,
	[switch] $test			= $false
)

if( !$clean -and !$gen -and !$build -and !$cleanbuild -and !$run -and !$test )
{
	Write-Output "no action specified. you can pass arguments:"
	Write-Output "    -clean             - cleans all build/tmp dirs in solution"
	Write-Output "    -gen               - generates visual studio solution for build"
	Write-Output "    -build             - builds solution (requires -gen first), additional flags for -build:"
	Write-Output "        -config Debug  - cmake build type, default Debug, can be Release"
	Write-Output "    -run               - run example app"
	Write-Output "    -test              - run tests in solution"
	exit
}

$currentDirectory = Get-Location

try
{
	if( $clean )
	{
		Write-Output "cleaning"
		Remove-Item obj -Recurse -Confirm:$false -Force -ErrorAction SilentlyContinue | Out-Null
		Remove-Item bin -Recurse -Confirm:$false -Force -ErrorAction SilentlyContinue | Out-Null
	}
	if( !( Test-Path obj ) )
	{
		Write-Output "no obj directory found. creating"
		New-Item -ItemType Directory -Force -Path obj
	}
	if( !( Test-Path bin ) )
	{
		Write-Output "no bin directory found. creating"
		New-Item -ItemType Directory -Force -Path bin
	}
	if( $gen )
	{
		Write-Output "generating solution"
		Set-Location obj
		cmake ..
		Set-Location $currentDirectory
	}
	if( $build -or $cleanbuild )
	{
		Write-Output "building solution in config $config"
		cmake --build obj --config $config
		Remove-Item bin/example.exe -Confirm:$false -Force -ErrorAction Ignore
		Remove-Item bin/tests.exe -Confirm:$false -Force -ErrorAction Ignore
		Copy-Item obj/example/$config/example.exe bin
		Copy-Item obj/tests/$config/tests.exe bin
	}
	if( $run )
	{
		Write-Output "running"
		.\bin\example.exe
	}
	if( $test )
	{
		Write-Output "testing"
		.\bin\tests.exe
	}
	Write-Output "exit ok"
}
finally
{
	# restore
	Set-Location $currentDirectory
}
