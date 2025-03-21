#!/bin/bash

# Log file
LOG_FILE="redirection_test.log"
MINISHELL=".././minishell"  # Path to your minishell executable
TEST_FILE="testfile.txt"
APPEND_FILE="appendfile.txt"
INPUT_FILE="inputfile.txt"

# Ensure minishell exists
if [ ! -x "$MINISHELL" ]; then
    echo "Error: Minishell not found or not executable." | tee -a "$LOG_FILE"
    exit 1
fi

GREEN="✅"
RED="❌"
RESET="\e[0m"

# Function to run a test and check output
run_test() {
    local setup_cmd="$1"
    local test_cmd="$2"
    local expected_output="$3"
    local check_file="$4"

    echo "Running: $test_cmd" | tee -a "$LOG_FILE"

    # If a setup command is required, execute it first
    if [ -n "$setup_cmd" ]; then
        echo "$setup_cmd" | $MINISHELL > /dev/null 2>&1
    fi

    # Run minishell and clean output
    timeout 2s bash -c "echo \"$test_cmd\" | $MINISHELL" > minishell_output.txt 2>&1

    # Remove the last minishell prompt from output

    actual_output=$(timeout 2s bash -c "echo \"$test_cmd\" | $MINISHELL" | tail -n +2 | sed 's/minishell\$>//g' | tr -d '\n' | xargs)
    # If checking a file, read its contents instead
    if [ -n "$check_file" ]; then
        actual_output=$(cat "$check_file" | tr -d '\n' | xargs)
    fi

    # Detect timeout (124 is the exit code for `timeout`)
    if [ $? -eq 124 ]; then
        echo -e "$RED FAIL$RESET | Command Timed Out ❌" | tee -a "$LOG_FILE"
    elif [ "$actual_output" == "$expected_output" ]; then
        echo -e "$GREEN PASS$RESET | Expected: '$expected_output' | Got: '$actual_output'" | tee -a "$LOG_FILE"
    else
        echo -e "$RED FAIL$RESET | Expected: '$expected_output' | Got: '$actual_output'" | tee -a "$LOG_FILE"
    fi

    echo "--------------------------------------" | tee -a "$LOG_FILE"
}

# Start logging
echo "======================================" > "$LOG_FILE"
echo "📜 Minishell Redirection Tests" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
date >> "$LOG_FILE"
echo "" >> "$LOG_FILE"

# **Prepare Test Files**
echo "input content" > "$INPUT_FILE"
rm -f "$TEST_FILE" "$APPEND_FILE"

# 🚀 **Output Redirection Tests (`>` and `>>`)**
run_test "" "echo 'hello' > $TEST_FILE" ""  # Write to file
run_test "" "cat $TEST_FILE" "hello" "$TEST_FILE" # Check file content

run_test "" "echo 'line1' > $TEST_FILE" ""  # Overwrite file
run_test "" "echo 'line2' >> $TEST_FILE" ""  # Append to file
run_test "" "cat $TEST_FILE" "line1line2" "$TEST_FILE" # Check file content

# 🚀 **Input Redirection Tests (`<`)**
run_test "" "cat < $INPUT_FILE" "input content"

# 🚀 **Combining Redirections Without `;` or `&&`**
run_test "" "echo 'overwrite' > $TEST_FILE" ""  # Write to file
run_test "" "cat < $TEST_FILE" "overwrite"

run_test "" "echo 'append' >> $APPEND_FILE" ""  # Append to file
run_test "" "cat < $APPEND_FILE" "append"

# **Clean up**
rm -f "$TEST_FILE" "$APPEND_FILE" "$INPUT_FILE"

# Summary
echo "======================================" >> "$LOG_FILE"
echo "📊 Test Summary" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
grep -E "$GREEN PASS|$RED FAIL" "$LOG_FILE" >> "$LOG_FILE"
echo "✅ Redirection Tests Completed. Check $LOG_FILE for results." | tee -a "$LOG_FILE"
