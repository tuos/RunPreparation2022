#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc11
export SSL_CERT_DIR=/etc/grid-security/certificates
export X509_USER_PROXY=/home/tuos/x509up_u126986

cd /nobackup/user/tuos/run2023/monitors/CMSSW_13_2_3/src/PbPbRun2023/DATAFLOWMONITOR/hi2023
eval `scramv1 runtime -sh`

dateAndTime=$(date +"%Y%m%d_%H%M%S")

echo "running do.sh"
fileName_do="output_do_$dateAndTime.txt"
./do.sh > "$fileName_do"

