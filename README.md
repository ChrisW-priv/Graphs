# Graph project
project designed to be a general interface for any graph, no matter the implementation.

I strive to build one, universal interface to allow any graph representation to 
work and thus allow for better separation of logic and actual implementation.

## Work needed!
This is practicaly R&D project! do not use it as yours! If you want to
constribute your work pls write to me! I would love some help on this!!!

## Glosary
Vertex - node that can have relation to other nodes
[...]

## TODO
Currently, I only have an experimental design. 
I need to design interface MUCH better.

Current iterator is just counter that relies heavily on correctness of
initlailsation and maintnance on remove of relation or vertex

Current thought: if I have spaces in my Vertex indexes like { 0, 2, 4, 6, 8, } 
implementation that I have will corretly recognise that I have 5 nodes but when
printing (looping over) I will only be able to access nodes 0,1,2,3,4. So here,
that is just 0,2,4. 

Either I accept this and force maintainers to keepup, or I need to reinvent
iteration.

Problem is that I cannot just inherit any from iterator because then iteration 
over Vertex in EdgeList implementation is a mess.

I could force implementation creators to choose and create their own iterator +
begin/end methods.
That could be a lot of repeated code but actually maybe not? 

I need to check if derived class can overide abstract iterator without issue.

Then, if it is possible, leave current implementation and suggest using
std::vector::iterator (in most cases that will be the one that makes most sense)

I can also ignore this issue and say that is someone represents his graph with 
even nodes only that it is his/her problem and interface will not allow that.

but that is stupid and not a way to go (what if I need to copy graph but only
if nodes are even? Then I would be the stupid one, that is what)


