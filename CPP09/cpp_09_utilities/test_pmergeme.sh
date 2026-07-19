#!/bin/bash

# ============================================================
#  PmergeMe — Comprehensive Test Suite
# ============================================================
#  Run from the ex02 directory after 'make'.
#  Usage: bash test_pmergeme.sh
# ============================================================

BINARY="./PmergeMe"
PASS=0
FAIL=0
ERRORS=()

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

# ── helpers ──────────────────────────────────────────────────

run_test() {
    local desc="$1"
    shift
    local args=("$@")

    output=$("$BINARY" "${args[@]}" 2>&1)
    exit_code=$?

    # Extract "After:" line
    after_line=$(echo "$output" | grep "^After:")

    if [ -z "$after_line" ]; then
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> No 'After:' line in output"
        echo -e "       -> exit=$exit_code  output: $output"
        ERRORS+=("$desc")
        ((FAIL++))
        return
    fi

    # Numbers after "After:"
    after_nums=$(echo "$after_line" | sed 's/After://')

    # Check sorted (non-decreasing)
    prev=""
    ok=true
    for n in $after_nums; do
        if [ -n "$prev" ] && [ "$n" -lt "$prev" ]; then
            ok=false
            break
        fi
        prev=$n
    done

    # Count elements in output vs input
    input_count=${#args[@]}
    output_count=$(echo $after_nums | wc -w | tr -d ' ')

    if [ "$input_count" -ne "$output_count" ]; then
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> Element count mismatch: input=$input_count output=$output_count"
        echo -e "       -> After: $after_nums"
        ERRORS+=("$desc")
        ((FAIL++))
        return
    fi

    if $ok; then
        echo -e "${GREEN}[PASS]${RESET} $desc"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> Output not sorted: $after_nums"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

expect_error() {
    local desc="$1"
    shift
    local args=("$@")

    output=$("$BINARY" "${args[@]}" 2>&1)
    exit_code=$?

    if [ "$exit_code" -ne 0 ]; then
        echo -e "${GREEN}[PASS]${RESET} $desc (correctly returned error)"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc (should have errored but did not)"
        echo -e "       -> output: $output"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

section() {
    echo ""
    echo -e "${CYAN}${BOLD}=========================================="
    echo -e "  $1"
    echo -e "==========================================${RESET}"
}

# ── build check ───────────────────────────────────────────────

if [ ! -f "$BINARY" ]; then
    echo -e "${YELLOW}Binary not found. Running make...${RESET}"
    make
fi

if [ ! -f "$BINARY" ]; then
    echo -e "${RED}Build failed. Aborting tests.${RESET}"
    exit 1
fi

# ==========================================================
section "ERROR / INVALID INPUT TESTS"
# ==========================================================

expect_error "No arguments"
expect_error "Negative number"                  -- -1
expect_error "Negative number mixed"            5 -3 2
expect_error "Float input"                      3.14
expect_error "Float mixed"                      1 2 3.5
expect_error "Alpha input"                      abc
expect_error "Alpha mixed"                      1 2 abc 4
expect_error "Overflow (INT_MAX + 1)"           2147483648
expect_error "Way over INT_MAX"                 9999999999
expect_error "Mixed valid and overflow"         1 2 2147483648
expect_error "Plus sign (not pure digit)"       +5

# ==========================================================
section "EDGE CASES --- TINY INPUTS"
# ==========================================================

run_test  "Single element"                      42
run_test  "Two elements, already sorted"        1 2
run_test  "Two elements, reverse sorted"        2 1
run_test  "Two equal elements"                  5 5
run_test  "Three elements"                      3 1 2
run_test  "Four elements"                       4 3 2 1
run_test  "Five elements (odd)"                 5 1 4 2 3

# ==========================================================
section "ALREADY SORTED / REVERSE SORTED"
# ==========================================================

run_test  "Sorted ascending  (10 elems)"        1 2 3 4 5 6 7 8 9 10
run_test  "Sorted descending (10 elems)"        10 9 8 7 6 5 4 3 2 1
run_test  "Sorted ascending  (21 elems)"        1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
run_test  "Sorted descending (21 elems)"        21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

# ==========================================================
section "ALL IDENTICAL VALUES"
# ==========================================================

run_test  "All same (2 elems)"                  7 7
run_test  "All same (3 elems)"                  7 7 7
run_test  "All same (5 elems)"                  3 3 3 3 3
run_test  "All same (10 elems)"                 1 1 1 1 1 1 1 1 1 1
run_test  "All same (11 elems, odd)"            2 2 2 2 2 2 2 2 2 2 2

# ==========================================================
section "DUPLICATES MIXED IN"
# ==========================================================

run_test  "Duplicates at start"                 1 1 2 3 4
run_test  "Duplicates at end"                   2 3 4 5 5
run_test  "Duplicates in middle"                1 3 3 3 5
run_test  "Multiple duplicate groups"           2 2 4 4 6 6
run_test  "Duplicates with odd count"           1 1 2 3 3 4 5
run_test  "Many duplicates"                     5 1 5 2 5 3 5 4 5

# ==========================================================
section "ODD vs EVEN ELEMENT COUNTS"
# ==========================================================

run_test  "Even count (6)"                      6 1 4 3 2 5
run_test  "Odd  count (7)"                      7 1 4 3 2 5 6
run_test  "Even count (8)"                      8 7 6 5 4 3 2 1
run_test  "Odd  count (9)"                      9 8 7 6 5 4 3 2 1
run_test  "Even count (16)"                     16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
run_test  "Odd  count (17)"                     17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

# ==========================================================
section "BOUNDARY VALUES"
# ==========================================================

run_test  "Zero"                                0
run_test  "Zero in sequence"                    0 5 3 1 2 4
run_test  "Multiple zeros"                      0 0 0 1 2
run_test  "INT_MAX"                             2147483647
run_test  "INT_MAX in sequence"                 2147483647 1 2 3
run_test  "INT_MAX multiple"                    2147483647 2147483647 2147483646
run_test  "Zero and INT_MAX"                    0 2147483647 500000000 1
run_test  "All zeros"                           0 0 0 0 0

# ==========================================================
section "JACOBSTHAL SEQUENCE BOUNDARY SIZES"
# (sizes around transitions: 1,3,5,11,21,43,85...)
# ==========================================================

for n in 2 3 4 5 10 11 12 20 21 22 42 43 44; do
    ARGS=$(seq "$n" -1 1 | tr '\n' ' ')
    run_test "Reverse-sorted $n elements" $ARGS
done

# ==========================================================
section "RANDOM / STRESS TESTS"
# ==========================================================

stress_test() {
    local count=$1
    local max=${2:-9999}
    local args=()
    for ((i=0; i<count; i++)); do
        args+=($((RANDOM % max)))
    done
    run_test "Random $count elements (max=$max)" "${args[@]}"
}

stress_test 10
stress_test 20
stress_test 50
stress_test 100
stress_test 500
stress_test 1000
stress_test 3000

# ==========================================================
section "SPECIAL PATTERNS"
# ==========================================================

run_test  "Alternating hi/lo"                   9 1 8 2 7 3 6 4 5 0
run_test  "All descending pairs"                10 9 8 7 6 5 4 3 2 1
run_test  "V-shape"                             5 4 3 2 1 2 3 4 5
run_test  "Sawtooth"                            3 1 4 1 5 9 2 6 5 3
run_test  "Power of 2 sequence"                 128 64 32 16 8 4 2 1
run_test  "One outlier at end"                  1 2 3 4 5 6 7 8 9 100
run_test  "One outlier at start"                100 1 2 3 4 5 6 7 8 9
run_test  "Two elements equal"                  42 42
run_test  "Three all same"                      0 0 0

# ==========================================================
section "OUTPUT FORMAT CHECKS"
# ==========================================================

format_test() {
    local desc="$1"
    shift
    local args=("$@")
    output=$("$BINARY" "${args[@]}" 2>&1)
    exit_code=$?

    has_before=$(echo "$output" | grep -c "^Before:")
    has_after=$(echo "$output" | grep -c "^After:")
    has_vec_time=$(echo "$output" | grep -c "std::vector")
    has_deq_time=$(echo "$output" | grep -c "std::deque")

    if [ "$has_before" -ge 1 ] && [ "$has_after" -ge 1 ] && \
       [ "$has_vec_time" -ge 1 ] && [ "$has_deq_time" -ge 1 ] && \
       [ "$exit_code" -eq 0 ]; then
        echo -e "${GREEN}[PASS]${RESET} $desc"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> before=$has_before after=$has_after vec=$has_vec_time deq=$has_deq_time exit=$exit_code"
        echo -e "       -> output: $output"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

format_test "Format: Before/After/Time present (5 elems)"    5 3 1 4 2
format_test "Format: Before/After/Time present (100 elems)"  $(seq 100 -1 1)
format_test "Format: timing label contains 'us'"             1 2 3 4 5

# ==========================================================
#  SUMMARY
# ==========================================================

echo ""
echo -e "${BOLD}=========================================="
echo -e "  RESULTS: ${GREEN}$PASS passed${RESET}  ${RED}$FAIL failed${RESET}${BOLD}"
echo -e "==========================================${RESET}"

if [ ${#ERRORS[@]} -gt 0 ]; then
    echo ""
    echo -e "${RED}${BOLD}Failed tests:${RESET}"
    for e in "${ERRORS[@]}"; do
        echo -e "  ${RED}x${RESET} $e"
    done
fi

echo ""
[ $FAIL -eq 0 ] && exit 0 || exit 1
