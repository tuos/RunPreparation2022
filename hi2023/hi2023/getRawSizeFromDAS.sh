
declare -i totalHIEphemeralZeroBias=0
for value in {0..1}
do
  queryName='dasgoclient --query="dataset dataset=/HIEphemeralZeroBias'$value'/HIRun2023A-v1/RAW | sum(dataset.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIEphemeralZeroBias=$(($totalHIEphemeralZeroBias+$num))
done

declare -i totalHIForward=0
for value in {0..2}
do
  queryName='dasgoclient --query="dataset dataset=/HIForward'$value'/HIRun2023A-v1/RAW | sum(dataset.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIForward=$(($totalHIForward+$num))
done

declare -i totalHIMinimumBias=0
for value in {0..3}
do
  queryName='dasgoclient --query="dataset dataset=/HIMinimumBias'$value'/HIRun2023A-v1/RAW | sum(dataset.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIMinimumBias=$(($totalHIMinimumBias+$num))
done

declare -i totalHIPhysicsRawPrime=0
for value in {0..31}
do
  queryName='dasgoclient --query="dataset dataset=/HIPhysicsRawPrime'$value'/HIRun2023A-v1/RAW | sum(dataset.size)" '
  result=$(eval "$queryName")
  num=$(echo -e $result | tr -c -d 0-9)
  totalHIPhysicsRawPrime=$(($totalHIPhysicsRawPrime+$num))
done

echo -ne "$totalHIEphemeralZeroBias""\t"
echo -ne "$totalHIForward""\t"
echo -ne "$totalHIMinimumBias""\t"
echo -ne "$totalHIPhysicsRawPrime""\t"
echo ""

