This is the Doubly Linked List library I made for the Arduino.
I originally wrote it for the Arduino, but you should be able to use it in any C++ project you have.
This is an abstract class, meaning you can initialize it to hold any particular data type you wish.
This linked list also deletes itself and all items within the list, which is why it was originally meant for an Arduino with limited memory.

Usage:
  To make a list to hold integers:
  
  DLinkedList<int> list;
  
  And similarly for chars:
  
  DLinkedList<char> list;
  
  And floats:
  
  DLinkedList<float> list;
  
  And for your own custom data types:
  
  DLinkedList<custom type> list;
