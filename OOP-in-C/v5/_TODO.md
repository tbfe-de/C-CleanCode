## Activities with Version 5

### Run the Unit Tests

First examine the new tests that have been added for

* `range_checked_atol` and
* `range_checked_atof`

**Note**: It's not quite *YAGNI* (you ain't going to need it) that
there is already functionality implemented that is not needed in
the current project. As an excuse just assume the new requirements
(which then need this new functionality) is already known at this
pont in time.

### Run the Demo Application

Try both, "good" and "bad" input, both as command line arguments
and from the environment variable `DDD_HH_MM_SS_PRELOAD`. How
environment variable are set may vary with the Shell you use.

Typically something this works:

```sh
DDD_HH_MM_SS_PRELOAD='10 20 30 40'
export DDD_HH_MM_SS_PRELOAD
```

If you want to know whether the variable was set use:

```sh
env | grep DDD_HH_MM_SS_PRELOAD
```

## Following Plan A – Get active with some hands-on coding
## Following Plan B - Understand what should have been done
