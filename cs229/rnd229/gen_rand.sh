#! /bin/bash

for VAR in {1..20}
do
	./rnd229 -o rnd$VAR.cs229 -n -f 164 --min-channels 4 --min-length 60 -l 120
	# files are seeded with the current time (seconds), make sure they are different
	sleep 1s
done
