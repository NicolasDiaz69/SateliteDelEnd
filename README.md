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

* Tarjeta de desarrollo Wemos D1 Mini.
* Modulo Micro SD.
* Modulo BMP180.
* Modulo DHT11.
* Modulo GPS Neo 6M.
* Modulo RF 915 MHz E32 915T210.
* Sensor de Polvo Gp2y1014au0f.

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
