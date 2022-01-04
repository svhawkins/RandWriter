# RandWriter
Generates random realistic text by using markov models and maps

## Requirements:
- Access to command line

## Running the Exectuable
```
./TextWriter [kgram level*] [desired length of text to generate] < [.txt file to generate from]
```
*(kgram being the length of the string that occurs prior to the occurence of a character. higher levels make for more realistic text)*

## Example Execution
```
./TextWriter 10 1000 < aesop.txt
```

### Result
```
me provide the wine to pour over you when it is time
to visit their king.  He
was neither wrathful, cruel, nor tyrannical, but just as he was about
to fly off, he made some excuse to send her
home on a visit to her father died, as there was no danger threatening from a long journey lay down, overcome with me instantly."  The Dog, wagging his tale and believing what he said, 
"if you will soon
let you know that you have done to yourself the trouble," said the 
Satyr, "a
fellow who with the help of a pole endeavored to carry out the least 
fear you,
nor are you stronger than herself, saying that if the Horseman got 
the hare, he rode
off as fast as he could run.  A neighbor, seeing the preparations for
a universal applause.  A Countryman 
 
A RICH NOBLEMAN once opened the
faggot, took their spades and mattocks and carefully provided nothing
was found, they cheered the actor, and
loaded him with their teeth.  A Fox, who had never been brought out on a journey, driving his design, she climbed 
```
*note: your result will not be exact to this. but the wording and style should be similar.*

## Miscellany
- fails at large input files (>= 1MB)
- aesop.txt, trump-clinton1.txt, romeo.txt and IolantheLibretto.txt also included as sample files
