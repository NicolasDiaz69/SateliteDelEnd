# Satelite del End

Cansat "We always come back" desarrollado en 2021 por:

*_Lina Sofía Daza Melo_*

*_Erick Steven Álvarez Ochoa_*
 
*_Nicolas Díaz Olaya_*

*_Juan Andrés Gutierrez Castro_*

**_ORIENTADOR_**

*_Miguel Angel Califa Urquiza_*

**Introducción**

*_Cyborg CEA es un equipo pereteneciente al Colegio Empresarial Los Andes de Facatativá, Cundinamarca, creado en el año 2021, su objetivo es desarrollar y probar multiples prototipos._* 

**Materiales para el lanzamiento del cansat** 
| Nombre | Cantidad |
| ------------- | ------------- |
| [Tarjeta de desarrollo Wemos D1 Mini.](https://www.prometec.net/wemos-d1-esp8266-wifi/) | 3 |
| [Modulo Micro SD.](https://www.prometec.net/wemos-d1-esp8266-wifi/) | 1 |
| [Modulo BMP180.](https://www.electronicaembajadores.com/es/Productos/Detalle/LCA2007/modulos-electronicos/arduino-d1-mini/wemos-d1-mini-sensor-de-presion-barometrica-bmp180) | 1 |
| [Modulo DHT11.](https://tienda.bricogeek.com/wemos-d1-mini/1591-shield-temperatura-y-humedad-dht11-para-wemos-d1-mini.html) | 1 |
| [Modulo GPS Neo 6M.](https://randomnerdtutorials.com/guide-to-neo-6m-gps-module-with-arduino/) | 1 |
| [Modulo Led RGB.](https://www.wemos.cc/en/latest/d1_mini_shield/rgb_led.html) | 1 |
| [Modulo LDR Digital.](https://forum.arduino.cc/t/ldr-sensor-digital-sensitivity/389338) | 1 |
| [Modulo RF 915 MHz E32 915T210.](https://www.didacticaselectronicas.com/index.php/comunicaciones/lora/m%C3%B3dulo-lora-915mhz-tarjetas-modulos-lora-lo-ra-de-comunicaci%C3%B3n-transmisores-rf-inal%C3%A1mbricos-wireless-sx1276-de-largo-alcance-de-915mhz-iot-detail)| 1 |
| [Sensor de Polvo Gp2y1014au0f.](https://co.mouser.com/ProductDetail/Sharp-Microelectronics/GP2Y1014AU0F?qs=rrS6PyfT74eynj5J61tvwA%3D%3D) | 1 |

**Objetivo**

Recopilar datos metereologicos para su posterior analisis, midiendo a diferentes alturas (0 - 100 metros).

**Interconexion entre los componentes de hardware**

Acontinuación encontraras en una imagen el diagrama esquematico tanto del CANSAT como del modulo receptor.

![Diagrama esquematico](https://raw.githubusercontent.com/NicolasDiaz69/SateliteDelEnd/main/Extra/Schematic_SateliteDelEnd_2021-09-15.png)

**Software**

* Arduino IDE.

**Como ensamblar el CANSAT**

[Click aqui para ver en Thinkercad](https://www.tinkercad.com/codeblocks/4GfSZVkioQ6-cansat-2021)

![Diagrama](https://raw.githubusercontent.com/NicolasDiaz69/SateliteDelEnd/main/Extra/Armado_Cansat.gif)

**Thingspeak Chanel**

[Cyborg CEA 4.0](https://thingspeak.com/channels/1422276)

**Resultados**

***Thingspeak***

![Diagrama](https://raw.githubusercontent.com/NicolasDiaz69/SateliteDelEnd/main/Extra/ResultadosRT.PNG)

***Post-Procesados***

![Diagrama](https://raw.githubusercontent.com/NicolasDiaz69/SateliteDelEnd/main/Extra/ResultadosLog.PNG)

**Conclusiones**

1. Contrario a la relacion que se evidencia a baja altura (<50 metros) donde al aumentar la altura disminuye la temperatura, hemos evidenciado por las mediciones obtenidas que al aumentar la altitud aumenta tambien la temperatura puesto que nos acercamos mas al sol (El cual es un comportamiento mas cercano al que experimentaria un satelite en orbita terrestre - Calor extremo en el dia, frio extremo en la noche).

2. La humedad refleja un comportamiento inverso al de la temperatura, por lo que a mayor temperatura menor humedad.

2. Tras realizar registro del tiempo de vuelo hasta el punto mas alto (menos de 30 segundos) se evidencia que el lanzamiento de un satélite tipo Bala resulta más óptimo en tiempo que un lanzamiento propulsado con combustible líquido, una bala disparada al aire puede subir hasta 1.6 Kilómetros en pocos segundos.

3. Las lecturas obtenidas demuestran que al aumentar la altura la temperatura disminuye junto con la presión atmosférica.

4. El diseño modular y simplificado tanto del cansat como del dispositivo de lanzamiento facilita su implementación en diferentes espacios y su fácil traslado.

**Aplicaciones futuras**

1. Tras el desarrollo de este proyecto podemos concluir que los microsatélites análogo a los celulares tendrán mayor cantidad de sensores a futuro y su software será actualizable para extender sus prestaciones.

2. Los microsatélites pueden a futuro contar con un sistema de navegación muy simple de forma que su caída al finalizar su ciclo de vida sea en un terreno en el cual se espera para su reutilización.

3. Al ser microsatélites, se podrán crear en el cielo diseños luminosos complejos análogos a los creados por las luciérnagas utilizando algoritmos matemáticos al aprovechar la oscuridad de la noche en conjunto con el LED integrado en el microsatélite.



**Librerias**

* Lora Library: https://github.com/KrisKasprzak/EBYTE
* DHT Library: https://github.com/adafruit/DHT-sensor-library
* BMP180 Library: https://github.com/LowPowerLab/SFE_BMP180
* GPS Neo 6M Library: https://github.com/mikalhart/TinyGPS
* Wemos D1 Led Library: https://github.com/adafruit/Adafruit_NeoPixel

**Notas**

* Los dispositivos Lora deben estar preconfigurados para operar, por lo que recomendamos implementar el siguiente [tutorial](https://makersportal.com/blog/2019/10/5/arduino-lora-network) previo al lanzamiento con los modulos LORA.

## Licencia

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
