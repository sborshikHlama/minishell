#!/bin/bash

# Log file
LOG_FILE="pipeline_test.log"
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
    local expected_output="$2"

    echo "Running: $test_cmd" | tee -a "$LOG_FILE"

    # Run command in minishell and clean output
 actual_output=$(timeout 2s bash -c "echo \"$test_cmd\" | $MINISHELL" | tail -n +2 | sed 's/minishell\$>//g' | tr -d '\n' | xargs)

    if [ "$actual_output" == "$expected_output" ]; then
        echo -e "$GREEN PASS$RESET | Expected: '$expected_output' | Got: '$actual_output'" | tee -a "$LOG_FILE"
    else
        echo -e "$RED FAIL$RESET | Expected: '$expected_output' | Got: '$actual_output'" | tee -a "$LOG_FILE"
    fi

    echo "--------------------------------------" | tee -a "$LOG_FILE"
}



# Start logging
echo "======================================" > "$LOG_FILE"
echo "📜 Minishell Pipeline Execution Tests" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
date >> "$LOG_FILE"
echo "" >> "$LOG_FILE"

# 🚀 **Pipeline Tests**
run_test "echo 'hello' | cat" "hello"
run_test "echo '123' | rev" "321"
run_test "echo 'a b c' | tr ' ' '-'" "a-b-c"
run_test "echo 'hello' | grep h" "hello"
run_test "echo 'world' | grep x" ""  # Empty output if no match
run_test "echo '42' | cat | cat | cat" "42"
run_test "ls | wc -l" "$(ls | wc -l)"  # Compare to real shell output
run_test "echo 'test' | head -n 1" "test"
run_test "echo 'a' | echo 'b'" "b"  # Should print only 'b' due to shell behavior
run_test "echo hello | cat | cat | cat | cat" "hello"
run_test "echo test | tr 'a-z' 'A-Z'" "TEST"
run_test "ls | sort | head -n 1" "$(ls | sort | head -n 1)"
run_test "echo 'first' | echo 'second'" "second"
run_test "echo 'HELLO' | tr 'A-Z' 'a-z' | rev" "olleh"

# Summary
echo "======================================" >> "$LOG_FILE"
echo "📊 Test Summary" >> "$LOG_FILE"
echo "======================================" >> "$LOG_FILE"
grep -E "$GREEN PASS|$RED FAIL" "$LOG_FILE" >> "$LOG_FILE"
echo "✅ Pipeline Tests Completed. Check $LOG_FILE for results." | tee -a "$LOG_FILE"
