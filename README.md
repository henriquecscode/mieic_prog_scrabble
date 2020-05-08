# Scrabble Junior + Board Builder

Scrabble Junior is a game all about capturing letters and getting points in a big board filled with intersecting words. Don't like standard boards? Don't worry, we got you covered with our Board Builder, which you can use to create board files (in .txt) with words as complicated as you like that you can use later to play the game with a max. of 4 players! Be attentive, play your chips right and you will be the one who comes out on top!

## Installation

With the game, we already provide a pair of .exe files which one can easily open to play the game, along with a simple standard board so you can get yourself used to playing! To jump in and play, the "BOARD.txt" file should ALWAYS be in the same folder as the "main.exe" file!
The Board Builder will create its board files and save him in the same folder its executable is in!

```bash
pip install foobar
```

## Rules

Welcome to SCRABBLE JUNIOR, a game where your main objective is to fill words placed in a board, letter by letter, in an orderly fashion - what do we mean by this? You can only place a chip in a letter that's:
⋅⋅* not captured (a captured letter will be shown in RED);
⋅⋅* the first uncaptured letter in a word.
Each player will be assigned 7 chips at the beginning of the game, and you'll be able to switch chips as you please, but let's start with the basics: look the screenshot below.
![ex1](https://user-images.githubusercontent.com/64466406/81388100-b1b22300-910f-11ea-8054-a6bd9cb36e6c.png)

As you can see, Player1 can capture both the F (of FRUIT) and the M (of MUSIC) in one play, to do so, he inputs the coordinates Ab and Ca. This will take the mentioned letters from his pool, turning them into invalid chips by marking them with a -.
![ex2](https://user-images.githubusercontent.com/64466406/81388458-3ac95a00-9110-11ea-8aae-602e776dddd5.png)

Now, imagining Player2 has chips to do so for the sake of this explanation, he intends to keep capturing letters from the words FRUIT and MUSIC. He only wants to play one chip, so let's think what can he do: he can either capture the R (Bb) from FRUIT or the U (Cb) from MUSIC. Depending on his/her strategy, one might be more ideal. If he captures the R, he'll be able to then capture the shared U without any problems, but if he captures the U first, he'll only be able to capture the I from FRUIT after he captures its R - this is the orderly principle we mentioned before. This way, it's a more fair experience, since chips are randomly assigned!
Points are only given by words completed - you will only get a point if you capture the last letter of a word. Of course, if you finish more than one word at once, you'll get multiple points!
Whatever he plays, it's not our business, but you do want to know how to exchange chips, right? You can either exchange 1 or 2 chips at a time, and this counts as a full turn: you won't be able to play your new chips until your opponents have a turn first. One player turn consists of 2 plays: an invalid play would be a coordinate of a captured letter or just an empty space of the board, but these DO NOT INVALIDATE other valid plays (meaning 1 valid play will always be counted).
![ex3](https://user-images.githubusercontent.com/64466406/81389602-035bad00-9112-11ea-8388-7560f0fc2a5a.png)

To exchange a chip, one of your plays should be Zz. To exchange two, both plays need to be Zz. Chip switching is limited by three factors alone: invalid chips, the letter pool and your concentration.
![ex4](https://user-images.githubusercontent.com/64466406/81389700-27b78980-9112-11ea-9b06-62ae8b221a55.png)

Player1 decided to exchange 2 chips: he is immediately warned about the letter pool before each play, so he knows he can exchange 2 chips without a problem. When the letter pool is empty (0 letters), the game will declare a winner automatically. Right after, his pool is printed again so he can be reminded of his chips - he can exchange chips in positions 1, 2, 3, 5 and 6. If he inputs any other position, any switching will be COMPLETELY invalidated - this is the game punishing you for not paying attention, so always be calm about exchanging chips, we wouldn't want you to lose a letter you actually need or to waste a turn!
Other than this, the game will also declare a winner if, by some insane amount of luck, all words are captured.
Some more intricate cases are also contemplated, and the game will let you know what to do whenever they're appliable!

```python
import foobar

foobar.pluralize('word') # returns 'words'
foobar.pluralize('goose') # returns 'geese'
foobar.singularize('phenomena') # returns 'phenomenon'
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
