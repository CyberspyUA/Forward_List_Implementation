I made own implementation of a single-linked list for Apriorit training task. <br />
This class defines such operations: <br />
a) Basic operations with a list: constructor, inserting items at the beginning of the list, iterating through the list, list size, deleting items. <br />
b) Move operations (move-constructor, move-assignment) <br />
c) The method for inserting items at the beginning must have an overload for the rvalue reference and correctly handle move. <br />
d) Creating a list using a constructor that takes std::initializer_list. <br />
e) The list templated and works not only with primitive values, but also with objects (and free memory correctly) <br />
f) Similar to class interface like std::forward_list, but without some methods - the custom constructor, emplace_* methods, are optional (but this will not be a disadvantage). Sort, merge, and unique do not need to be implemented.<br />
g) Implemented a split_when method that allows you to split a list into two, which determines the position from which to split the item based on the boolean value returned by the passed predicate function. The predicate itself can be passed using std::function <br />
