# **Microprocessor Interface Programming**
**Interface** is the path for communication between two components. Interfacing is of two types, memory interfacing and I/O interfacing.


## Block Diagram of Memory and I/O Interfacing
![](https://www.tutorialspoint.com/microprocessor/images/interfacing.jpg)
- We will be using Shunya interfaces for programming the microprocessor Interfaces.    

## Over view of the Shunya lib
[![](https://mermaid.ink/img/eyJjb2RlIjoiZ3JhcGggVERcblx0XG5cdEN7U2h1bnlhIEludGVyZmFjZSBDb3JlIEFQSX1cblx0QyAtLT58T25lfCBEW0dQSU8gQVBJXVxuXHRDIC0tPnxUd298IEVbSW50ZXJydXB0IEFQSV1cblx0QyAtLT58VGhyZWV8IEZbRGVsYXkgQVBJXVxuICAgICAgQyAtLT58Rm91cnwgR1tJMkMgQVBJXVxuICAgICAgQyAtLT58Rml2ZXwgSFtTUEkgQVBJXVxuICAgICAgQyAtLT58U2l4fCBWW1VBUlQgQVBJXVxuICAgICAgQyAtLT58U2V2ZW58YVtQV00gQVBJXVxuXHRcdFx0XHRcdCIsIm1lcm1haWQiOnsidGhlbWUiOiJkZWZhdWx0In0sInVwZGF0ZUVkaXRvciI6ZmFsc2V9)](https://mermaid-js.github.io/mermaid-live-editor/#/edit/eyJjb2RlIjoiZ3JhcGggVERcblx0XG5cdEN7U2h1bnlhIEludGVyZmFjZSBDb3JlIEFQSX1cblx0QyAtLT58T25lfCBEW0dQSU8gQVBJXVxuXHRDIC0tPnxUd298IEVbSW50ZXJydXB0IEFQSV1cblx0QyAtLT58VGhyZWV8IEZbRGVsYXkgQVBJXVxuICAgICAgQyAtLT58Rm91cnwgR1tJMkMgQVBJXVxuICAgICAgQyAtLT58Rml2ZXwgSFtTUEkgQVBJXVxuICAgICAgQyAtLT58U2l4fCBWW1VBUlQgQVBJXVxuICAgICAgQyAtLT58U2V2ZW58YVtQV00gQVBJXVxuXHRcdFx0XHRcdCIsIm1lcm1haWQiOnsidGhlbWUiOiJkZWZhdWx0In0sInVwZGF0ZUVkaXRvciI6ZmFsc2V9)

### Example of a GPIO API
> GPIO API    
**pinmode()**      
**Description** : Sets the direction of the GPIO pin to INPUT or OUTPUT     
**Parameters**      
> - physicalPin(int) - Physical pin number of the GPIO     
> - mode(int) - GPIO mode either INPUT or OUTPUT

> **Return-type** : void    
> **Usage** : pinmode(7, OUTPUT);