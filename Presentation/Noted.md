# Main Class and Data Structure

Then let's go to the most tuff part of my presentation. It might be confusing, just cheer up!.

## Scene Node Tree

### Class Inherit Relation

First and formest, I would like to introduce the method that we use to manege the messy elements in our game, Scene Node Tree.

All of you must be pretty familiar with a node list, but how about a node tree? 

Before talk about the tree, let's discuss what a node is.

Please see the slide.

The flow chart demonstrate the relationship between classes which are real object in game. The base class SceneNode inherit /in'herit/ 
transformable, drawable and Nocoplable to make it an unique object present in game. 

Some element, like the background must be at a certain place so we have class Sprite Node;
Other element are allow to be placed in the map so that a new class named entity is developed with movement feature such as get voelocity and set rotation.
In addition, we derived class for tanks, bullets as known as projectile class, stone and cloud based on their feature.

Everyone can implement the feature without more resource so I will egnore that part. Let return to the tree.

### Class link relation

Since we know that a scene can be a tank, a bullet, or just the background, the sand, 
the question is how can we update and draw then in the correct order.

Let see the link relationship between this objects.

In our base class scene node, we saved its parent and chidren by one pointer and one pointer array. 
Yes, we use a pointer array to show its children because its a tree, not a link list.

when we want to update tree, we update it self, and then update its chilfren recursively. 
More spercificcal when we want to draw this tree in the slide, 
1. we draw root here, nothing,
2. and then the background node, ok we draw the sands as background
3. What is the next? Oh air layer, we draw tanks, bullets, stone so on and so forth
4. and finally we draw the top layer, clouds.

So far so good!

Are you interested in how do we delete a node like bullet? 
1. no? OK.. next
2. Good answer..

One point is that you can not use delete to clear the bullet directly. 
that will cause a big demage to your process because you create a empty drawable element!

Actually when we do the collision / 'lision / detection, the bullet on the wall will be bush in to a stack firstly.
After checking all the bullet in current scene node tree, 
we find each bullet in the stack, 
remove the link relation between that bullet and its parents first.
At the last step, we delete bullet to free the memory.

I shared this to you because we met a unreasonable bugs last week because the error order of deleting the useless scene node.

## Switch between states
In a game, we are not always playing the game.

For this reason we have many states such as manu-state, winstate and pause-state. 

The rule of Switching state follows the basic logic. 

See here, from manu state, we can go to game state, whcih mean we want to play the game, 
or we can goto confirm state to show that we want to exit the game.

More technically we use a state stack to implement the transfer. for instance, \TODO

## Button
How do we give a friendly interface to let use select the state that he want? That is the Button Class.

Button is inherited from Class Component, which has some members to record the value is selected or not.

The container of the botton support user to change thier selection as they wish.

Once a button is selected, we changed its color to let user know.

## Command

Sound easy, right? Yes it is!

Now lets go to a complicate one, the command class. 

The issue is when player press a key, eject a bullet for example, it is no hard to call the function fire() on Tank directly.
We do want to find the pointer to that tank.

In stead of that we push the command into command queue. 
At th mean time We set private member variables Category on both SceneNode Class and command class. 

When our program deal with a command, it will traverse through all the scene node tree and compare its mCategory. 

Action will be processed only when the mCategory of command and scene node match.

# Demo
That is the main technical stuff by now. Feel sleepy? Now give time to Yang to show the demo!!!!!!

# Q & A
That is all of the project. thanks for lestening. Please see more details on our report.
Any questions??


