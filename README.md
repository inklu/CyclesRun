# CyclesRun
It's designed for periodically invoking void static functions in a predifined time.

Base class is CyclesRun. It can by used directly through CyclesRun::addCycle passing an array of functions or can be inherited from the base class and used one of the following overloaded methods: onEveryMls(), onEveryCycle().

The public methods CyclesRun::start() and pause() are designed respectivly for starting and pausing the invocation of functions.
