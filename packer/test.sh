# Black        0;30     Dark Gray     1;30
# Red          0;31     Light Red     1;31
# Green        0;32     Light Green   1;32
# Brown/Orange 0;33     Yellow        1;33
# Blue         0;34     Light Blue    1;34
# Purple       0;35     Light Purple  1;35
# Cyan         0;36     Light Cyan    1;36
# Light Gray   0;37     White         1;37

BOLD='\033[5m'
NORMAL=$(tput sgr0)
NC='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
GRAY='\033[1;30m'
WHITE='\033[1;37m'
MAGENTA='\033[1;35m'

DATASET=$(cat dataset)

FILENAME=()
INPUTS=()
OUTPUTS=()

IFS=$'\n' read -rd '' -a y <<<"$DATASET"


for i in "${y[@]}"
do
	IFS=':' read -ra value <<< "$i"
	if [[ $i == *FILE* ]]; then

		FILENAME[${#FILENAME[@]}]="${value[1]}"
	fi
	if [[ $i == *IN* ]]; then
		INPUTS[${#INPUTS[@]}]=${value[1]}
	fi
	if [[ $i == *OUT* ]]; then
		OUTPUTS[${#OUTPUTS[@]}]=${value[1]}
	fi
done

clang-format -i *.c

for (( i=0; i<${#FILENAME[@]}; i++ ));
do
	echo "$GRAY ============= $WHITE Test for: $MAGENTA ${FILENAME[i]} $GRAY ================"
	gcc ${FILENAME[i]}
	
	FILE=$(echo ${FILENAME[i]} | sed 's/ *$//g')

	OUT_V=$(echo ${OUTPUTS[i]} | tr ' ' '_')
	IN_V=$(echo ${INPUTS[i]} | tr ' ' '_');

	RESULT=$(./a.out << EOF
	${INPUTS[i]}
	EOF);
	
	RES_V=$(echo $RESULT | sed 's/ *$//g' | tr ' ' '_')

	if [ "$RES_V" = "$OUT_V" ]; then
		echo "$GRAY TEST #$i $GREEN Well done $NC"

	else
		echo "$GRAY TEST #$i $RED ERROR $NC"
		echo '\tExpected:\t'${OUTPUTS[i]}
		echo '\tGot:\t\t'   ${RESULT}
	fi
	rm a.out
done
: '
for in_v in "${INPUTS[@]}"
do
	echo $in_v
done

for out_v in "${OUTPUTS[@]}"
do
	echo $out_v
done

'

while getopts 'lha:' OPTION; do
  case "$OPTION" in
    l)
      echo "linuxconfig"
      ;;
    h)
      echo "you have supplied the -h option"
      ;;
    a)
      avalue="$OPTARG"
      echo "The value provided is $OPTARG"
      ;;
    ?)
      echo "script usage: $(basename \$0) [-l] [-h] [-a somevalue]" >&2
      exit 1
      ;;
  esac
done
shift "$(($OPTIND -1))"
