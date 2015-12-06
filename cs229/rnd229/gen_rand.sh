#! /bin/bash

for VAR in {1..20}
do
	./rnd229 -o rnd$VAR.cs229 -f 100 --min-channels 4 --min-length 60 -l 120
done
