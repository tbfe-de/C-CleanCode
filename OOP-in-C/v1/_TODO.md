# Activities with Version 1

## Run the Unit Tests

```sh
make
```

The result should look something like this:

```txt
gcc -std=c99 -o assert_based unit_Test.c ChainCounter.c
** unit tests passed **
```

If you repeat the `make` command

## Run the Demo Application

```sh
make run-demo-app
```

The full result should end with something like this:

```txt
gcc -std=c99 -o app_main ChainCounter.c DDD_HH_MM_SS.c
  4d03h02m01s -- next: 6808 steps of 356521 remaining
  4d01h08m33s -- next: 5250 steps of 349713 remaining
  3d23h41m03s -- next:   74 steps of 344463 remaining
...
0d10h01m39s -- next: 7802 steps of 36099 remaining
  0d07h51m37s -- next: 6854 steps of 28297 remaining
  0d05h57m23s -- next:  978 steps of 21443 remaining
  0d05h41m05s -- next: 7409 steps of 20465 remaining
  0d03h37m36s -- next: 8229 steps of 13056 remaining
  0d01h20m27s -- next: 4827 steps of 4827 remaining
  0d00h00m00s -- DONE
```

This shows a "Countdown Clock" output (obviously) measuring in
*days*, *hours*, *minutes*, and *seconds*. The start time is 4
days, 3 hours, 2 minutes, and 1 second. (For brevity part of the
output has been deleted from the middle.)

You can run the demo application again with different start values
this way:

```sh
./app_demo 0 5 30 10
```

This runs the countdown starting from 5 hours, 30 minutes, and 15
seconds:

```txt
  0d05h30m15s -- next: 6808 steps of 19815 remaining
  0d03h36m47s -- next: 5250 steps of 13007 remaining
  0d02h09m17s -- next:   74 steps of 7757 remaining
  0d02h08m03s -- next: 3659 steps of 7683 remaining
  0d01h07m04s -- next: 4024 steps of 4024 remaining
  0d00h00m00s -- DONE
```

== More TBD ==
