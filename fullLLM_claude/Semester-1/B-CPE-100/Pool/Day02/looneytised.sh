#!/bin/bash

sed 's/theo1/Wile E. Coyote/g; s/steven1/Daffy Duck/g; s/arnaud1/Porky Pig/g; s/pierre-jean/Marvin the Martian/g' < /dev/stdin | grep -E "(Wile E. Coyote|Daffy Duck|Porky Pig|Marvin the Martian)"