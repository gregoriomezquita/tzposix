# tzposix
Get the timezone posix string from GPS coordinates

El software de algunos microcontroladores siguen el standard POSIX de ajuste de hora local. Esto quiere decir que debes ajustar la variable de entorno "TZ" con [setenv](http://man7.org/linux/man-pages/man3/setenv.3.html) y luego llamar a [tzset](http://man7.org/linux/man-pages/man3/tzset.3.html) de la liberia *time*.  
[tzposix.c](./tzposix.c) es un CGI para convertir la localizacion geografica (lat, long) en el string POSIX necesario para la variable de entorno TZ. Devuelve un json conteniendo la version Olson y POSIX de TimeZone. Una vez compilado y descargado en el directorio cgi-bin de tu servidor web se invoca de la siguiente manera:
<center>

    https://yourserver/cgi-bin/tzposix?lat=[float]&lon=[float]

</center>
Ejemplo:  
<center>

    https://sotech.es/cgi-bin/tzposix?lat=40.4165000&lon=-3.7025600

</center>

devuelve el siguiente JSON:
<center>

    {"olson": "Europe/Madrid", "posix": "CET-1CEST,M3.5.0,M10.5.0/3"}

</center>
El fichero [tzinfo.json](./tzinfo.json)  contiene la tabla de correspondencia entre el formato Olson y el formato POSIX. Las instrucciones para crearlo están en [tzinfo](https://github.com/pgurenko/tzinfo).


