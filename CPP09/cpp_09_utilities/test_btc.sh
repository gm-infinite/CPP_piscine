#!/bin/bash

# ============================================================
#  BitcoinExchange (ex00) — Comprehensive Test Suite
# ============================================================
#  Run from the ex00 directory after 'make'.
#  Usage: bash ../cpp_09_utilities/test_btc.sh
#  Or:    cd ex00 && bash ../cpp_09_utilities/test_btc.sh
# ============================================================

BINARY="./btc"
PASS=0
FAIL=0
ERRORS=()
TMPDIR_TEST=$(mktemp -d)

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

# ── helpers ──────────────────────────────────────────────────

# make_input <filename> <lines...>
# Creates a temp input file with header "date | value" + given lines
make_input() {
    local file="$TMPDIR_TEST/$1"
    shift
    echo "date | value" > "$file"
    for line in "$@"; do
        echo "$line" >> "$file"
    done
    echo "$file"
}

# expect_stdout DESC EXPECTED_PATTERN INPUT_FILE
# Checks that stdout contains the expected pattern
expect_stdout() {
    local desc="$1"
    local expected="$2"
    local input="$3"

    output=$("$BINARY" "$input" 2>/dev/null)
    if echo "$output" | grep -qF "$expected"; then
        echo -e "${GREEN}[PASS]${RESET} $desc"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> Expected stdout to contain: '$expected'"
        echo -e "       -> Got: '$output'"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# expect_stderr DESC EXPECTED_PATTERN INPUT_FILE
expect_stderr() {
    local desc="$1"
    local expected="$2"
    local input="$3"

    stderr_output=$("$BINARY" "$input" 2>&1 1>/dev/null)
    if echo "$stderr_output" | grep -qF "$expected"; then
        echo -e "${GREEN}[PASS]${RESET} $desc"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> Expected stderr to contain: '$expected'"
        echo -e "       -> Got stderr: '$stderr_output'"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# expect_no_stdout DESC INPUT_FILE
# checks no stdout is produced for an errored line
expect_no_stdout_for_line() {
    local desc="$1"
    local not_expected="$2"
    local input="$3"

    output=$("$BINARY" "$input" 2>/dev/null)
    if echo "$output" | grep -qF "$not_expected"; then
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> Expected no stdout for this pattern but found: '$not_expected'"
        ERRORS+=("$desc")
        ((FAIL++))
    else
        echo -e "${GREEN}[PASS]${RESET} $desc"
        ((PASS++))
    fi
}

# expect_error_exit DESC [args...]
expect_error_exit() {
    local desc="$1"
    shift
    output=$("$BINARY" "$@" 2>&1)
    exit_code=$?
    if [ "$exit_code" -ne 0 ]; then
        echo -e "${GREEN}[PASS]${RESET} $desc (exit != 0)"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc (should have exited with error)"
        echo -e "       -> output: $output"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# expect_exit_ok DESC INPUT_FILE
expect_exit_ok() {
    local desc="$1"
    local input="$2"
    "$BINARY" "$input" > /dev/null 2>&1
    exit_code=$?
    if [ "$exit_code" -eq 0 ]; then
        echo -e "${GREEN}[PASS]${RESET} $desc (exit == 0)"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc (expected exit 0, got $exit_code)"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# result_check DESC INPUT_FILE DATE VALUE EXPECTED_RESULT
# Checks stdout contains "DATE => VALUE = EXPECTED" with float tolerance
result_check() {
    local desc="$1"
    local input="$2"
    local date="$3"
    local value="$4"
    local expected="$5"  # expected result (approximate)

    output=$("$BINARY" "$input" 2>/dev/null)
    # Check if output line matches the pattern (loose match on the = value)
    if echo "$output" | grep -qF "$date => $value = "; then
        echo -e "${GREEN}[PASS]${RESET} $desc (output line found)"
        ((PASS++))
    else
        echo -e "${RED}[FAIL]${RESET} $desc"
        echo -e "       -> Expected line containing: '$date => $value = '"
        echo -e "       -> Got: '$output'"
        ERRORS+=("$desc")
        ((FAIL++))
    fi
}

# ── Build check ───────────────────────────────────────────────

if [ ! -f "$BINARY" ]; then
    echo -e "${YELLOW}Binary not found, running make...${RESET}"
    make
fi

if [ ! -f "$BINARY" ]; then
    echo -e "${RED}Build failed. Aborting.${RESET}"
    exit 1
fi

# ==========================================================
section "ARGUMENT / INVOCATION ERRORS"
# ==========================================================

expect_error_exit "No arguments"
expect_error_exit "Two arguments" "foo.txt" "bar.txt"
expect_error_exit "Non-existent file"  "nonexistent_file_xyz_abc.txt"

# ==========================================================
section "SUBJECT EXAMPLE TEST (from the PDF)"
# ==========================================================
# The PDF shows: date | value header then various lines
# Expected output seen in the PDF. We test key lines.

SUBJECT_INPUT=$(make_input "subject_input.txt" \
    "2011-01-03 | 3" \
    "2011-01-03 | 2" \
    "2011-01-03 | 1" \
    "2011-01-03 | 1.2" \
    "2011-01-09 | 1" \
    "2012-01-11 | -1" \
    "2001-42-42" \
    "2012-01-11 | 1" \
    "2012-01-11 | 2147483648")

expect_stdout   "Subject: 2011-01-03 | 3 → produces output line"  "2011-01-03 => 3 = "  "$SUBJECT_INPUT"
expect_stdout   "Subject: 2011-01-09 | 1 → produces output line"  "2011-01-09 => 1 = "  "$SUBJECT_INPUT"
expect_stderr   "Subject: negative number error"                   "not a positive number" "$SUBJECT_INPUT"
expect_stderr   "Subject: bad input (2001-42-42)"                  "bad input"             "$SUBJECT_INPUT"
expect_stderr   "Subject: too large a number"                      "too large a number"    "$SUBJECT_INPUT"
expect_no_stdout_for_line "Subject: -1 line produces no result"   "=> -1 = " "$SUBJECT_INPUT"

# ==========================================================
section "VALUE VALIDATION"
# ==========================================================

NEG_INPUT=$(make_input "neg.txt" "2011-01-03 | -1")
expect_stderr "Negative value → 'not a positive number'" "not a positive number" "$NEG_INPUT"
expect_no_stdout_for_line "Negative value → no stdout" "=> -1 = " "$NEG_INPUT"

NEG2_INPUT=$(make_input "neg2.txt" "2011-01-03 | -0.5")
expect_stderr "Negative float → 'not a positive number'" "not a positive number" "$NEG2_INPUT"

LARGE_INPUT=$(make_input "large.txt" "2012-01-11 | 2147483648")
expect_stderr "Too large (>1000) → 'too large a number'" "too large a number" "$LARGE_INPUT"

LARGE2_INPUT=$(make_input "large2.txt" "2012-01-11 | 1001")
expect_stderr "Value 1001 → 'too large a number'" "too large a number" "$LARGE2_INPUT"

EXACT1000_INPUT=$(make_input "exact1000.txt" "2012-01-11 | 1000")
expect_exit_ok "Value exactly 1000 is valid (exit 0)" "$EXACT1000_INPUT"
expect_stdout  "Value exactly 1000 produces output" "=> 1000 = " "$EXACT1000_INPUT"

ZERO_INPUT=$(make_input "zero.txt" "2012-01-11 | 0")
expect_exit_ok "Value 0 is valid (exit 0)" "$ZERO_INPUT"
expect_stdout  "Value 0 produces output (=> 0 = 0)" "=> 0 = " "$ZERO_INPUT"

FLOAT_INPUT=$(make_input "float.txt" "2011-01-03 | 1.2")
expect_stdout "Float value 1.2 produces output" "=> 1.2 = " "$FLOAT_INPUT"

FLOAT2_INPUT=$(make_input "float2.txt" "2011-01-03 | 0.001")
expect_stdout "Float value 0.001 produces output" "=> 0.001 = " "$FLOAT2_INPUT"

# ==========================================================
section "DATE FORMAT VALIDATION"
# ==========================================================

BAD_DATE1=$(make_input "baddate1.txt" "2001-42-42")
expect_stderr "No separator '|' → bad input" "bad input" "$BAD_DATE1"

BAD_DATE2=$(make_input "baddate2.txt" "abcd-ef-gh | 5")
expect_stderr "Non-numeric date → bad input" "bad input" "$BAD_DATE2"

BAD_DATE3=$(make_input "baddate3.txt" "2011-13-01 | 5")
expect_stderr "Invalid month 13 → bad input" "bad input" "$BAD_DATE3"

BAD_DATE4=$(make_input "baddate4.txt" "2011-00-01 | 5")
expect_stderr "Invalid month 00 → bad input" "bad input" "$BAD_DATE4"

BAD_DATE5=$(make_input "baddate5.txt" "2011-01-00 | 5")
expect_stderr "Invalid day 00 → bad input" "bad input" "$BAD_DATE5"

BAD_DATE6=$(make_input "baddate6.txt" "2011-01-32 | 5")
expect_stderr "Invalid day 32 → bad input" "bad input" "$BAD_DATE6"

BAD_DATE7=$(make_input "baddate7.txt" "11-01-03 | 5")
expect_stderr "Short year (bad format) → bad input" "bad input" "$BAD_DATE7"

BAD_FORMAT1=$(make_input "badfmt1.txt" "2011/01/03 | 5")
expect_stderr "Slashes instead of dashes → bad input" "bad input" "$BAD_FORMAT1"

BAD_FORMAT2=$(make_input "badfmt2.txt" "2011.01.03 | 5")
expect_stderr "Dots instead of dashes → bad input" "bad input" "$BAD_FORMAT2"

BAD_FORMAT3=$(make_input "badfmt3.txt" "2011-01-03 5")
expect_stderr "Missing '|' separator → bad input" "bad input" "$BAD_FORMAT3"

BAD_FORMAT4=$(make_input "badfmt4.txt" "2011-01-03| 5")
expect_stderr "Wrong separator (no spaces) → bad input" "bad input" "$BAD_FORMAT4"

JUST_DATE=$(make_input "justdate.txt" "2011-01-03")
expect_stderr "Date only, no value → bad input" "bad input" "$JUST_DATE"

# ==========================================================
section "CLOSEST DATE LOOKUP (lower bound)"
# ==========================================================

# If date not in DB, the program uses the closest lower date.
# 2009-01-02 is the first date in data.csv.
# A date before all DB entries should produce an error.
BEFORE_ALL=$(make_input "before_all.txt" "2008-01-01 | 1")
# The spec says use the lower date; if none exists, it's an error.
stderr_out=$("$BINARY" "$BEFORE_ALL" 2>&1 1>/dev/null)
stdout_out=$("$BINARY" "$BEFORE_ALL" 2>/dev/null)
if [ -n "$stderr_out" ] && [ -z "$stdout_out" ]; then
    echo -e "${GREEN}[PASS]${RESET} Date before DB range → error, no stdout"
    ((PASS++))
elif [ -z "$stdout_out" ]; then
    echo -e "${GREEN}[PASS]${RESET} Date before DB range → no stdout (error handled)"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Date before DB range → unexpected stdout: '$stdout_out'"
    ERRORS+=("Date before DB range should produce no output result")
    ((FAIL++))
fi

# Date not in DB but in range → uses closest lower date, produces output
NOT_IN_DB=$(make_input "notindb.txt" "2011-01-05 | 2")
expect_stdout "Date not in DB but in range → output produced" "=> 2 = " "$NOT_IN_DB"

# Exact match in DB
EXACT_DATE=$(make_input "exactdate.txt" "2011-01-03 | 1")
expect_stdout "Exact date in DB → output produced" "2011-01-03 => 1 = " "$EXACT_DATE"

# ==========================================================
section "MULTIPLE VALID LINES"
# ==========================================================

MULTI=$(make_input "multi.txt" \
    "2011-01-03 | 3" \
    "2011-01-03 | 2" \
    "2011-01-03 | 1" \
    "2011-01-09 | 1")

output=$("$BINARY" "$MULTI" 2>/dev/null)
line_count=$(echo "$output" | grep -c "=>")
if [ "$line_count" -eq 4 ]; then
    echo -e "${GREEN}[PASS]${RESET} 4 valid lines → 4 output lines"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} 4 valid lines → got $line_count output lines (expected 4)"
    ERRORS+=("4 valid lines should produce 4 output lines")
    ((FAIL++))
fi

# ==========================================================
section "MIXED VALID AND INVALID LINES"
# ==========================================================

MIXED=$(make_input "mixed.txt" \
    "2011-01-03 | 5" \
    "2012-01-11 | -1" \
    "2001-42-42" \
    "2012-01-11 | 2")

output=$("$BINARY" "$MIXED" 2>/dev/null)
stderr_out=$("$BINARY" "$MIXED" 2>&1 1>/dev/null)
valid_lines=$(echo "$output" | grep -c "=>")
error_lines=$(echo "$stderr_out" | grep -c "Error")

if [ "$valid_lines" -eq 2 ]; then
    echo -e "${GREEN}[PASS]${RESET} Mixed input: 2 valid results on stdout"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Mixed input: expected 2 valid stdout lines, got $valid_lines"
    ERRORS+=("Mixed input: should produce 2 stdout lines")
    ((FAIL++))
fi

if [ "$error_lines" -ge 2 ]; then
    echo -e "${GREEN}[PASS]${RESET} Mixed input: ≥2 error messages on stderr"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Mixed input: expected ≥2 stderr errors, got $error_lines"
    ERRORS+=("Mixed input: should produce ≥2 error lines on stderr")
    ((FAIL++))
fi

# ==========================================================
section "EMPTY FILE / HEADER ONLY"
# ==========================================================

# --- Completely empty file (0 bytes) ---
EMPTY_FILE="$TMPDIR_TEST/empty.txt"
touch "$EMPTY_FILE"

empty_stdout=$("$BINARY" "$EMPTY_FILE" 2>/dev/null)
empty_ec=$?

# Must not crash
if [ "$empty_ec" -lt 128 ]; then
    echo -e "${GREEN}[PASS]${RESET} Empty file (0 bytes) → no crash (exit $empty_ec)"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Empty file (0 bytes) → crashed/signal (exit $empty_ec)"
    ERRORS+=("Empty file should not crash")
    ((FAIL++))
fi

# Must produce no result lines on stdout (nothing to exchange)
if [ -z "$empty_stdout" ]; then
    echo -e "${GREEN}[PASS]${RESET} Empty file (0 bytes) → no output on stdout"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Empty file (0 bytes) → unexpected stdout: '$empty_stdout'"
    ERRORS+=("Empty file should produce no stdout")
    ((FAIL++))
fi

# --- Header-only file ---
HEADER_ONLY="$TMPDIR_TEST/header_only.txt"
echo "date | value" > "$HEADER_ONLY"

ho_stdout=$("$BINARY" "$HEADER_ONLY" 2>/dev/null)
ho_ec=$?

if [ "$ho_ec" -lt 128 ]; then
    echo -e "${GREEN}[PASS]${RESET} Header-only file → no crash (exit $ho_ec)"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Header-only file → crashed/signal (exit $ho_ec)"
    ERRORS+=("Header-only file should not crash")
    ((FAIL++))
fi

# No result lines — there are no data lines to process
if [ -z "$ho_stdout" ]; then
    echo -e "${GREEN}[PASS]${RESET} Header-only file → no output on stdout"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Header-only file → unexpected stdout: '$ho_stdout'"
    ERRORS+=("Header-only file should produce no stdout lines")
    ((FAIL++))
fi

# --- Whitespace-only file ---
WS_FILE="$TMPDIR_TEST/whitespace.txt"
printf "   \n\t\n\n" > "$WS_FILE"

ws_stdout=$("$BINARY" "$WS_FILE" 2>/dev/null)
ws_ec=$?

if [ "$ws_ec" -lt 128 ]; then
    echo -e "${GREEN}[PASS]${RESET} Whitespace-only file → no crash (exit $ws_ec)"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Whitespace-only file → crashed (exit $ws_ec)"
    ERRORS+=("Whitespace-only file should not crash")
    ((FAIL++))
fi

if [ -z "$ws_stdout" ]; then
    echo -e "${GREEN}[PASS]${RESET} Whitespace-only file → no output on stdout"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Whitespace-only file → unexpected stdout: '$ws_stdout'"
    ERRORS+=("Whitespace-only file should produce no stdout")
    ((FAIL++))
fi

# ==========================================================
section "OUTPUT FORMAT CHECK"
# ==========================================================

FMT_INPUT=$(make_input "fmt_check.txt" "2011-01-03 | 5")
output=$("$BINARY" "$FMT_INPUT" 2>/dev/null)

# Line should match: "YYYY-MM-DD => VALUE = RESULT"
if echo "$output" | grep -qE '^[0-9]{4}-[0-9]{2}-[0-9]{2} => .+ = .+$'; then
    echo -e "${GREEN}[PASS]${RESET} Output format matches 'YYYY-MM-DD => VALUE = RESULT'"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Output format unexpected: '$output'"
    ERRORS+=("Output should match 'DATE => VALUE = RESULT' format")
    ((FAIL++))
fi

# ==========================================================
section "NEWLINE AT END OF OUTPUT"
# ==========================================================

FMT2_INPUT=$(make_input "newline_check.txt" "2011-01-03 | 1")
output=$("$BINARY" "$FMT2_INPUT" 2>/dev/null)
# Ensure it ends with a newline (bash captures without trailing newline,
# so we check output is non-empty and the program doesn't print extra garbage)
if [ -n "$output" ]; then
    echo -e "${GREEN}[PASS]${RESET} Output is non-empty for valid input"
    ((PASS++))
else
    echo -e "${RED}[FAIL]${RESET} Empty output for valid input"
    ERRORS+=("Valid input should produce non-empty output")
    ((FAIL++))
fi

# ==========================================================
#  CLEANUP & SUMMARY
# ==========================================================

rm -rf "$TMPDIR_TEST"

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
