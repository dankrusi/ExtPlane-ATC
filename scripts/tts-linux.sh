VOICE=voice_rab_diphone
TEMPO=1.7
PITCH=500

PROFILE=$1

if [ $PROFILE -eq 1 ]; then
	VOICE=voice_rab_diphone
	TEMPO=1.7
	PITCH=500
elif [ $PROFILE -eq 2 ]; then
	VOICE=voice_rab_diphone
	TEMPO=1.6
	PITCH=300
elif [ $PROFILE -eq 3 ]; then
	VOICE=voice_rab_diphone
	TEMPO=1.8
	PITCH=700
elif [ $PROFILE -eq 4 ]; then
	VOICE=voice_rab_diphone
	TEMPO=1.7
	PITCH=400
elif [ $PROFILE -eq 5 ]; then
	VOICE=voice_rab_diphone
	TEMPO=1.9
	PITCH=200
fi

echo $2 > tts.txt
cat tts.txt | text2wave -o tts.wav -eval "($VOICE)" -scale 5
#play tts.wav overdrive 70 100 sinc -4k
#play tts.wav overdrive 30 30
#play tts.wav
#play tts.wav tempo $TEMPO pitch $PITCH pad 0 0.2 vol 1 amplitude 0.15 contrast 30 overdrive 30 30 vol 0.7 
play tts.wav pad 0 0.2 vol 1 amplitude 0.15 contrast 30  overdrive 30 10 vol 0.7 
#play tts.wav
