if [ -z ${1+x} ]; then
	echo "Usage: ./upload.sh <PalletName> [force]";
	exit;
fi

FORCE="$2"
SKETCH="$1"
echo
echo "Setting up $SKETCH..."
echo

SKETCH_DIRECTORY="/Users/leonid.belyi/personal/ArduinoLights/Palettes/$SKETCH"
UNO="$SKETCH_DIRECTORY/${SKETCH}Uno"
DUE="$SKETCH_DIRECTORY/${SKETCH}Due"
MIC="$SKETCH_DIRECTORY/${SKETCH}Micro"

UNOPORT="/dev/cu.usbmodem143301"
DUEPORT="/dev/cu.usbmodem14343101"
MICPORT="/dev/cu.usbmodem143201"

UNOTYPE="arduino:avr:uno"
DUETYPE="arduino:sam:arduino_due_x_dbg"
MICTYPE="arduino:avr:micro"

UNOBUILD="$UNO/build/arduino.avr.uno"
DUEBUILD="$DUE/build/arduino.sam.arduino_due_x_dbg"
MICBUILD="$MIC/build/arduino.avr.micro"

test -d "$UNO" || { echo "Uno directory $UNO does not exist" && exit; }
test -d "$DUE" || { echo "Due directory $DUE does not exist" && exit; }
test -d "$MIC" || { echo "Micro directory $MIC does not exist" && exit; }

function compile () {
    # $1 = fbqn, $2 = path, $3 = buildpath
    arduino-cli compile "$2" -b "$1" --build-path "$3"
}

function upload () {
    # $1 = fbqn, $2 = port, $3 = path
    arduino-cli upload -p "$2" -b "$1" --input-dir "$4"
}

function compile_and_upload () {
    # $1 = fbqn, $2 = port, $3 = path, $4 = build_path
    arduino-cli compile "$3" -b "$1"
    arduino-cli upload -p "$2" -b "$1" --input-dir "$4"
}

function compile_all {
	echo
	echo ==================================
	echo "Compiling $SKETCH for all boards..."
	echo ==================================
	echo

	# UNO
	echo
	echo "Uno =============>"
	echo
	compile "$UNOTYPE" "$UNO" "$UNOBUILD" &

	# DUE
	echo
	echo "Due =============>"
	echo
	compile "$DUETYPE" "$DUE" "$DUEBUILD" &

	# MIC
	echo
	echo "Micro =============>"
	echo
	compile "$MICTYPE" "$MIC" "$MICBUILD" &

	wait
}


function upload_all {
	echo
	echo ==================================
	echo "Uploading $SKETCH to all boards!"
	echo ==================================
	echo

	# DUE
	echo
	echo "Due =============>"
	echo
	upload "$DUETYPE" "$DUEPORT" "$DUE" "$DUEBUILD" &

	# MIC
	echo
	echo "Micro =============>"
	echo
	(sleep 3 && upload "$MICTYPE" "$MICPORT" "$MIC" "$MICBUILD") &

	# UNO
	echo
	echo "Uno =============>"
	echo
	(sleep 5 && upload "$UNOTYPE" "$UNOPORT" "$UNO" "$UNOBUILD") &

	# These take the longest to upload so run them in parallel and wait
	wait
}


# compile_all
# time upload_all

function run {
	if [ ! -d "$UNOBUILD" ] || [ ! -d "$DUEBUILD" ] || [ ! -d "$MICBUILD" ] || [ ! -z "$FORCE" ]; then
		time compile_all
	fi
	time upload_all
}

time run

