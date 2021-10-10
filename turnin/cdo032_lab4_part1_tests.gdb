#Test file for "Lab4"

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below
# Test sequence from Start => PORTB: 1
test "PINA: 0x01=> PORTB: 1, state: PB0_on"
set state = Start
setPINA 0x01
expectPORTB 0x1
checkResult

# Test sequence from PB0_off to PB1_on => PORTB: 0x2
test "PINA: 0x0, 0x1 => PORTB: 2, state: PB1_on"
set state = PB0_off
setPINA 0x0
expect state PB0_off
continue 2
setPINA 0x1
expectPORTB 0x2
expect state PB1_on
checkResult

# Test sequence from PB1_on to PB0_on => PORTB: 0x1
test "PINA: 0x0, 0x1 => PORTB: 1, state: PB0_on"
set state = PB1_on
setPINA 0x0
expect state PB1_off
continue 2
setPINA 0x1
expectPORTB 0x1
expect state PB0_on
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n