#!/bin/sh

SAMPLEIN=$(find . -name '*.frag' -o \( -name '*.decaf' \))
TEST_NUM=$(wc -w <<< "$SAMPLEIN")
PASSED_NUM=0

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
    $(./dcc < $SAMPLE &> out) # suppress shell output
    (cmp --silent out $EXPECTEDOUT && echo -e "${GREEN}PASS${NC}" && let "PASSED_NUM++") \
        || (echo -e "${RED} FAIL${NC}")
    rm out

done

if [ $PASSED_NUM -lt $TEST_NUM ]; then
    RESULT_COLOR=$RED
fi
echo ""
echo "${RESULT_COLOR}${SEPARATOR}"
echo "$PASSED_NUM/$TEST_NUM Passed$NC"
