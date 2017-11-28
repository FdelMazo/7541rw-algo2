# KevinBaconPy
Implementacion de 'Seis Grados de Kevin Bacon' en Python 3

Originalmente usado en el 2c2017 como trabajo práctico de [Algoritmos y Programacion II](https://algoritmos-rw.github.io/algo2/tps/2017_2/tp3) en la FIUBA.

Para mayor contexto, se recomienda leer antes la [consigna](Consigna.md)

Este trabajo pretende modelar la idea de los 'Seis Grados de Kevin Bacon' utilizando la base de datos de IMDB (parseada con IMDBtoCSV)

### Como usar

* Descargar [actors.csv](https://drive.google.com/drive/folders/0B2J1xTZnFQnBVnZzcF8xR3Z3SVE) o bien usar un archivo generado con [IMDBtoCSV](https://github.com/fdelmazo/imdbtocsv)
  * Tambien se puede usar el test.csv proporcionado dentro de la carpeta pruebas
* Llamar a `python3 kevin_bacon.py actors.csv`
* Utilizar cualquiera de los comandos disponibles. De requerir un argumento adicional, debe ser escrito entre comillas simples, por ejemplo: `camino_hasta_KB 'Penn Sean'`
* Para unas pruebas automatizadas y comprobar que seis_grados.py y el grafo.py (pero no kevin_bacon.py) funcionen, de manera básica, correctamente: Pasar los 3 archivos .py a 'Pruebas' y ejecutar `make`
