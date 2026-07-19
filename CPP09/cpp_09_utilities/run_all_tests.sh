#!/bin/bash

# ============================================================
#  CPP09 — Master Test Runner
# ============================================================
#  Run from anywhere inside CPP09/
#  Usage: bash cpp_09_utilities/run_all_tests.sh
#  Or from cpp_09_utilities/: bash run_all_tests.sh
# ============================================================

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CPP09_DIR="$(dirname "$SCRIPT_DIR")"

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

TOTAL_PASS=0
TOTAL_FAIL=0

run_exercise() {
    local ex_name="$1"   # e.g. "ex00 - BitcoinExchange"
    local ex_dir="$2"    # absolute path
    local test_script="$3"  # absolute path to test script

    echo ""
    echo -e "${CYAN}${BOLD}############################################"
    echo -e "#  $ex_name"
    echo -e "############################################${RESET}"

    if [ ! -d "$ex_dir" ]; then
        echo -e "${RED}[ERROR]${RESET} Directory not found: $ex_dir"
        return
    fi

    # Build
    echo -e "${BOLD}Building in $ex_dir ...${RESET}"
    (cd "$ex_dir" && make -s 2>&1)
    if [ $? -ne 0 ]; then
        echo -e "${RED}[ERROR]${RESET} Build failed for $ex_name"
        ((TOTAL_FAIL++))
        return
    fi

    # Run tests from the exercise directory
    (cd "$ex_dir" && bash "$test_script")
    ex_exit=$?

    if [ "$ex_exit" -eq 0 ]; then
        echo -e "${GREEN}${BOLD}$ex_name: ALL TESTS PASSED${RESET}"
    else
        echo -e "${RED}${BOLD}$ex_name: SOME TESTS FAILED${RESET}"
        ((TOTAL_FAIL++))
    fi
}

run_exercise \
    "ex00 — BitcoinExchange (btc)" \
    "$CPP09_DIR/ex00" \
    "$SCRIPT_DIR/test_btc.sh"

run_exercise \
    "ex01 — Reverse Polish Notation (RPN)" \
    "$CPP09_DIR/ex01" \
    "$SCRIPT_DIR/test_rpn.sh"

run_exercise \
    "ex02 — PmergeMe (Ford-Johnson)" \
    "$CPP09_DIR/ex02" \
    "$SCRIPT_DIR/test_pmergeme.sh"

echo ""
echo -e "${BOLD}============================================"
if [ "$TOTAL_FAIL" -eq 0 ]; then
    echo -e "  ${GREEN}ALL EXERCISES PASSED${RESET}${BOLD}"
else
    echo -e "  ${RED}$TOTAL_FAIL EXERCISE(S) HAD FAILURES${RESET}${BOLD}"
fi
echo -e "============================================${RESET}"
echo ""

[ "$TOTAL_FAIL" -eq 0 ] && exit 0 || exit 1
