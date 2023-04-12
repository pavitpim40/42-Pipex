#!/bin/bash

RED="\033[0;31m"
GREEN='\033[0;32m'
BLUE='\033[0;34m'
BOLD="\033[1m"
RESET="\033[0m"


mkdir outs
cd outs
mkdir "02" "04" "05" "07"
cd ../
# TES-01
# echo -e "${BOLD}${BLUE}## TEST-01${RESET}"
# PATH_OUTS='./outs/01'

# ORG_CMD="$(< infile csdfat | wsdfc -cl > $PATH_OUTS/test-01-org.txt)"
# echo EXIT STATUS : $? > "$PATH_OUTS/test-01-status-my.txt"



# PIPEX_CMD="$(./pipex  infile csdfat  "wsdfc -cl" $PATH_OUTS/test-01-my.txt)"
# echo EXIT STATUS : $? > "$PATH_OUTS/test-01-status-org.txt"



# if diff $PATH_OUTS/test-01-org.txt $PATH_OUTS/test-01-my.txt >/dev/null ; then
#    echo -e "${BOLD}OUTPUT : ${BOLD}${GREEN}NO DIFF${RESET}"
# else
# 	echo -e "${BOLD}OUTPUT : ${BOLD}${RED}DIFF${RESET}"
#     diff $PATH_OUTS/test-01-org.txt $PATH_OUTS/test-01-my.txt >> diff-01.txt
# fi

# if diff $PATH_OUTS/test-01-status-org.txt $PATH_OUTS/test-01-status-my.txt >/dev/null ; then
#   echo -e "${BOLD}STATUS : ${BOLD}${GREEN}NO DIFF${RESET}"
# else
# 	echo -e "${BOLD}STATUS : ${BOLD}${RED}DIFF${RESET}"
#     diff $PATH_OUTS/test-01-status-org.txt $PATH_OUTS/test-01-status-my.txt >> $PATH_OUTS/diff-01.txt
# fi

# MAKE="$(make re)"
# TEST02



echo -e "${BOLD}${BLUE}## TEST-02${RESET}"
PATH_OUTS='./outs/02'

ORG_CMD="$(< ll /bin/catsdc | wcss -cl > $PATH_OUTS/output-original.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-my.txt"



PIPEX_CMD="$(./pipex ll /bin/catsdc  "wsdfc -cl" $PATH_OUTS/output-my.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-org.txt"



if diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >/dev/null ; then
   echo -e "${BOLD}OUTPUT : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}OUTPUT : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >> diff.txt
fi

if diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >/dev/null ; then
  echo -e "${BOLD}STATUS : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}STATUS : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >> $PATH_OUTS/diff-status.txt
fi




# TEST04

echo -e "${BOLD}${BLUE}## TEST-04${RESET}"
PATH_OUTS='./outs/04'

ORG_CMD="$(< infile csdfat | wsdfc -cl > $PATH_OUTS/output-original.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-my.txt"



PIPEX_CMD="$(./pipex infile csdfat "wsdfc -cl" $PATH_OUTS/output-my.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-org.txt"



if diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >/dev/null ; then
   echo -e "${BOLD}OUTPUT : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}OUTPUT : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >> diff.txt
fi

if diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >/dev/null ; then
  echo -e "${BOLD}STATUS : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}STATUS : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >> $PATH_OUTS/diff-status.txt
fi


# TEST05
# < non_exist_input /bin/catsdc | wcss -cl 

echo -e "${BOLD}${BLUE}## TEST-05${RESET}"
PATH_OUTS='./outs/05'

ORG_CMD="$(< non_exist_input /bin/catsdc | wcss -cl  > $PATH_OUTS/output-original.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-my.txt"



PIPEX_CMD="$(./pipex non_exist_input /bin/catsdc  "wcss -cl" $PATH_OUTS/output-my.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-org.txt"



if diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >/dev/null ; then
   echo -e "${BOLD}OUTPUT : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}OUTPUT : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >> diff.txt
fi

if diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >/dev/null ; then
  echo -e "${BOLD}STATUS : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}STATUS : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >> $PATH_OUTS/diff-status.txt
fi


# TEST07
# < exist_input /bin/caqwdt  | /bin/lsqwd -ls 

echo -e "${BOLD}${BLUE}## TEST-07${RESET}"
PATH_OUTS='./outs/07'

ORG_CMD="$(< infile /bin/caqwdt  | /bin/lsqwd -ls  > $PATH_OUTS/output-original.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-my.txt"



PIPEX_CMD="$(./pipex infile /bin/caqwdt "/bin/lsqwd -ls" $PATH_OUTS/output-my.txt)"
echo EXIT STATUS : $? > "$PATH_OUTS/status-org.txt"



if diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >/dev/null ; then
   echo -e "${BOLD}OUTPUT : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}OUTPUT : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/output-original.txt $PATH_OUTS/output-my.txt >> diff.txt
fi

if diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >/dev/null ; then
  echo -e "${BOLD}STATUS : ${BOLD}${GREEN}NO DIFF${RESET}"
else
	echo -e "${BOLD}STATUS : ${BOLD}${RED}DIFF${RESET}"
    diff $PATH_OUTS/status-org.txt $PATH_OUTS/status-my.txt >> $PATH_OUTS/diff-status.txt
fi