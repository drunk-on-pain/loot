# loot

Library Of Ordinary Tools

Collection of (hopefully) useful C++ modules to implement a certain task. 
Mostly this serves as a playground for exploring the [Objective] C [++] 
language[s] and programming techniques therein.

# Command Line Parser

A set of classes that handle command line arguments based on a set of 
rules. There are two terms one has to be acquainted with: option and
value. An option is specified with an option-switch ("-" for short 
version or "--" for the long version). An option can appear as a 
standalone entity or require one or more values specified with it.

The module allows to specify whether an option must appear on the 
command line or can be optional. In addition to that it is possible to 
combine this with how many values a certain option requires. The module
then evaluates the command line arguments against these rules and 
returns a list of error-reasons for all violations found. Client code
can then decide how to proceed. Either way, found options and their
associated values are available for use.

[See the Wiki for details][clpusage]

# Know Issues

Compiling the test suite on XCode does not work. See [this StackOverflow question][xctst]
for an explanation. Compiling on the command line on OS X works without problems.

[xctst]: http://stackoverflow.com/questions/11697657/xcode-4-3-is-not-finding-header-files-in-usr-include?rq=1
[clpusage]: https://github.com/drunk-on-pain/loot/wiki/Command-Line-Parser