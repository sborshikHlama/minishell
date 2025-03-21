#!/bin/bash

LOG_FILE="syntax_test.log"
MINISHELL=".././minishell"  # Update path to your Minishell executable

# Ensure Minishell is executable
if [ ! -x "$MINISHELL" ]; then
    echo "Error: Minishell not found or not executable." | tee -a "$LOG_FILE"
    exit 1
fi

GREEN="✅"
RED="❌"
RESET="\e[0m"

# Function to run a test and log results
run_test() {
    local test_cmd="$1"
    local expected_output="$2"

    echo "Running: $test_cmd" | tee -a "$LOG_FILE"

    # Run the command inside Minishell and capture output before "exit"
    actual_output=$(timeout 2s bash -c "echo \"$test_cmd\" | $MINISHELL" | tail -n +2 | sed 's/minishell\$>//g' | tr -d '\n' | xargs)
	
	echo "This is output: " $actual_output

    if [ "$actual_output" == "$expected_output" ]; then
        echo -e "$GREEN PASS$RESET | Expected: $expected_output | Got: $actual_output" | tee -a "$LOG_FILE"
    else
        echo -e "$RED FAIL$RESET | Expected: $expected_output | Got: $actual_output" | tee -a "$LOG_FILE"
    fi

    echo "--------------------------------------" | tee -a "$LOG_FILE"
}

# Start logging
echo "======================================" > "$LOG_FILE"
echo "📜 Minishell Syntax Handling Tests" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
date >> "$LOG_FILE"
echo "" >> "$LOG_FILE"

# Test Cases
run_test "echo hello" "hello"
# run_test "ls | wc -l" "$(ls | wc -l)"
# run_test "ls > file.txt" ""  # Should create file.txt
run_test "echo \"hello" "minishell: syntax error: unclosed quote"
# run_test "ls |" "minishell: syntax error near unexpected token"
run_test ">" "minishell: syntax error near unexpected token"
run_test "cat <" "minishell: syntax error near unexpected token"
run_test "echo >" "minishell: syntax error near unexpected token"
run_test "echo \"Hello $USER\"" "Hello $(whoami)"
run_test "echo '$USER'" "arsenii"
run_test "echo hello |" "minishell: syntax error near unexpected token"
run_test "echo hello | | " "minishell: syntax error near unexpected token"

# Summary
echo "======================================" >> "$LOG_FILE"
echo "📊 Test Summary" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
grep -E "$GREEN PASS|$RED FAIL" "$LOG_FILE" >> "$LOG_FILE"
echo "✅ Tests Completed. Check $LOG_FILE for results." | tee -a "$LOG_FILE"
