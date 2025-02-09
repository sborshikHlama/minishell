#!/bin/bash

# Log file
LOG_FILE="env_test.log"
MINISHELL=".././minishell"  # Path to your minishell executable

# Ensure minishell exists
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
    local expected_output="$2"  # Add expected output

    echo "Running: $test_cmd" | tee -a "$LOG_FILE"

    # Capture the output before "exit"
	actual_output=$(echo "$test_cmd" | $MINISHELL | head -1)
    # Check if output matches expectation
    if [ "$actual_output" == "$expected_output" ]; then
        echo -e "$GREEN PASS$RESET | Expected: $expected_output | Got: $actual_output" | tee -a "$LOG_FILE"
    else
        echo -e "$RED FAIL$RESET | Expected: $expected_output | Got: $actual_output" | tee -a "$LOG_FILE"
    fi

    echo "--------------------------------------" | tee -a "$LOG_FILE"
}

# Start logging
echo "======================================" > "$LOG_FILE"
echo "📜 Minishell Environment Handling Tests" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
date >> "$LOG_FILE"
echo "" >> "$LOG_FILE"

# Test Cases with Expected Outputs
run_test "echo \$USER" "$(whoami)"        # Check if $USER expands
run_test "echo \$HOME" "$HOME"            # Check if $HOME expands
run_test "echo \$PATH" "$PATH"            # Check if $PATH expands
run_test "echo \$NOT_SET" ""              # Check unset variable (should return empty)
run_test "echo \$?USER" "0USER"           # Check handling of $? followed by a variable
run_test "echo 'Hello \$USER'" "Hello \$USER"  # Single quotes should NOT expand variables
run_test "echo \"Hello \$USER\"" "Hello $(whoami)"  # Double quotes should expand variables

# Summary
echo "======================================" >> "$LOG_FILE"
echo "📊 Test Summary" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
grep -E "$GREEN PASS|$RED FAIL" "$LOG_FILE" >> "$LOG_FILE"
echo "✅ Tests Completed. Check $LOG_FILE for results." | tee -a "$LOG_FILE"
