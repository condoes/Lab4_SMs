#Test file for "Lab4"

echo ======================================================\n
echo Running all tests..."\n\n

# Test sequence from unlocked to locked (with #Y) => PORTB: 0
test "PINA: 0x04, 0x0, 0x02, 0x0 => PORTB: 0, state: locked"
set state = unlocked
setPINA 0x04
expect state PA2_Press
continue 2
setPINA 0x0
expect state PA2_Released
continue 2
setPINA 0x02
expect state Y_Pressed
continue
setPINA 0x0
expect state locked
expect PORTB 1
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n