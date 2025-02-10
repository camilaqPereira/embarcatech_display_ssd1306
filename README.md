<h1 align="center"> Exibição de _char_ (recebidos via serial) em SSD1306 usando BitDogLab</h1>

## Sobre o projeto

- [Detalhamento de funcionalidades](https://github.com/camilaqPereira/embarcatech_display_ssd1306/blob/main/docs/embarcatech_display_slide.pdf)
- [Sobreo o projeto - Youtube](https://youtu.be/FpLeyuu5WhI)
- [Demonstração de funcionamento](https://youtu.be/PTZMiRFgVaQ)

## Periféricos da BitDogLab utilizados

- WS2812: matriz de leds -> controlado pela PIO (máquina de estádos programável)
- LED RGB verde e azul -> gerenciados no callback das IRQs
- Pushbuttons A e B -> gerenciado por meio de IRQ
- Display SSD1306 -> gerenciado por meio da comunicação I2C

## Instruções de uso


### Clone o repositório
No seu terminal, digite o seguinte comando:

<code> git clone https://github.com/camilaqPereira/embarcatech_display_ssd1306.git </code>

### Importe o projeto no VSCode
No VSCode, importe o projeto utilizando a extensão oficial Rasberry Pi

### Compile o projeto
Compile o projeto utilizando o botão **COMPILE** no fim da página (ou **RUN** caso sua placa já esteja conectada ao computador em modo boot)

### Controle dos LEDs
Caso tenha gravado o código na placa seguindo o passo anterior, basta pressionar os pushbuttons para que os leds sejam ativados.

### Comunicação serial
No VSCode, abra o monitor serial e inicie o monitoramento da porta associada à sua placa. Interaja com o programa enviando letras e números pelo monitor serial.
