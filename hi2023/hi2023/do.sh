#echo "get nevents from raw"
./getnEventsFromRawDAS.sh
#echo "get raw size for each pd"
./getRawSizeFromDAS.sh

#echo "get nevents from aod"
./getnEventsFromAodDAS.sh
#echo "get aod size for each pd"
./getAodSizeFromDAS.sh

#echo "get miniaod size for each pd"
./getMiniAodSizeFromDAS.sh
#echo "get miniaod size for each pd at vandy"
./getMiniAodSizeAtVandy.sh

