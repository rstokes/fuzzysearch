fuzzysearch
===========

Fuzzy String Searching

The service takes a list of strings and indexes them by each word.  The Search method takes a string and does a lookup
by each word in the string.  The results are then scored using Dice's coefficient.

There is a .net implementation in C# and a jvm implementation in Scala.
