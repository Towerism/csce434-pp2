#!/bin/bash

SAMPLEIN=$(find ./test/"$1" -name '*.frag' -o \( -name '*.decaf' \))
TEST_NUM=$(wc -w <<< "$SAMPLEIN")
PASSED_NUM=0
FAILED=
ARGS=

if [ "$1" = "syntax" ]; then
   ARGS="-s"
fi

RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
NC=$(tput setaf 7)
RESULT_COLOR=$GREEN

SEPARATOR="==========================="

echo "${GREEN}"
echo "Running tests"
echo "${SEPARATOR}"
echo "${NC}"

for SAMPLE in $SAMPLEIN; do
    EXPECTEDOUT=$(echo "$SAMPLE" | sed -e "s/\.frag/\.out/g" | sed -e "s/\.decaf/\.out/g" )

    printf "${GREEN}[ Test $SAMPLE ]${NC}"

    rm -f out

    $(./dcc $ARGS < $SAMPLE &> out) # suppress shell output

    cmp --silent out $EXPECTEDOUT

    if [[ $? != 0 ]]; then
        echo -e "${RED} FAIL${NC}"
        FAILED="$FAILED $SAMPLE"
    else
        echo -e "${GREEN} PASS${NC}"
        ((PASSED_NUM+=1))
    fi

    rm out
done

if [ $PASSED_NUM -lt $TEST_NUM ]; then
    RESULT_COLOR=$RED
    echo ""
    echo -e "${RED}Failed tests:\n"
fi

for FAILURE in $FAILED; do
    echo -e "[ Test $FAILURE ]"
done
echo ""
echo "${RESULT_COLOR}${SEPARATOR}"
echo "$PASSED_NUM/$TEST_NUM Passed$NC"
echo ""

if [ $PASSED_NUM -lt $TEST_NUM ]; then
    exit 1
fi
