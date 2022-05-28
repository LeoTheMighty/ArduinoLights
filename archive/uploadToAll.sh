set -e

if [ -z ${1+x} ]; then
	echo "Usage: ./uploadToAll <PalletName>";
	exit;
fi

SKETCH="$1"
echo
echo "Setting up $SKETCH..."
echo

SKETCH_DIRECTORY="/c/Users/Leo/files/Arduino/Palettes/$SKETCH"
UNO="$SKETCH_DIRECTORY/${SKETCH}Uno"
DUE="$SKETCH_DIRECTORY/${SKETCH}Due"
ESP="$SKETCH_DIRECTORY/${SKETCH}ESP"

test -d "$UNO" || { echo "Uno directory $UNO does not exist" && exit; }
test -d "$DUE" || { echo "Due directory $DUE does not exist" && exit; }
test -d "$ESP" || { echo "ESP directory $ESP does not exist" && exit; }

function compile () {
    # $1 = fbqn, $2 = path
    arduino-cli compile "$2" -b "$1"
}

function upload () {
    # $1 = fbqn, $2 = port, $3 = path
    arduino-cli upload "$3" -p "$2" -b "$1"
}

function compile_and_upload () {
    # $1 = fbqn, $2 = port, $3 = path
    arduino-cli compile "$3" -b "$1"
    arduino-cli upload "$3" -p "$2" -b "$1"
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
	compile arduino:avr:uno "$UNO"

	# DUE
	echo
	echo "Due =============>"
	echo
	compile arduino:sam:arduino_due_x_dbg "$DUE"

	# ESP
	echo
	echo "ESP =============>"
	echo
	compile esp8266:esp8266:nodemcuv2 "$ESP"
}


function upload_all {
	echo
	echo ==================================
	echo "Uploading $SKETCH to all boards!"
	echo ==================================
	echo

	# ESP
	echo
	echo "ESP =============>"
	echo
	upload esp8266:esp8266:nodemcuv2 COM5 "$ESP"

	# DUE
	echo
	echo "Due =============>"
	echo
	upload arduino:sam:arduino_due_x_dbg COM4 "$DUE"

	# UNO
	echo
	echo "Uno =============>"
	echo
	upload arduino:avr:uno COM3 "$UNO"
}

compile_all
time upload_all

