#!/bin/bash
f=c17;./a111204.o ../prog2_2022/$f.v -p ../prog2_2022/$f.pat -l ../prog2_2022/test_lib.lib
f=c432;./a111204.o ../prog2_2022/$f.v -p ../prog2_2022/$f.pat -l ../prog2_2022/test_lib.lib
f=example;./a111204.o ../prog2_2022/$f.v -p ../prog2_2022/$f.pat -l ../prog2_2022/test_lib.lib

echo "[START DIFF LOAD]"
diff a111204_c17_load.txt ../golden_answer/golden_c17_load.txt
diff a111204_c432_load.txt ../golden_answer/golden_c432_load.txt
diff a111204_example_load.txt ../golden_answer/golden_example_load.txt

echo "[START DIFF DELAY]"
diff a111204_c17_delay.txt ../golden_answer/golden_c17_delay.txt
diff a111204_c432_delay.txt ../golden_answer/golden_c432_delay.txt
diff a111204_example_delay.txt ../golden_answer/golden_example_delay.txt

#diff a111204_c17_path.txt ../golden_answer/golden_c17_path.txt
#diff a111204_c432_path.txt ../golden_answer/golden_c432_path.txt
#diff a111204_example_path.txt ../golden_answer/golden_example_path.txt
