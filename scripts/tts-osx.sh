VOICE=voice_rab_diphone
TEMPO=1.7
PITCH=500

PROFILE=$1
TEXT=$2

PROFILE=1

if [ $PROFILE == "1" ]; then
        VOICE=Alex
        TEMPO=1.0
        PITCH=0
elif [ $PROFILE -eq 2 ]; then
        VOICE=Alex
        TEMPO=1.2
        PITCH=300
elif [ $PROFILE -eq 3 ]; then
        VOICE=Alex
        TEMPO=1.2
	PITCH=700
elif [ $PROFILE -eq 4 ]; then
        VOICE=Alex
        TEMPO=1.0
	PITCH=400
elif [ $PROFILE -eq 5 ]; then
        VOICE=Alex
        TEMPO=1.4
	PITCH=200
fi

#echo $2 > tts.txt
#cat tts.txt | text2wave -o tts.wav -eval "($VOICE)" -scale 5

#play tts.wav tempo $TEMPO pitch $PITCH pad 0 0.2 vol 1 amplitude 0.15 contrast 30 overdrive 30 30 vol 0.7
#osascript <<EOT
#say {$TEXT} using "Alex"
#EOT

say -v "$VOICE" -o tts.aiff "$TEXT"
scripts/sox-osx tts.aiff -d tempo $TEMPO pitch $PITCH pad 0 0.2 vol 1 amplitude 0.15 contrast 30 overdrive 30 30 vol 0.1
pwd
