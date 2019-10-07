$currentDirectory = Get-Location

Try
{
	ForEach( $arg in $args )
	{
		switch( $arg )
		{
			"r"
			{
				Write-Output "set Release flag"
				$buildType = "Release"
				break
			}
			"d"
			{
				Write-Output "set Debug flag"
				$buildType = "Debug"
				break
			}
		}
	}

	ForEach( $arg in $args )
	{
		switch -wildcard( $arg )
		{
			"clean"
			{
				Try
				{
					Remove-Item -Recurse -Force -ErrorAction Stop -Path obj
				}
				Catch [ System.Management.Automation.ItemNotFoundException ]
				{
					Write-Output "no obj folder"
				}
				Try
				{
					Remove-Item -Force -ErrorAction Stop -Path bin/example.exe
				}
				Catch [ System.Management.Automation.ItemNotFoundException ]
				{
					Write-Output "no bin folder"
				}
				Write-Output "clean ok"
				break
			}
		}
	}

	ForEach( $arg in $args )
	{
		switch -wildcard( $arg )
		{
			"gen*"
			{
				$year = "20" + $arg.Substring( "gen".Length )
				$cmakeGenerators = cmd /c cmake -G '2>&1'
				$filteredGenerator = $cmakeGenerators.Where{ $_.Contains( "Visual Studio" ) -and $_.Contains( $year ) }[0]
				$first = $filteredGenerator.IndexOf( "Visual" )
				$count = $filteredGenerator.IndexOf( " = " ) - $first
				$generator = $filteredGenerator.Substring( $first, $count ).Trim( " ", "	" )
				if( $filteredGenerator.Contains( "[arch]" ) )	# todo check this condition
				{
					$generator = $generator.Substring( 0, $generator.IndexOf( " [arch]" ) )
					$generator = $generator + " Win64"
				}
				Write-Output "cmake generator will use '$generator'"
				mkdir -Path obj -ErrorAction SilentlyContinue | Out-Null
				Set-Location obj
				$additionalArgs = ""
				if( $buildType.Equals( "Debug" ) )
				{
					$additionalArgs = "-Werror=dev"
				}
				cmake .. -G $generator $additionalArgs
				Set-Location ..
				break
			}
			"b"
			{
				if( $buildType.Equals( "" ) )
				{
					throw 'You need specify configuration for this command: r or d'
				}
				Set-Location obj
				$additionalArgs = ""
				if( $buildType.Equals( "Debug" ) )
				{
					$additionalArgs = @("--verbose", "--clean-first")
				}
				cmake --build . --config $buildType $additionalArgs
				Set-Location ..
				if( Test-Path -PathType Leaf -Path bin/$buildType/*.exe )
				{
					Get-ChildItem -Path bin/$buildType | 
						Where-Object { $_.Name -match ".exe" } | 
						Copy-Item -Destination bin
				}
			}
		}
	}
}
Finally
{
	Set-Location $currentDirectory
}
