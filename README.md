## What is this?
This is the source code for `Quiz 201 - 15 puzzle`.\
You will not find here anything that will compile and build successfully. That is because the entire quiz is divided by modules - a single chunk of code (a file with .cpp extension) that user should write per step **or** a chunk of unit-test code provided by the teacher.

i divide quiz into modules for several reasons:
- It's easier to copy an isolated module code into your IDE
- It exactly matches the layout in the lesson\*
- It's easy to track changes for a separate module
<a/>

\*_(e.g. There is a quiz that consists of 4 steps. When you expand code block called "Solution for step 2" it does not contain the code from step 1 because it's irrelevant for step 2 and was already implemented. Unit-test code for step 2 (with main() function in it) is completely different from unit-test code for step 1. Thus, unit-test code does not test things from step 1)_

## How to get the code?
In order to generate code for a specific step (or entire quiz), download this repository as .zip (or just clone it) and run `Code generator.exe` file (or Code generator.ahk if you have AutoHotkey installed). Choose which step you would like to have code for. After clicking the button "Copy to clipboard" the entire code will be copied to your clipboard, and now you can paste it wherever you want!

**_Optional reading:_**\
You can also do it manually, but it's a pain in the butt - that's why i created a program that does that for you. This is rather to help you understand what's going on under the hood.\
Let's say you want the buildable code for step 3 in a quiz that has 4 steps in total. Here's what you have to do:
- copy and paste step 1 to your IDE
- copy and paste step 2 to your IDE
- copy and paste step 3 to your IDE
- copy and paste unit-test for 3 to your IDE
- because it's a simple copy-paste you will end up with a messy code because `#include` directives will be all over the place. So move all `#include`s at the top of the file

That's it. The code should build successfully.
