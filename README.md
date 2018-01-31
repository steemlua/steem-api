#### What is the project about?

	This project is a wrapper of steem APIs. It provides an easy way to use steem APIs for Lua developers.
	The current implementation is a wrapper of steem API and the returned values are all in JSON.
	
	Next release will be focus on making the lua developer's life easy:
	1) Convert the JSON string to lua table etc.
	2) Add some utilities function, for example get post payout, get user's vote power/weight etc.

#### Dependences:

	libcurl 7.54
	lua5.3

#### Compile:

- windows/msys compiling: gcc -shared steem.cpp -o steem.dll -lcurl -llua
- linux compiling: gcc -shared steem.cpp -o steem.so -lcurl -llua

#### Install:

	After compile, you will get the steem.dll on windows, and steem.so on linux.
	Just put the shared library in the same directory with lua script, it will works fine.
	
#### Version history:

    Please see CHANGELOG.md file
	
#### How to use it?

    Please see the DOC.md

#### How to contribute?

    Just fork this project, create your branch, commit your changes and send a pull request!

#### How to contact me?

    Just following me on steemit: https://steemit.com/@steemlua

#### Test:

	lua test.lua

#### Test result:

```
{"id":1,"result":702626}24
```