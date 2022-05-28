if [ -z ${1+x} ]; then
	echo "Usage: ./uploadToAllParallel.sh <PalletName>";
	return;
fi

SKETCH="$1"
echo
echo "Setting up $SKETCH..."
echo

SKETCH_DIRECTORY="/c/Users/Leo/files/Arduino/Palettes/$SKETCH"
UNO="$SKETCH_DIRECTORY/${SKETCH}Uno"
DUE="$SKETCH_DIRECTORY/${SKETCH}Due"
MIC="$SKETCH_DIRECTORY/${SKETCH}Micro"

test -d "$UNO" || { echo "Uno directory $UNO does not exist" && return; }
test -d "$DUE" || { echo "Due directory $DUE does not exist" && return; }
test -d "$MIC" || { echo "Micro directory $MIC does not exist" && return; }

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
	compile arduino:avr:uno "$UNO" &

	# DUE
	echo
	echo "Due =============>"
	echo
	compile arduino:sam:arduino_due_x_dbg "$DUE" &

	# MIC
	echo
	echo "Micro =============>"
	echo
	compile arduino:avr:micro "$MIC" &

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
	upload arduino:sam:arduino_due_x_dbg COM4 "$DUE" &

	# MIC
	echo
	echo "Micro =============>"
	echo
	(sleep 3 && upload arduino:avr:micro COM13 "$MIC") &

	# UNO
	echo
	echo "Uno =============>"
	echo
	(sleep 5 && upload arduino:avr:uno COM3 "$UNO") &

	# These take the longest to upload so run them in parallel and wait
	wait
}

# compile_all
time upload_all

