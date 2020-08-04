# Micoprocessor Interfaces
The **interface** in a **microprocessor** is an integrated circuit that performs the basic functions of the central processing unit. It enables a user to communicate with a computer.
[![](https://mermaid.ink/img/eyJjb2RlIjoiZ3JhcGggVERcblx0XG5cdEMoKE1pY3JvcG9jZXNzb3IgSW50ZXJmYWNlKSlcblx0QyAtLT58T25lfCBEW0dQSU8gXVxuICAgICAgQyAtLT58VHdvfCBHW0kyQ11cbiAgICAgIEMgLS0-fFRocmVlfCBIW1NQSV1cbiAgICAgIEMgLS0-fEZvdXJ8IFZbVUFSVF1cbiAgICAgIEMgLS0-fEZpdmV8YVtQV01dXG5cdFx0XHRcdFx0IiwibWVybWFpZCI6eyJ0aGVtZSI6ImRlZmF1bHQifSwidXBkYXRlRWRpdG9yIjpmYWxzZX0)](https://mermaid-js.github.io/mermaid-live-editor/#/edit/eyJjb2RlIjoiZ3JhcGggVERcblx0XG5cdEMoKE1pY3JvcG9jZXNzb3IgSW50ZXJmYWNlKSlcblx0QyAtLT58T25lfCBEW0dQSU8gXVxuICAgICAgQyAtLT58VHdvfCBHW0kyQ11cbiAgICAgIEMgLS0-fFRocmVlfCBIW1NQSV1cbiAgICAgIEMgLS0-fEZvdXJ8IFZbVUFSVF1cbiAgICAgIEMgLS0-fEZpdmV8YVtQV01dXG5cdFx0XHRcdFx0IiwibWVybWFpZCI6eyJ0aGVtZSI6ImRlZmF1bHQifSwidXBkYXRlRWRpdG9yIjpmYWxzZX0)
## 1.GPIO
- A **GPIO (general-purpose input/output)** port handles both incoming and outgoing
digital signals.    
- GPIO can be used as **Input or Output.**

#### GPIO Pins of Raspberry pie
![](https://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/06/Raspberry-Pi-GPIO-Header-with-Photo-702x336.png)

## 2.Universal Asynchronous Receiver Transmitter(UART)
         
         
![](https://www.allaboutcircuits.com/uploads/articles/BBUART_diagram1_2.JPG)
![](https://developer.electricimp.com/sites/default/files/attachments/images/uart/uart3.png)
## 3.Serial Peripheral Interface(SPI)
        
         
![](https://cdn.sparkfun.com/assets/c/7/8/7/d/52ddb2dcce395fed638b4567.png)
##### Master with multiple slaves
![](https://embeddedsystech.files.wordpress.com/2012/05/350px-spi_three_slaves_daisy_chained-svg2.png)

## 4.Inter-Integrated Circuit(I2C)
![](https://kcssol.files.wordpress.com/2019/05/ohhh...-where-and-how-to-see-i2c-lets-focus-on-inter-integrated-circuits-part-i.jpg)
### Data Transmission in I2C
![](https://www.electronicshub.org/wp-content/uploads/2018/02/Basics-of-I2C-Communication-Data-Transfer-Protocol.jpg)
### I2C Frame Structure
![](https://www.researchgate.net/profile/Guillaume_Delbergue/publication/324792444/figure/fig28/AS:631572537565212@1527590035817/A-I2C-frame-structure.png)

## 5.Pulse Width Modulation(PWM)
Pulse Width Modulation, or **PWM**, is a technique for getting analog results with digital means. Digital control is used to create a square wave, a signal switched between on and off. ... The duration of "on time" is called the pulse width. To get varying analog values, you change, or modulate, that pulse width.          
#### PWM Duty cycle
![](https://www.arduino.cc/en/uploads/Tutorial/pwm.gif)
