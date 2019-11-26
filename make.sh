CLEAN=false
GEN=false
BUILD=false
CONFIG="Debug"
CLEANBUILD=false
RUN=false
TEST=false
J=4

while [ "$1" != "" ]
do
	PARAM=`echo $1 | awk -F= '{print $1}'`
	VALUE=`echo $1 | awk -F= '{print $2}'`
	case $PARAM in
		-clean)			CLEAN=true;;
		-gen)			GEN=true;;
		-build)			BUILD=true;;
		-config)		CONFIG=$VALUE;;
		-cleanbuild)	CLEANBUILD=true;;
		-run)			RUN=true;;
		-test)			TEST=true;;
		-j)				J=$VALUE;;
		*)
			echo "ERROR: unknown parameter \"$PARAM\""
			;;
	esac
	shift
done

if [ $CLEAN = false			\
	-a $GEN = false			\
	-a $BUILD = false		\
	-a $CLEANBUILD = false	\
	-a $RUN = false			\
	-a $TEST = false ]
then
	echo "no action specified. you can pass arguments:"
	echo "    -clean"
	echo "    -gen"
	echo "    -build    with additional flags:"
	echo "        -config Release - default Debug"
	echo "        -j 8            - count of threads to build"
	echo "    -run"
	echo "    -test"
	exit 1
fi

CURRENT_DIRECTORY=`pwd`

if [ $CLEAN = true ]; then
	echo "cleaning"
	rm -rf obj bin
fi

if [ ! -d "obj" ]; then
	echo "no obj directory found. creating"
	mkdir obj
	mkdir obj/Debug
	mkdir obj/Release
fi

if [ ! -d "bin" ]; then
	echo "no bin directory found. creating"
	mkdir bin
fi

if [ $GEN = true ]; then
	echo "generating solution for debug"
	cmake -S . -B obj/Debug -Werror=dev -DCMAKE_BUILD_TYPE=Debug
	echo "generating solution for release"
	cmake -S . -B obj/Release -Werror=dev -DCMAKE_BUILD_TYPE=Release
fi

if [ $BUILD = true ] || [ $CLEANBUILD = true ]; then
	echo "building solution in config $CONFIG"
	ADDITIONAL_ARGS=""
	if [ $CONFIG == "Debug" ]; then
		ADDITIONAL_ARGS="$ADDITIONAL_ARGS --verbose"
	fi
	if [ $CLEANBUILD = true ]; then
		ADDITIONAL_ARGS="$ADDITIONAL_ARGS --clean-first"
	fi
	cmake --build obj/$CONFIG $ADDITIONAL_ARGS -j $J
	rm -f bin/example
	rm -f bin/tests
	cp obj/$CONFIG/example bin
	cp obj/$CONFIG/tests bin
fi

if [ $RUN = true ]; then
	echo "running"
	./bin/example
fi

if [ $TEST = true ]; then
	echo "testing"
	./bin/tests
fi

cd $CURRENT_DIRECTORY

echo "exit ok"
