#! /bin/bash

events=`cat "testx.txt"`
inputfiles=`cat "testy.txt"`

edmCopyPickMerge outputFile=pickevents.root eventsToProcess=$events inputFiles=$inputfiles



