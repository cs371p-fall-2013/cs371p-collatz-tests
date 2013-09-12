# 
# If it doesn't work, you're going to need to fix it yourself
# You can modify NUM_DIFFS to display more or fewer differences if they occur
# 
# mass_collatz.sh
#   by Nathan Petryk
# 
# Simply runs your compiled RunCollatz against all the *-RunCollatz.{in,out}
#  files
#
# to invoke:
# $ ./mass_collatz.sh ../../cs371p-collatz/RunCollatz
# 
#
# The first argument is your compiled RunCollatz File
#
# If you're running it from outside the *-tests repo, the second argument
# is the path to the *-tests directory
#
#
#

TEMPFILE="_mass_collatz_temp.out"
TEMPERR="_mass_collatz_temp.err"
TIMEFILE="_mass_collatz_temp.time"

NUM_DIFFS=5

test_for_differences() {
  dir=$(dirname "$2")
  name=$(basename "$2")
  ext="${name##*.}"
  name="${name%.*}"

  in="$dir/$name.in"
  out="$dir/$name.out"

  num_tests=$(wc -l $in | sed -r "s/(\d*) .*/\1/g")
  printf "Running %-22s (%6d lines) - " $name $num_tests

  if ! [ -f $out ]; then
    printf "Missing $out\n"
    return
  fi

  time_raw=$((time $1 < $in > $TEMPFILE 2> $TEMPERR) 2>&1)
  if [ -s $TEMPERR ]; then
    echo "Got STDERR output during run: "
    cat "$TEMPERR"
    echo ""
    return
  fi

  time=$(echo "$time_raw" | grep user | sed "s/user\s*//g")
  if [[ $? -ne 0 ]]; then
    log="$name.errorlog"
    cp $TIMEFILE $log
    echo "ERROR. Log is $log"
  fi

  diffs_raw=$(diff -yb $TEMPFILE $out | grep "|" | sed -r "s/\s+/ /g" )
  if [ ${#diffs_raw} -gt 0 ]; then
    diffs=$(echo "$diffs_raw" | wc -l)
    printf "%d differences in %s (Showing up to %d)\n" $diffs $time $NUM_DIFFS
    echo "Your Output | Expected Output"
    echo "$diffs_raw" | head -n $NUM_DIFFS
    echo ""
  else
    printf "ALL GOOD in %s\n" $time
  fi
}
  

PROG=$1
INFILES=$2*-RunCollatz.in

for f in $INFILES
do
  test_for_differences $PROG $f
done
rm -rf $TEMPFILE
rm -rf $TIMEFILE
rm -rf $TIMEERR


