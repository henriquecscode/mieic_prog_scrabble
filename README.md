# Scrabble Junior + Board Builder

<p align="justify">
Scrabble Junior is a game all about capturing letters and getting points in a big board filled with intersecting words. Don't like standard boards? Don't worry, we got you covered with our Board Builder, which you can use to create board files with words as complicated as you like to have the most fun you can with a max. of 4 players. Be attentive, play your chips right and you will be the one who comes out on top!
</p>

## Installation

<p align="justify">
With the game, we already provide a pair of .exe files which one can easily open to play the game, along with a simple standard board so you can get yourself used to playing! To jump in and play, the BOARD file you intend to use for playing should ALWAYS be in the same folder as the "main.exe" file!
The Board Builder will create its board files and save them in the same folder its executable is in!
</p>

## Rules

### Basic Rules
<p align="justify">
Welcome to SCRABBLE JUNIOR, a game where your main objective is to fill words placed in a board, letter by letter, in an orderly fashion - what do we mean by this? You can only place a chip in a letter that's:<ul>
<li>not captured (a captured letter will be shown in RED);</li>
<li>the first uncaptured letter in a word.</li></ul>
</p>

### How to Play
<p align="justify">
Each player will be assigned 7 chips at the beginning of the game, and you'll be able to switch chips as you please, but let's start with the basics: look the screenshot below.
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/64466406/81388100-b1b22300-910f-11ea-8054-a6bd9cb36e6c.png">
</p>

<p align="justify">
As you can see, Player1 can capture both the F (of FRUIT) and the M (of MUSIC) in one play, to do so, he inputs the coordinates Ab and Ca. This will take the mentioned letters from his pool, turning them into invalid chips by marking them with a -.
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/64466406/81388458-3ac95a00-9110-11ea-8aae-602e776dddd5.png">
</p>

<p align="justify">
Now, imagining Player2 has chips to do so for the sake of this explanation, he intends to keep capturing letters from the words FRUIT and MUSIC. He only wants to play one chip, though, so let's think about what can he do: he can either capture the R (Bb) from FRUIT or the U (Cb) from MUSIC. Depending on his/her/their strategy, one might be more ideal:
<ul>
<li>if he captures the R, he'll be able to then capture the shared U without any problems;</li>
<li>if he captures the U first, he'll only be able to capture the I from FRUIT after he captures its R;</li></ul>
<p align="justify">
  This the long version of the <em>orderly fashion</em> we mentioned before. This way, it's a fair experience, since chips are randomly assigned!
Whatever Player2 decides to do, it's not our business, though. One player turn consists of 2 plays: an invalid play would be a coordinate of a captured letter or just an empty space of the board, but these <strong>DO NOT INVALIDATE</strong> other valid plays (as long as you're doing a valid play, it'll be counted). Yes, you can capture 2 letters from the same word in the same turn (<em>back to back</em>), but you need to input the coordinates in the correct order!
</p>

### Getting Points
<p align="justify">
Points are only given by words completed - you will only get a point if you capture the last letter of a word. Of course, if you finish more than one word at once, you'll get multiple points!
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/64466406/81389602-035bad00-9112-11ea-8388-7560f0fc2a5a.png">
</p>

### Exchanging Chips
<p align="justify">
You can either exchange 1 or 2 chips at a time, and this counts as a full turn: you won't be able to play your new chips until your opponents have a turn first. To exchange a chip, one of your plays should be Zz. To exchange two, both plays need to be Zz. Chip switching is limited by three factors alone: invalid chips, the letter pool and your concentration.
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/64466406/81389700-27b78980-9112-11ea-9b06-62ae8b221a55.png">
</p>

<p align="justify">
Player1 decided to exchange 2 chips: he is immediately warned about the letter pool before each play, so he knows he can exchange 2 chips without a problem. When the letter pool is empty (0 letters), exchanging chips becomes impossible. To help him choose which chips to switch, his/her/their pool is printed again - he can exchange chips in positions 1, 2, 3, 5 and 6.
If he inputs any other position, any switching will be COMPLETELY invalidated - this is the game punishing you for not paying attention, so always be calm about exchanging chips, we wouldn't want you to lose a letter you actually need or to waste a precious turn!
</p>

## Board Builder

