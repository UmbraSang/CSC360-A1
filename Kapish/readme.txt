Kapish
Connor McLeod
V00725080

Readme

The Initial Shell:

    The first function called by our main is argsReader() whose
main function is to prepare for then take in input from the User
in intakeline(), break that input into a set of args in getTokens(),
then run it through kapexec(). After which it frees our malloc'd
memory and checks to make sure the shell should still be running.
If so we do it all again, otherwise gracefully exit.

Preparing Args:

    Getting the line from the user is easy with the getline()
function. Helpfully, if the getline is EOF we recieve -1 and
know control-D has been pressed. This will exit kapish.
    Provided we actually got input, we jump into getTokens().
Using a while loop lets us pull until the input has no more tokens,
and I used the DoublyLinkedList from our pointer gymnastic assignment.
Using the DoublyLinkedList was admittedly a little extra, however I
put a lot of hours into it and i'll be damnned if it's not used!

Command Execution:

    Passing the args List into kapexec() is the next step to actually
run the command given. However, kapexec() is supposed to accept an array,
so I created the listToArray() function to bridge the gap. listToArray()
pops tokens into the char** array, freeing as it goes, then the array is
returned into kapexec(). kapexec() checks the first index (the command)
against the built-ins, if there's a match we jump into builtInFuncSwitch(),
else we fall into launch().
    builtInFuncSwitch() is a switch statement using the index of the match
in kapexec() to very quickly choose the correct built-in function, each of
which uses an already existing call to complete its task.
    launch() on the other hand is a touch more complex. After forking a child
the parent waits for it to finish it's task. Meanwhile the child will call
the execvp() and pass it the command (args[0]) and the remaining to self process.

Final Thoughts:

    Although C is not my language of choice, I'm very interested in further
exploring the fork() functionality in other programming assignmnets. I'm sure
we've only scratched the surface of what kinds of shenanigans forks() can
allow us to get up to, and I'm excited to get involved!

help citations:

Tutorial given to class - https://brennan.io/2015/01/16/write-a-shell-in-c/
many many google searches - https://stackoverflow.com/
Worked with friends in class - Dayton Depradine, Jamie Kirkwin