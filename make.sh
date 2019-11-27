CLEAN=false
GEN=false
BUILD=false
CONFIG="Debug"
CLEANBUILD=false
RUN=false
TEST=false

while [ "$1" != "" ]
do
	PARAM=`echo $1 | awk -F= '{print $1}'`
	VALUE=`echo $1 | awk -F= '{print $2}'`
	case $PARAM in
		-clean)			CLEAN=true;;
		-gen)			GEN=true;;
		-build)			BUILD=true;;
		-config)		CONFIG=$VALUE;;
		-run)			RUN=true;;
		-test)			TEST=true;;
		*)
			echo "ERROR: unknown parameter \"$PARAM\""
			;;
	esac
	shift
done

if [ $CLEAN = false			\
	-a $GEN = false			\
	-a $BUILD = false		\
	-a $RUN = false			\
	-a $TEST = false ]
then
	echo "no action specified. you can pass arguments:"
	echo "    -clean"
	echo "    -gen"
	echo "    -build    with additional flags:"
	echo "        -config Release - default Debug"
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
	cd $CURRENT_DIRECTORY/obj/Debug
	cmake $CURRENT_DIRECTORY -DCMAKE_BUILD_TYPE=Debug

	echo "generating solution for release"
	cd $CURRENT_DIRECTORY/obj/Release
	cmake $CURRENT_DIRECTORY -DCMAKE_BUILD_TYPE=Release

	cd $CURRENT_DIRECTORY
fi

if [ $BUILD = true ]; then
	echo "building solution in config $CONFIG"
	cmake --build obj/$CONFIG
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
