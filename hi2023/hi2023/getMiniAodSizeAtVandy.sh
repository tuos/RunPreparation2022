
declare -i totalHIEphemeralZeroBias=0
for value in {0..1}
do
  queryName='dasgoclient --query="file dataset=/HIEphemeralZeroBias'$value'/HIRun2023A-PromptReco-v1/MINIAOD site=T2_US_Vanderbilt | sum(file.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIEphemeralZeroBias=$(($totalHIEphemeralZeroBias+$num))
done

declare -i totalHIForward=0
for value in {0..2}
do
  queryName='dasgoclient --query="file dataset=/HIForward'$value'/HIRun2023A-PromptReco-v1/MINIAOD site=T2_US_Vanderbilt | sum(file.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIForward=$(($totalHIForward+$num))
done

declare -i totalHIMinimumBias=0
for value in {0..3}
do
  queryName='dasgoclient --query="file dataset=/HIMinimumBias'$value'/HIRun2023A-PromptReco-v1/MINIAOD site=T2_US_Vanderbilt | sum(file.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIMinimumBias=$(($totalHIMinimumBias+$num))
done

declare -i totalHIPhysicsRawPrime=0
for value in {0..31}
do
  queryName='dasgoclient --query="file dataset=/HIPhysicsRawPrime'$value'/HIRun2023A-PromptReco-v1/MINIAOD site=T2_US_Vanderbilt | sum(file.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIPhysicsRawPrime=$(($totalHIPhysicsRawPrime+$num))
done

declare -i totalHIForwardAOD=0
for value in {0..2}
do
  queryName='dasgoclient --query="file dataset=/HIForward'$value'/HIRun2023A-PromptReco-v1/AOD site=T2_US_Vanderbilt | sum(file.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIForwardAOD=$(($totalHIForwardAOD+$num))
done

echo -ne "$totalHIEphemeralZeroBias""\t"
echo -ne "$totalHIForward""\t"
echo -ne "$totalHIMinimumBias""\t"
echo -ne "$totalHIPhysicsRawPrime""\t"
echo -ne "$totalHIForwardAOD""\t"
echo ""

