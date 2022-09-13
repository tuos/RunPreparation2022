#! /bin/bash

outFile="pickevents_centAll.root"
events=`cat "events_centAll_Selected.txt"`
inputfiles=`cat "inputfilelist.txt"`
edmCopyPickMerge outputFile=$outFile eventsToProcess=${events::-1} inputFiles=$inputfiles



#edmCopyPickMerge outputFile=pickevents.root eventsToProcess=327464:51:19828178,327464:51:19721794,327554:1234:633350775 inputFiles=/store/hidata/HIRun2018A/HIMinimumBias9/AOD/04Apr2019-v1/60000/6E57258E-521F-A045-93D9-6F3AF3D13BEE.root,/store/hidata/HIRun2018A/HIMinimumBias12/AOD/04Apr2019-v1/30009/311A32E0-6F20-4148-9481-938F56BBFE60.root