### How to Use
<p align="justify">
Open the executable and you'll be greeted with a very simple interface that shall let you build your own boards. The first thing you'll have to do is to give the program a file with words - don't worry, we already got you covered with a big one ("WORDS.txt") -, that will be used to verify the words you wish to place in a board, that will even give you some replacing words in case you choose a word that isn't part of the file! After that, you'll be asked about the size of the board, which will always be square-shaped! Finally, the board builder will work similarly to the SCRABBLE JUNIOR game, but with a more slowed down pace, for each letter you wish to place in the board you'll need to provide:
</p>
<ul>
<li>a row coordinate (an upper case letter);</li>
<li>a collumn coordinate (a lower case letter);</li>
<li>an orientation (either H for Horizontal or V for Vertical);</li>
</ul>
<p align="justify">
From just this, you will be able to build the board following some very simple guidelines - the builder will recognize situations where you're trying to do something that you shouldn't be able to do, and remind you accordingly, so don't worry about following rules! Don't forget to give your custom boards some appealing names! Might we suggest "BOARD_BY_ME"?
</p>

## FAQ
> Why can't we choose who gets to play first?
<p align="justify">
<em>Scrabble Junior</em> is a luck-based game. This means starting first has no real advantage. If you do wish to choose who plays first, do it before inputting your names when prompted by the game - it will follow the order by which you input said names!
</p>

> How can I finish the game?
<p align="justify">
Whenever the letter pool (which will be constantly updated) is empty or (by some extreme luck) you capture all words in a board, the game will declare a winner. 
</p>

> Are there any special cases a player should know about?
<p align="justify">
When those cases arise, the game will tell the player what he should do. Most of the times, it's boils down to having to forcefully make an invalid play, since this is a mostly neutral action in a game - the only punish for invalid plays is a simple warning that the play was, in fact, invalid. This means that when you do it <em>on purpose</em>, there's nothing to lose from it, it's just a way to move to the next turn until the game can actually do what it should!
</p>

> How many words can I put in a board when building one?
<p align="justify">
As many as the simple guidelines the BOARD BUILDER follows allows you to, which only prevent you from having adjacent words unless they somehow intersect. The size of the board is obviously at play here as well, but that's only natural.
</p>

> Why do I have to put the executables in the same place as the files I need to use?
<p align= "justify">
Both programs were made to work inside a specific folder for them - we took this into consideration since we also like having an organized computer, with a folder for a game. Also, the alternative consisted in having the player copy the WHOLE path to a file and pasting it on input, which would be (in our humble opinion) a hassle for everyone.
</p>

> Is there any easy strategy to win the game?
<p align= "justify">
Being attentive and concentrated in what you're doing is a great start - which we mean without an ounce of passive-aggressiveness towards the person reading this. As alluded before, SCRABBLE JUNIOR is <em>kind of</em> a luck based game. We tried to make it a little more stategy based by asking for attention from the player - for example: you won't be forced to play a chip you can play because you might wish to exchange it instead for a potentially better one -, so that's really all we can tell you. But keeping track of each player's chips can definitely be useful, as well!
</p>

> I found a bug! How should I tell you about it?
<p align= "justify">
First of all, we're so sorry and hope it didn't affect your experience of the game or the builder. If you wish to contact us, try reaching out through GitHub and tell us about the issue. We'll try to attend to it as soon as possible and thanks for worrying about it!
</p>


## Choices we made
<ul>
<li>The board builder suggests words to the user whenever they try to place a letter that's not part of the word list file used;</li>
<li>The board builder makes sure words aren't entirely adjacent (2 horizontal words won't be in succeeding horizontal lines, just like 2 vertical words won't be in succeeding vertical lines and two words of different orientation won't "touch" unless they share an intersecting letter);</li>
<li>A player cannot exchange an invalid (-) chip - should one player try it, their turn will immediately end;</li>
<li>Players don't get punished for invalid plays - an invalid play will just result in a simple warning;</li>
<li>Since it was recquired to have a limited letter pool, players will be punished for trying to exchange invalid (-) chips;</li>
<li>Trying to capture letters in the wrong order (for example, trying to capture the R and U in FRUIT before the F or even inputting the U coordinates before R will not capture the words, since the capturing is done sequentially, one play at a time;</li>
<li>Players get to force a tie, but doing this won't declare a winner - seemed like the fair thing to do;</li>
<li>The letter pool ending results in an abrupt ending, but with a winner declared;</li>
<li>The letter pool gets randomly assigned letters, which means not always will it get the recquired letters to finish the board;</li>
<li>Player pools get sorted to help with choosing chips to exchange;</li>
<li>
</ul>