#!/bin/bash

# ============================================================
#  RPN (ex01) — Comprehensive Test Suite
# ============================================================
#  Run from the ex01 directory after 'make'.
#  Usage: bash ../cpp_09_utilities/test_rpn.sh
# ============================================================

BINARY="./RPN"
PASS=0
FAIL=0
ERRORS=()

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

section() {
    echo ""
    echo -e "${CYAN}${BOLD}=========================================="
    echo -e "  $1"
    echo -e "==========================================${RESET}"
}

# expect_result DESC EXPRESSION EXPECTED_OUTPUT
# Checks that stdout == EXPECTED_OUTPUT and exit code == 0
expect_result() {
    local desc="$1"
    local expr="$2"
    local expected="$3"

    output=$("$BINARY" "$expr" 2>/dev/null)
    exit_code=$?

    if [ "$exit_code" -eq 0 ] && [ "$output" = "$expected" ]; then
        echo -e "${GREEN}[PASS]${RESET} $desc"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> Expression: '$expr'"
        echo -e "       -> Expected:   '$expected' (exit 0)"
        echo -e "       -> Got:        '$output'   (exit $exit_code)"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# expect_error DESC EXPRESSION
# Checks that stderr contains "Error" and exit code != 0
expect_error() {
    local desc="$1"
    local expr="$2"

    stderr_out=$("$BINARY" "$expr" 2>&1 1>/dev/null)
    exit_code=$?
    stdout_out=$("$BINARY" "$expr" 2>/dev/null)

    # Must exit with error
    if [ "$exit_code" -ne 0 ] && echo "$stderr_out" | grep -qi "error"; then
        echo -e "${GREEN}[PASS]${RESET} $desc (correctly errored)"
        ((PASS++))
    elif [ "$exit_code" -ne 0 ]; then
        # exit error but no "Error" word – still acceptable per spec
        echo -e "${GREEN}[PASS]${RESET} $desc (exit != 0)"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc (should have errored)"
        echo -e "       -> Expression: '$expr'"
        echo -e "       -> stdout: '$stdout_out'  stderr: '$stderr_out'  exit: $exit_code"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# expect_error_no_args
# Binary with no args should error
expect_error_noargs() {
    local desc="$1"
    output=$("$BINARY" 2>&1)
    exit_code=$?
    if [ "$exit_code" -ne 0 ]; then
        echo -e "${GREEN}[PASS]${RESET} $desc (exit != 0)"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc (should have errored, got exit 0)"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# ── Build check ──────────────────────────────────────────────

if [ ! -f "$BINARY" ]; then
    echo -e "${YELLOW}Binary not found, running make...${RESET}"
    make
fi
if [ ! -f "$BINARY" ]; then
    echo -e "${RED}Build failed. Aborting.${RESET}"
    exit 1
fi

# ==========================================================
section "SUBJECT EXAMPLES (from the PDF)"
# ==========================================================
# Note: numbers in the expression are always < 10 per spec.
# Results can exceed 10.

expect_result  "8 9 * 9 - 9 - 9 - 4 - 1 +"     "8 9 * 9 - 9 - 9 - 4 - 1 +"   "42"
expect_result  "7 7 * 7 -"                       "7 7 * 7 -"                    "42"
expect_result  "1 2 * 2 / 2 * 2 4 - +"           "1 2 * 2 / 2 * 2 4 - +"       "0"
expect_error   "(1 + 1) — parentheses are invalid" "(1 + 1)"

# ==========================================================
section "BASIC OPERATIONS"
# ==========================================================

expect_result  "Addition: 3 + 4 = 7"             "3 4 +"    "7"
expect_result  "Subtraction: 5 - 3 = 2"          "5 3 -"    "2"
expect_result  "Multiplication: 3 * 4 = 12"      "3 4 *"    "12"
expect_result  "Division: 8 / 4 = 2"             "8 4 /"    "2"

# ==========================================================
section "ZERO RESULTS"
# ==========================================================

expect_result  "5 - 5 = 0"      "5 5 -"    "0"
expect_result  "0 * 9 = 0"      "0 9 *"    "0"
expect_result  "0 + 0 = 0"      "0 0 +"    "0"
expect_result  "0 / 1 = 0"      "0 1 /"    "0"

# ==========================================================
section "NEGATIVE INTERMEDIATE RESULTS"
# ==========================================================
# The spec says input numbers < 10, but results can be negative.

expect_result  "3 - 5 = -2"     "3 5 -"    "-2"
expect_result  "1 - 9 = -8"     "1 9 -"    "-8"
expect_result  "2 9 - 3 * = -21" "2 9 - 3 *"  "-21"

# ==========================================================
section "CHAINED OPERATIONS"
# ==========================================================

expect_result  "1 2 3 + + = 6"       "1 2 3 + +"    "6"
expect_result  "9 8 - 7 6 - + = 2"   "9 8 - 7 6 - +"  "2"
expect_result  "2 3 * 4 + = 10"      "2 3 * 4 +"    "10"
expect_result  "5 1 2 + 4 * + 3 - = 14" "5 1 2 + 4 * + 3 -"  "14"
expect_result  "2 2 2 2 + + + = 8"   "2 2 2 2 + + +"   "8"

# ==========================================================
section "SINGLE NUMBER (trivial valid expression?)"
# ==========================================================
# A single number with no operator: the stack has one element.
# Per spec, stack must have exactly 1 element at end → valid result.

expect_result  "Single number 5"         "5"    "5"
expect_result  "Single number 0"         "0"    "0"
expect_result  "Single number 9"         "9"    "9"

# ==========================================================
section "DIVISION EDGE CASES"
# ==========================================================

expect_result  "Integer division 7 / 2 = 3"    "7 2 /"   "3"
expect_result  "9 / 3 = 3"                     "9 3 /"   "3"
expect_error   "Division by zero"              "5 0 /"

# ==========================================================
section "ERROR CASES: TOO FEW OPERANDS"
# ==========================================================

expect_error   "Operator with no operands: +"    "+"
expect_error   "Operator with one operand: 5 +"  "5 +"
expect_error   "Two operators no operands: + +"  "+ +"
expect_error   "Only operator: *"                "*"
expect_error   "Only operator: -"                "-"
expect_error   "Only operator: /"                "/"

# ==========================================================
section "ERROR CASES: TOO MANY OPERANDS"
# ==========================================================

# Stack has more than 1 element after processing → Error
expect_error   "Two numbers, no operator: 1 2"   "1 2"
expect_error   "Three numbers, no operator: 1 2 3" "1 2 3"
expect_error   "Extra leftover after op: 1 2 + 3"  "1 2 + 3"

# ==========================================================
section "ERROR CASES: INVALID TOKENS"
# ==========================================================

# Numbers >= 10 are invalid (spec: numbers always < 10)
expect_error   "Number 10 → invalid token"      "10"
expect_error   "Number 42 → invalid token"      "42"
expect_error   "Multi-digit in expression"      "10 2 +"
expect_error   "Alphabetic token 'a'"           "a"
expect_error   "Alphabetic token 'abc'"         "abc"
expect_error   "Alphabetic token 'x'"           "x"
expect_error   "Comma as token"                 "1 2 , +"

# The spec says tokens are + - / * and single-digit numbers only.
# Parentheses are explicitly forbidden in the subject example.
expect_error   "Parenthesis ( is invalid"       "( 1 2 + )"
expect_error   "Caret ^ is invalid"             "2 3 ^"
expect_error   "Percent % is invalid"           "6 3 %"

# ==========================================================
section "NO ARGUMENTS"
# ==========================================================

expect_error_noargs "No arguments → error"

# ==========================================================
section "EMPTY EXPRESSION"
# ==========================================================

expect_error   "Empty string → error"  ""

# ==========================================================
section "WHITESPACE ONLY"
# ==========================================================

expect_error   "Spaces only → error"   "   "

# ==========================================================
section "OUTPUT FORMAT: Result on stdout, Error on stderr"
# ==========================================================

# Valid: result must be on stdout
out=$("$BINARY" "3 4 +" 2>/dev/null)
if [ "$out" = "7" ]; then
    echo -e "${GREEN}[PASS]${RESET} Valid expression: result '7' on stdout"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Valid expression: expected '7' on stdout, got '$out'"
    ERRORS+=("Valid result should appear on stdout")
    ((FAIL++))
fi

# Valid: nothing on stderr
err=$("$BINARY" "3 4 +" 2>&1 1>/dev/null)
if [ -z "$err" ]; then
    echo -e "${GREEN}[PASS]${RESET} Valid expression: no output on stderr"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Valid expression: unexpected stderr: '$err'"
    ERRORS+=("Valid result should produce no stderr output")
    ((FAIL++))
fi

# Error: result must appear on stderr, not stdout
out=$("$BINARY" "+" 2>/dev/null)
err=$("$BINARY" "+" 2>&1 1>/dev/null)
if [ -z "$out" ] && [ -n "$err" ]; then
    echo -e "${GREEN}[PASS]${RESET} Error expression: 'Error' on stderr, nothing on stdout"
    ((PASS++))
elif [ -z "$out" ]; then
    echo -e "${GREEN}[PASS]${RESET} Error expression: nothing on stdout (stderr: '$err')"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Error expression: stdout should be empty, got '$out'"
    ERRORS+=("Error case should produce no stdout")
    ((FAIL++))
fi

# ==========================================================
section "OUTPUT ENDS WITH NEWLINE"
# ==========================================================

result=$("$BINARY" "5 3 +" 2>/dev/null)
if [ "$result" = "8" ]; then
    echo -e "${GREEN}[PASS]${RESET} Output '8' has correct value (shell strips trailing newline)"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Expected '8', got '$result'"
    ERRORS+=("Output should be '8' for '5 3 +'")
    ((FAIL++))
fi

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
